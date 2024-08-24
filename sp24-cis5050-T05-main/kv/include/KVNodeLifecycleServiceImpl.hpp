#ifndef KV_NODE_LIFECYCLE_SERVICE_IMPL_H
#define KV_NODE_LIFECYCLE_SERVICE_IMPL_H

#include "../grpc_proto/kv_lifecycle.grpc.pb.h"

class KVNodeLifecycleServiceImpl final : public kvstore::KVNodeLifecycle::Service {
public:
    grpc::Status Shutdown(grpc::ServerContext* context, const kvstore::ShutdownRequest* request, kvstore::ShutdownResponse* response) override;
    grpc::Status Restart(grpc::ServerContext* context, const kvstore::RestartRequest* request, kvstore::RestartResponse* response) override;
    grpc::Status CheckNodeHealth(grpc::ServerContext* context, const kvstore::HealthCheckRequest* request, kvstore::HealthCheckResponse* response) override;
    grpc::Status SetPrimary(grpc::ServerContext* context, const kvstore::SetPrimaryRequest* request, kvstore::SetPrimaryResponse* response) override;
    grpc::Status ActiveNodes(grpc::ServerContext* context, const kvstore::ActiveNodesRequest* request, kvstore::ActiveNodesResponse* response) override;
};

#endif // KV_NODE_LIFECYCLE_SERVICE_IMPL_H
