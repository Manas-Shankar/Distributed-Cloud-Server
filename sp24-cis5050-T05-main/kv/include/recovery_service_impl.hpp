#ifndef RECOVERY_SERVICE_IMPL_HPP
#define RECOVERY_SERVICE_IMPL_HPP

#include "../grpc_proto/recovery.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include "recovery_controller.hpp"
#include "tablet_manager.hpp"

class RecoveryServiceImpl final : public recovery::RecoveryService::Service
{
public:
    RecoveryServiceImpl(Recovery_Controller &recovery_controller);
    grpc::Status StartRecovery(grpc::ServerContext *context, const recovery::StartRecoveryRequest *request, recovery::StartRecoveryResponse *response) override;
    grpc::Status GetLogFiles(grpc::ServerContext *context, const recovery::GetLogFilesRequest *request, recovery::LogFiles *response) override;
    grpc::Status GetCheckpointFiles(grpc::ServerContext *context, const recovery::CheckpointFilesRequest *request, recovery::CheckpointFilesResponse *response) override;
    grpc::Status SendCheckpointChunk(grpc::ServerContext *context, const recovery::FileChunk *request, recovery::CheckpointChunkResponse *response) override;
    // grpc::Status StreamCheckpoint(grpc::ServerContext *context, const recovery::StreamCheckpointRequest *request, grpc::ServerWriter<recovery::FileChunk> *writer) override;
    grpc::Status NotifyRecoveryComplete(grpc::ServerContext *context, const recovery::RecoveryCompleteRequest *request, recovery::RecoveryCompleteResponse *response) override;

private:
    Recovery_Controller &recovery_controller_;
};

#endif // RECOVERY_SERVICE_IMPL_HPP

/*
 // get log files from primary
    rpc GetLogFiles(GetLogFilesRequest) returns (LogFiles);

    // stream tablet (checkpoint) files from primary
    rpc StreamCheckpoint(StreamCheckpointRequest) returns (stream FileChunk);

    // notify other nodes the checkpointing is complete
    rpc NotifyRecoveryComplete(RecoveryCompleteRequest) returns (RecoveryCompleteResponse);
*/