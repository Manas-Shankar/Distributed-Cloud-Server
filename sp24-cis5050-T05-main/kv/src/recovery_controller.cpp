#include "../include/recovery_controller.hpp"
#include "../include/tablet_manager.hpp"
#include "../include/tablet.hpp"
#include "../include/status_manager.hpp"

Recovery_Controller::Recovery_Controller(const std::string &server_address,
                                         const std::string &primary_address,
                                         const std::unordered_map<std::string, std::shared_ptr<grpc::Channel>> &channels) : server_address_(server_address), is_primary_(server_address == primary_address), is_recovering_(false), channels_(channels)
{
    // load the checkpoint version number from filename upon server restart
    int64_t checkpoint_version_number = Tablet_Manager::get_instance().get_checkpoint_version_number();
    // setup the client stub for the recovery service
    std::cout << "Primary address: " << primary_address << std::endl;
    for (const auto &channel : channels_)
    {
        // skip its own address in stub setup
        if (channel.first == server_address)
            continue;
        stubs_[channel.first] = recovery::RecoveryService::NewStub(channel.second);
    }
}
Recovery_Controller::~Recovery_Controller()
{
}

// called whenever a node comes back up after a failure: starts the recovery process
void Recovery_Controller::start_recovery()
{
    // Implement case where there is no active primary node
    if (Status_Manager::GetInstance().get_primary_address() == "-1")
    {
        std::cerr << "No active primary node. Set our node as an active node so other nodes can recover from me" << std::endl;
        Status_Manager::GetInstance().set_to_recovered();
        return;
    }
    std::cout << "Starting recovery" << std::endl;
    set_is_recovering(true);
    // get the checkpoint number from the tablet manager
    int64_t checkpoint_number = Tablet_Manager::get_instance().get_checkpoint_version_number();
    // get list of the number of lines of each log file (transaction log) from the tablet manager
    std::vector<int64_t> log_line_numbers = Tablet_Manager::get_instance().get_log_line_numbers();

    int retry_count = 0;
    int sleep_time = 1;
    while (!send_start_recovery(checkpoint_number, log_line_numbers))
    {
        std::cerr << "Error starting recovery. Retrying..." << std::endl;
        sleep(1);
        retry_count++;
        if (retry_count > 5)
        {
            std::cerr << "Error starting recovery. Max retries reached." << std::endl;
            set_is_recovering(false);
            return;
        }
        sleep_time *= 3;
    }
    send_recovery_complete();
    set_is_recovering(false);
    // let the backend master know that the node has recovered
    Status_Manager::GetInstance().set_to_recovered();
}

bool Recovery_Controller::send_start_recovery(int64_t checkpoint_number, const std::vector<int64_t> &log_line_numbers)
{
    // setup context, request and response objects
    recovery::StartRecoveryResponse response;
    grpc::ClientContext context;
    recovery::StartRecoveryRequest request;
    request.set_checkpoint_version_number(checkpoint_number);
    for (const auto &log_line_number : log_line_numbers)
    {
        request.add_log_number(log_line_number);
    }
    // send the checkpoint number and log numbers to the primary node to get the recovery type
    std::cout << "primary: " << Status_Manager::GetInstance().get_primary_address() << std::endl;
    grpc::Status status = stubs_[Status_Manager::GetInstance().get_primary_address()]->StartRecovery(&context, request, &response);
    if (status.ok())
    {
        std::cout << "Recovery type: " << response.type() << std::endl;
        if (response.type() == recovery::RecoveryType::UP_TO_DATE)
        {
            std::cout << "Node is up to date" << std::endl;
        }
        else if (response.type() == recovery::RecoveryType::CHECKPOINT_FILE)
        {
            // Delete all old Tablets from disk
            Tablet_Manager::get_instance().delete_all_outdated_tablet_files();
            bool checkpoints_rcvd = recover_checkpoint_files();
            if (checkpoints_rcvd)
            {
                recover_log_files(log_line_numbers);
                apply_queued_requests();
            }
            else
            {
                std::cerr << "Error recovering checkpoint files" << std::endl;
            }
        }
        else
        {
            recover_log_files(log_line_numbers);
            apply_queued_requests();
        }
    }
    else
    {
        std::cerr << "Error starting recovery" << status.error_message() << std::endl;
    }
    return status.ok();
}

bool Recovery_Controller::send_recovery_complete()
{
    // setup context, request and response objects
    recovery::RecoveryCompleteResponse rec_compl_response;
    grpc::ClientContext rec_compl_context;
    recovery::RecoveryCompleteRequest rec_compl_request;
    std::string primary = Status_Manager::GetInstance().get_primary_address();
    std::cout << "Primary address: " << primary << std::endl;
    grpc::Status notify_status = stubs_[primary]->NotifyRecoveryComplete(&rec_compl_context, rec_compl_request, &rec_compl_response);
    if (!notify_status.ok())
    {
        std::cerr << "Error notifying recovery complete: " << notify_status.error_code() << notify_status.error_message() << std::endl;
        return false;
    }
    return true;
}

// recover from the checkpoint file of primary node
bool Recovery_Controller::recover_checkpoint_files()
{
    // get the checkpoint files from the primary node
    recovery::CheckpointFilesResponse response;
    grpc::ClientContext context;
    recovery::CheckpointFilesRequest request;
    std::string address = server_address_;
    request.set_address(address);
    grpc::Status status = stubs_[Status_Manager::GetInstance().get_primary_address()]->GetCheckpointFiles(&context, request, &response);
    if (!status.ok())
    {
        std::cerr << "Error getting checkpoint files: " << status.error_code() << status.error_message() << std::endl;
        return false;
    }
    return true;
}

// recover from the transaction log of primary node
void Recovery_Controller::recover_log_files(std::vector<int64_t> log_line_numbers)
{
    // get the log files from the primary node
    recovery::LogFiles response;
    grpc::ClientContext context;
    recovery::GetLogFilesRequest request;
    for (const auto &log_line_number : log_line_numbers)
    {
        request.add_log_number(log_line_number);
    }
    if (!stubs_[Status_Manager::GetInstance().get_primary_address()]->GetLogFiles(&context, request, &response).ok())
    {
        std::cerr << "Error getting log files" << std::endl;
    }
    // get the log files from the response
    const google::protobuf::RepeatedPtrField<recovery::Log_File> &log_files = response.log_files();
    // write the log files to the disk
    for (const auto &log : log_files)
    {
        std::string file_name = Tablet_Manager::get_instance().get_server_path() + "/log_files/" + log.file_name();
        std::ofstream file(file_name, std::ios::binary | std::ios::app);
        if (!file.is_open())
        {
            std::cerr << "Error opening file" << std::endl;
        }
        std::cout << "Writing log file: " << log.file_name() << std::endl;
        file.write(log.content().data(), log.content().size());
        file.close();
    }
    apply_new_log_entries(log_files);
}

void Recovery_Controller::apply_new_log_entries(const google::protobuf::RepeatedPtrField<recovery::Log_File> &log_files)
{
    // Loop over log file and get the tablet for each log file and apply the log entries to the tablet
    for (const auto &log : log_files)
    {
        // get the tablet for the log file
        std::string file_name = log.file_name();
        size_t pos = file_name.find_last_of("_");
        if (pos != std::string::npos)
        {
            int tablet_id = stoi(file_name.substr(pos + 1));
            Tablet *tablet = Tablet_Manager::get_instance().get_tablet_by_id(tablet_id);
            // apply the log entries to the tablet
            std::istringstream line_stream(log.content());
            std::cout << "Applying logs to tablet: " << tablet_id << std::endl;
            tablet->apply_logs_to_memtable(line_stream);
        }
        else
        {
            std::cerr << "Error parsing logs. Log file name doesn't follow naming convention" << std::endl;
        }
    }
}

void Recovery_Controller::apply_queued_requests()
{
    // TODO: Implement the apply_queued_requests function so we can process requests during recovery
    /*
    // get the replication coordinator
    Replication_Coordinator &replication_coordinator = Replication_Coordinator::get_instance();
    // get the queued requests
    std::vector<std::string> queued_requests = replication_coordinator.get_queued_requests();
    // apply the queued requests
    for (const auto &request : queued_requests)
    {
        replication_coordinator.apply_request(request);
    }*/
}

void Recovery_Controller::set_is_recovering(bool is_recovering)
{
    is_recovering_ = is_recovering;
}

bool Recovery_Controller::recovery_in_progress()
{
    return is_recovering_;
}

bool Recovery_Controller::is_primary()
{
    return server_address_ == Status_Manager::GetInstance().get_primary_address();
}

bool Recovery_Controller::compare_log_numbers(const google::protobuf::RepeatedField<int64_t> &log_line_numbers_from_recovering_node, const std::vector<int64_t> &log_line_numbers)
{
    // compare the log line numbers from the recovering node with the log line numbers from the primary node
    return log_line_numbers_from_recovering_node.size() == log_line_numbers.size() &&
           std::equal(log_line_numbers_from_recovering_node.begin(), log_line_numbers_from_recovering_node.end(), log_line_numbers.begin());
}

bool Recovery_Controller::send_chunked_checkpoint_files(std::string caller_address)
{
    std::cout << "Sending checkpointing files" << std::endl;
    namespace fs = std::filesystem;
    // std::string folder_path = Tablet_Manager::get_instance().get_server_path() + "/tablets/";
    std::vector<Tablet *> tablets = Tablet_Manager::get_instance().get_all_tablets();
    std::cout << "Number of tablets: " << tablets.size() << std::endl;
    std::string path = Tablet_Manager::get_instance().get_server_path() + "/metadata.txt";
    std::cout << "Metadata file path: " << path << std::endl;
    std::filesystem::path metadata_file_path = path;
    // Open the metadata file
    std::ifstream metadata_file(metadata_file_path);
    if (!metadata_file.is_open())
    {
        std::cerr << "Error opening metadata file" << std::endl;
        return false;
    }
    try
    {
        for (const auto &tablet : tablets)
        {
            std::string file_path = tablet->get_file_path();
            if (!fs::exists(file_path))
            {
                std::cerr << "File does not exist: " << file_path << std::endl;
                continue; // Skip this file if it doesn't exist
            }
            int tablet_id = tablet->get_tablet_id();
            std::cout << "Tablet ID: " << tablet_id << std::endl;
            std::cout << "Getting range from metadata file" << std::endl;
            std::string starting_range = Tablet_Manager::get_instance().get_range_from_metadata_file(tablet_id, metadata_file);
            std::cout << "Sending checkpoint file: " << file_path << std::endl;
            const auto &entry = fs::directory_entry(file_path);
            std::ifstream file(entry.path(), std::ios::binary);

            if (!file.is_open())
            {
                return false;
            }

            // setup buffer for streaming file
            const size_t buffer_size = 1024 * 1024;
            std::vector<char> buffer(buffer_size);

            bool is_final_chunk = false;
            // std::string filename = entry.path().filename().string();

            while (!is_final_chunk)
            {
                file.read(buffer.data(), buffer_size);
                std::streamsize read_size = file.gcount();
                if (read_size < buffer_size)
                    is_final_chunk = true;

                // setup FileChunk object for streaming
                recovery::FileChunk chunk;
                chunk.set_content(buffer.data(), read_size);
                chunk.set_is_final_chunk(is_final_chunk);
                chunk.set_filename(file_path);
                chunk.set_tablet_id(tablet_id);
                chunk.set_starting_range(starting_range);
                // Send chunk back to caller
                grpc::ClientContext context;
                recovery::CheckpointChunkResponse response;
                grpc::Status status = stubs_[caller_address]->SendCheckpointChunk(&context, chunk, &response);
                if (!status.ok())
                {
                    std::cerr << "Error sending checkpoint chunk: " << status.error_code() << status.error_message() << std::endl;
                    return false;
                }
                std::cout << "Sent chunk to caller." << std::endl;
            }
            // close the file after streaming all chunks in file
            file.close();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }

    std::cout << "Finished sending checkpointing files" << std::endl;
    return true;
}

// recover from the checkpoint file of primary node
void Recovery_Controller::recover_with_checkpoint_chunks(std::string &bytes_content, const std::string &filename, const int &tablet_id, bool is_final_chunk, const std::string &starting_range)
{
    std::cout << "Recovering using checkpoint chunks" << std::endl;
    // folder containing all the checkpoint files
    std::cout << "Received chunk for tablet: " << tablet_id << std::endl;
    std::cout << "Filename: " << filename << std::endl;
    std::cout << "Is final chunk: " << is_final_chunk << std::endl;
    // check if we already have the file open
    std::string path = Tablet_Manager::get_instance().get_server_path() + "/tablets/";
    std::string file_name = filename.substr(filename.find_last_of("/") + 1);
    path = path + file_name;
    std::cout << "Path: " << path << std::endl;
    std::ofstream file(path, std::ios::binary | std::ios::app);
    if (!file.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
    }
    // write the chunk to the file
    file.write(bytes_content.data(), bytes_content.size());
    // if this is the last chunk, close the file
    if (is_final_chunk)
    {
        file.close();
        Tablet *tablet = Tablet_Manager::get_instance().get_tablet_by_id(tablet_id);
        if (tablet != nullptr)
        {
            tablet->update_file_path(filename);
        }
        else
        {
            Tablet_Manager::get_instance().add_tablet_from_checkpoint_file(path, starting_range);
        }
    }
}

bool Recovery_Controller::test()
{
    std::cout << "Testing Recovery Controller" << std::endl;
    return true;
}