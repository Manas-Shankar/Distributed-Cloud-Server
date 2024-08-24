// BackendMasterController.cpp

#include "BackendMasterController.h"

void BackendMasterController::RegisterFrontendServer(const std::string& address) {
    std::lock_guard<std::mutex> lock(registryMutex);
    registeredFrontendServers.push_back(FrontendServerInfo{address});
}

void BackendMasterController::NotifyFrontendServers(const penncloud::frontend::NodeUpdate& update) {
    std::lock_guard<std::mutex> lock(registryMutex);
    for (const auto& frontend : registeredFrontendServers) {
        auto channel = grpc::CreateChannel(frontend.address, grpc::InsecureChannelCredentials());
        auto stub = penncloud::frontend::FrontendBackendMasterService::NewStub(channel);

        grpc::ClientContext context;
        penncloud::frontend::Acknowledgment ack;
        grpc::Status status = stub->ReceiveNodeUpdate(&context, update, &ack);

        if (!status.ok()) {
            std::cerr << "Error notifying frontend server at " << frontend.address << std::endl;
            // Handle the error accordingly
        }
    }
}
