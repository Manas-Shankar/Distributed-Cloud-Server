#include "../include/recovery_service_impl.hpp"

RecoveryServiceImpl::RecoveryServiceImpl(Recovery_Controller &recovery_controller) : recovery_controller_(recovery_controller)
{
}

grpc::Status RecoveryServiceImpl::StartRecovery(grpc::ServerContext *context, const recovery::StartRecoveryRequest *request, recovery::StartRecoveryResponse *response)
{
    // set is recovering to true:
    recovery_controller_.set_is_recovering(true);
    // Extract the checkpoint version number from the request
    int64_t checkpoint_version_number = request->checkpoint_version_number();
    const google::protobuf::RepeatedField<int64_t> log_line_numbers_from_recovering_node = request->log_number();

    // get the up to date checkpoint number from the tablet manager
    Tablet_Manager &tablet_manager = Tablet_Manager::get_instance();
    int64_t current_checkpoint_number = tablet_manager.get_checkpoint_version_number();
    std::vector<int64_t> log_line_numbers = tablet_manager.get_log_line_numbers();

    // Set the recovery type based on the checkpoint number
    if (current_checkpoint_number == checkpoint_version_number)
    {
        if (log_line_numbers.size() == 0 || recovery_controller_.compare_log_numbers(log_line_numbers_from_recovering_node, log_line_numbers))
        {
            response->set_type(recovery::RecoveryType::UP_TO_DATE);
        }
        else
        {
            response->set_type(recovery::RecoveryType::LOGFILES);
        }
    }
    else
    {
        response->set_type(recovery::RecoveryType::CHECKPOINT_FILE);
    }

    return grpc::Status::OK;
}

grpc::Status RecoveryServiceImpl::GetLogFiles(grpc::ServerContext *context, const recovery::GetLogFilesRequest *request, recovery::LogFiles *response)
{
    std::cout << "Received GetLogFiles request" << std::endl;
    // Extract the log line numbers from the request
    const google::protobuf::RepeatedField<int64_t> log_line_numbers = request->log_number();
    for (auto &log_line_number : log_line_numbers)
    {
        std::cout << "Log line number in protobuf: " << log_line_number << std::endl;
    }
    std::vector<int64_t> log_line_numbers_vector(log_line_numbers.begin(), log_line_numbers.end());
    for (auto &log_line_number : log_line_numbers_vector)
    {
        std::cout << "Log line number: " << log_line_number << std::endl;
    }
    std::map<std::string, std::string> logs = Tablet_Manager::get_instance().get_logs(log_line_numbers_vector);
    // add all the log files in the response
    for (auto &log : logs)
    {
        recovery::Log_File *log_file = response->add_log_files();
        log_file->set_content(log.second);
        log_file->set_file_name(log.first);
        std::cout << "Added log file: " << log.first << std::endl;
    }
    // return OK status
    return grpc::Status::OK;
}

grpc::Status RecoveryServiceImpl::GetCheckpointFiles(grpc::ServerContext *context, const recovery::CheckpointFilesRequest *request, recovery::CheckpointFilesResponse *response)
{
    std::cout << "Received GetCheckpointFiles request" << std::endl;
    std::string caller_address = request->address();
    std::cout << "Caller address: " << caller_address << std::endl;
    // call the function that will iteratively send checkpoint chunks to recvering node of caller_address
    bool status = recovery_controller_.send_chunked_checkpoint_files(caller_address);

    if (status)
    {
        std::cout << "Successfully sent checkpoints." << std::endl;
        response->set_ack(true);
        return grpc::Status::OK;
    }
    else
    {
        std::cout << "Failed to send checkpoints." << std::endl;
        response->set_ack(false);
        return grpc::Status(grpc::StatusCode::INTERNAL, "Failed to send checkpoint files.");
    }
}

grpc::Status RecoveryServiceImpl::SendCheckpointChunk(grpc::ServerContext *context, const recovery::FileChunk *request, recovery::CheckpointChunkResponse *response)
{
    std::cout << "Received Chunk from Primary Node" << std::endl;
    // Extract the content of the checkpoint chunk
    std::string chunk_content = request->content();
    std::string filename = request->filename();
    bool is_final_chunk = request->is_final_chunk();
    int tablet_id = request->tablet_id();
    std::string starting_range = request->starting_range();
    // call the function that will recover the checkpoint chunk
    recovery_controller_.recover_with_checkpoint_chunks(chunk_content, filename, tablet_id, is_final_chunk, starting_range);

    return grpc::Status::OK;
}

/*
// Stream all of the checkpoint files to the client
grpc::Status RecoveryServiceImpl::StreamCheckpoint(grpc::ServerContext *context, const recovery::StreamCheckpointRequest *request, grpc::ServerWriter<recovery::FileChunk> *writer)
{
    std::cout << "Received StreamCheckpoint request" << std::endl;
    namespace fs = std::filesystem;
    std::string folder_path = Tablet_Manager::get_instance().get_server_path() + "/tablets/";
    try
    {
        for (const auto &entry : fs::directory_iterator(folder_path))
        {
            std::ifstream file(entry.path(), std::ios::binary);

            if (!file.is_open())
            {
                return grpc::Status(grpc::StatusCode::INTERNAL, "Error opening file");
            }

            // setup buffer for streaming file
            const size_t buffer_size = 1024 * 1024;
            char buffer[buffer_size];

            bool is_final_chunk = false;
            std::string filename = entry.path().filename().string();

            while (!is_final_chunk)
            {
                file.read(buffer, buffer_size);
                std::streamsize read_size = file.gcount();
                if (read_size < buffer_size)
                    is_final_chunk = true;

                // setup FileChunk object for streaming
                recovery::FileChunk chunk;
                std::cout << "setting chunk content to: " << buffer << std::endl;
                chunk.set_content(buffer, read_size);
                chunk.set_is_final_chunk(is_final_chunk);
                chunk.set_filename(filename);
                // write chunk to stream
                writer->Write(chunk);
            }
            // close the file after streaming all chunks in file
            file.close();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return grpc::Status(grpc::StatusCode::INTERNAL, "Error reading files");
    }

    return grpc::Status::OK;
}
*/

grpc::Status RecoveryServiceImpl::NotifyRecoveryComplete(grpc::ServerContext *context, const recovery::RecoveryCompleteRequest *request, recovery::RecoveryCompleteResponse *response)
{
    // set is recovering to false:
    std::cout << "Received NotifyRecoveryComplete request" << std::endl;
    recovery_controller_.set_is_recovering(false);
    return grpc::Status::OK;
}
