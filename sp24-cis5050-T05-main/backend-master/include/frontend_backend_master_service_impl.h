#ifndef FRONTEND_BACKEND_MASTER_SERVICE_IMPL_H
#define FRONTEND_BACKEND_MASTER_SERVICE_IMPL_H

#include "frontend_backend_master.grpc.pb.h"

class FrontendBackendMasterServiceImpl final : public penncloud::frontend::FrontendBackendMasterService::Service {
public:
    grpc::Status RegisterFrontend(grpc::ServerContext* context, const penncloud::frontend::Empty* request, penncloud::frontend::Acknowledgment* response) override;

    // Additional methods for handling node updates to frontend servers
};

#endif // FRONTEND_BACKEND_MASTER_SERVICE_IMPL_H
