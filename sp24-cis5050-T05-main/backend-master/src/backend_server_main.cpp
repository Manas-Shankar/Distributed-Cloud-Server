#include <grpc++/grpc++.h>
#include "frontend_backend_master_service_impl.h"
#include "backend_master_kv_service_impl.h"
#include "BackendMasterController.h" // Include the controller header

// Define a global or singleton instance of BackendMasterController
// (Consider appropriate design patterns for initialization and access)
BackendMasterController backendMasterController;

void RunServer() {
    std::string serverAddress("0.0.0.0:50051");
    FrontendBackendMasterServiceImpl frontendService;
    BackendMasterKVServiceImpl backendService;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());
    
    // Register your services with the builder
    builder.RegisterService(&frontendService);
    builder.RegisterService(&backendService);

    // The rest of your server setup remains the same
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << serverAddress << std::endl;

    // Example: Trigger an update to all frontend servers (this should be event-driven in practice)
    // This is just to illustrate the invocation; you'd likely call this elsewhere in response to specific events
    penncloud::frontend::NodeUpdate exampleUpdate; // Populate this with actual update data
    backendMasterController.NotifyFrontendServers(exampleUpdate);

    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
}
