#include "../include/checkpoint_service_impl.hpp"

CheckpointServiceImpl::CheckpointServiceImpl(Checkpoint_Controller &checkpoint_controller) : checkpoint_controller_(checkpoint_controller) {}

grpc::Status CheckpointServiceImpl::StartCheckpointing(grpc::ServerContext *context,
                                                       const checkpoint::StartCheckpointingRequest *request,
                                                       checkpoint::StartCheckpointingResponse *response)
{
    // Start the checkpointing process
    std::cout << "Starting checkpointing process." << std::endl;
    int64_t checkpoint_version_number = request->checkpoint_version();
    // call the checkpointint controller to start the checkpointing process
    bool result = checkpoint_controller_.start_checkpointing(checkpoint_version_number);
    response->set_ack(result);
    if (!result)
    {
        return grpc::Status(grpc::StatusCode::INTERNAL, "Start checkpointing failed.");
    }
    return grpc::Status::OK;
}

grpc::Status CheckpointServiceImpl::CompleteCheckpoint(grpc::ServerContext *context,
                                                       const checkpoint::CompleteCheckpointRequest *request,
                                                       checkpoint::CompleteCheckpointResponse *response)
{
    // Complete the checkpointing process
    std::cout << "Complete checkpointing process" << std::endl;
    // call the checkpointing controller set is_checkpointing to false
    int64_t checkpoint_version = request->checkpoint_version();
    bool result = checkpoint_controller_.secondary_complete_checkpointing(checkpoint_version);
    if (result)
    {
        return grpc::Status::OK;
    }
    return grpc::Status(grpc::StatusCode::INTERNAL, "Complete checkpointing failed.");
    ;
}