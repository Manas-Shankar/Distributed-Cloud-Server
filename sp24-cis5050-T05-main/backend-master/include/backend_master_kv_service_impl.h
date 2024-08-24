#ifndef BACKEND_MASTER_KV_SERVICE_IMPL_H
#define BACKEND_MASTER_KV_SERVICE_IMPL_H

#include "backend_master_kv.grpc.pb.h"

class BackendMasterKVServiceImpl final : public penncloud::backend::BackendMasterKVService::Service {
public:
    grpc::Status CheckNodeHealth(grpc::ServerContext* context, const penncloud::backend::HealthCheckRequest* request, penncloud::backend::HealthCheckResponse* response) override;

    // Methods for backend node management
};

#endif // BACKEND_MASTER_KV_SERVICE_IMPL_H
