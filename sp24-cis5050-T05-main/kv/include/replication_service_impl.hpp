#ifndef REPLICATION_SERVICE_IMPL_HPP
#define REPLICATION_SERVICE_IMPL_HPP

#include "../grpc_proto/replication.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include "controller.hpp"
#include "replication_coordinator.hpp"
#include "checkpoint_controller.hpp"

class Replication_Coordinator;
class Checkpoint_Controller;

class ReplicationServiceImpl final : public replication::ReplicationService::Service
{
public:
    ReplicationServiceImpl(Replication_Coordinator &replication_coordinator, Checkpoint_Controller &checkpoint_controller);
    grpc::Status forwardTransaction(grpc::ServerContext *context, const replication::Transaction *request, replication::TransactionResponse *response) override;

private:
    KV_Controller controller_;
    Replication_Coordinator &replication_coordinator_;
    Checkpoint_Controller &checkpoint_controller_;
};

#endif // REPLICATION_SERVICE_IMPL_HPP
