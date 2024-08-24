// BackendMasterController.h

#include <grpc++/grpc++.h>
#include "frontend_backend_master.grpc.pb.h"

class BackendMasterController {
private:
    struct FrontendServerInfo {
        std::string address; // Address used to communicate with the frontend server
        // Additional info like last update timestamp, credentials, etc.
    };

    std::vector<FrontendServerInfo> registeredFrontendServers;
    std::mutex registryMutex; // To protect access to registeredFrontendServers

public:
    // Method to add frontend servers to the registry
    void RegisterFrontendServer(const std::string& address);

    // Method to notify all registered frontend servers about node updates
    void NotifyFrontendServers(const penncloud::frontend::NodeUpdate& update);
};

// Implementation details for registering and notifying frontend servers...
