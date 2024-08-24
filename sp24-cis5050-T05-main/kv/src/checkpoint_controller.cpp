#include "../include/checkpoint_controller.hpp"
#include "../include/tablet_manager.hpp"

Checkpoint_Controller::Checkpoint_Controller(const std::string &server_address,
                                             const std::string &primary_address,
                                             const std::unordered_map<std::string, std::shared_ptr<grpc::Channel>> &channels,
                                             int max_write_count) : is_primary_(server_address == primary_address), primary_node_address_(primary_address), server_address_(server_address), channels_(channels), replication_coordinator_(nullptr), write_count_(0), checkpoint_version_number_(1), is_checkpointing_(false), max_write_count_(max_write_count)
{
    // load the checkpoint version number from filename upon server restart
    checkpoint_version_number_ = Tablet_Manager::get_instance().get_checkpoint_version_number();

    // setup the client stub for the checkpoint service
    /*if (!is_primary())
    {
        auto channel = channels_[primary_node_address_];
        primary_stub_ = checkpoint::CheckpointService::NewStub(channel);
    }*/
    // create the stubs for all other nodes
    for (const auto &channel : channels_)
    {
        // skip its own address in stub setup
        if (channel.first == server_address)
            continue;
        stubs_[channel.first] = checkpoint::CheckpointService::NewStub(channel.second);
    }
}

Checkpoint_Controller::~Checkpoint_Controller()
{
}

// done by primary node
void Checkpoint_Controller::init_checkpointing()
{
    std::cout << "Initiating checkpointing" << std::endl;
    // TODO: send checkpoint message to itself and only then start checkpointing
    // get new checkpoint number:
    update_checkpoint_number();
    // start checkpointing:
    Tablet_Manager &tablet_manager = Tablet_Manager::get_instance();
    tablet_manager.start_checkpointing(checkpoint_version_number_);
    // set is checkpointing to true
    set_checkpointing(true);
    // and call multicast_checkpoint
    multicast_checkpoint();
}
bool Checkpoint_Controller::multicast_checkpoint()
{
    // loop over all other nodes and forward the checkpoint to them
    for (const auto &stub : stubs_)
    {
        // ignore inactive nodes
        if (!Status_Manager::GetInstance().is_active(stub.first))
        {
            std::cout << "Ignoring node: " << stub.first << " as it is down." << std::endl;
            continue;
        }
        // declare response and request and context objects
        checkpoint::StartCheckpointingResponse response;
        grpc::ClientContext context;
        checkpoint::StartCheckpointingRequest request;
        request.set_checkpoint_version(checkpoint_version_number_);
        // Wait for all nodes to respond with a success message (ACK)
        if (!stub.second->StartCheckpointing(&context, request, &response).ok())
        {
            // TODO: handle failure -> Check with BE-Master if node is alive
            // if any node fails to respond with a success message, return false
            return false;
        }
    }
    // If all nodes respond with a success message, call complete_checkpointing
    complete_checkpointing();
    return true;
}
void Checkpoint_Controller::complete_checkpointing()
{
    // tell the other nodes that the checkpoint is complete
    for (const auto &stub : stubs_)
    {
        if (!Status_Manager::GetInstance().is_active(stub.first))
        {
            std::cout << "Ignoring node: " << stub.first << " as it is down." << std::endl;
            continue;
        }
        checkpoint::CompleteCheckpointResponse response;
        grpc::ClientContext context;
        checkpoint::CompleteCheckpointRequest request;
        stub.second->CompleteCheckpoint(&context, request, &response);
    }
    // reset the write count to 0
    write_count_ = 0;
    // set is_checkpointing to false
    set_checkpointing(false);
}

// done by secondary nodes
bool Checkpoint_Controller::start_checkpointing(int64_t &checkpoint_version_number)
{
    // start checkpointing
    Tablet_Manager &tablet_manager = Tablet_Manager::get_instance();
    tablet_manager.start_checkpointing(checkpoint_version_number);
    checkpoint_version_number_ = checkpoint_version_number;
    // set is checkpointing to true
    set_checkpointing(true);
    // return true if successful
    return true;
}
// same as complete_checkpointing but triggered by RPC call from primary and doesn't send any more RPC calls
bool Checkpoint_Controller::secondary_complete_checkpointing(int64_t &checkpoint_version_number)
{
    // set write_count_ to 0
    write_count_ = 0;
    // set is_checkpointing to false
    set_checkpointing(false);
    // return true if successful
    return true;
}

// setters
void Checkpoint_Controller::set_checkpointing(bool is_checkpointing)
{
    is_checkpointing_ = is_checkpointing;
}
// getters
bool Checkpoint_Controller::is_checkpointing()
{
    return is_checkpointing_;
}

void Checkpoint_Controller::update_checkpoint_number()
{
    std::lock_guard<std::mutex> lock(checkpoint_version_number_mutex_);
    checkpoint_version_number_ += 1;
}

void Checkpoint_Controller::set_replication_coordinator(Replication_Coordinator *replication_coordinator)
{
    replication_coordinator_ = replication_coordinator;
}

bool Checkpoint_Controller::is_primary()
{
    return is_primary_;
}

void Checkpoint_Controller::increase_write_count()
{
    std::lock_guard<std::mutex> lock(write_count_mutex_);
    write_count_++;
    std::cout << "Write count: " << write_count_ << std::endl;
    std::cout << "Max write count until checkpoint: " << max_write_count_ << std::endl;
    // if write count is greater than max_write_count_ and node is the primary, start the checkpointing process
    if (write_count_ >= max_write_count_ && Status_Manager::GetInstance().get_primary_address() == server_address_)
    {
        init_checkpointing();
    }
}