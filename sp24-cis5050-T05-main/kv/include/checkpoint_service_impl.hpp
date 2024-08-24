
#ifndef CHECKPOINT_SERVICE_IMPL_HPP
#define CHECKPOINT_SERVICE_IMPL_HPP

#include "../grpc_proto/checkpoint.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include "checkpoint_controller.hpp"

// Inheriting from the generated CheckpointService::Service class from checkpoint.grpc.pb.h
class CheckpointServiceImpl final : public checkpoint::CheckpointService::Service
{
public:
    CheckpointServiceImpl(Checkpoint_Controller &checkpoint_controller);
    grpc::Status StartCheckpointing(grpc::ServerContext *context,
                                    const checkpoint::StartCheckpointingRequest *request,
                                    checkpoint::StartCheckpointingResponse *response) override;

    grpc::Status CompleteCheckpoint(grpc::ServerContext *context,
                                    const checkpoint::CompleteCheckpointRequest *request,
                                    checkpoint::CompleteCheckpointResponse *response) override;

private:
    Checkpoint_Controller &checkpoint_controller_;
};

#endif // CHECKPOINT_SERVICE_IMPL_HPP