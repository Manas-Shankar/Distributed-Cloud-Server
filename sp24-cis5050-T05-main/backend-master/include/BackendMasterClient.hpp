#ifndef BACKEND_MASTER_CLIENT_HPP
#define BACKEND_MASTER_CLIENT_HPP

#include "node_status_manager.hpp"

#include <string>
#include <unordered_map>
#include <memory>
#include <grpcpp/grpcpp.h>
#include "kv_lifecycle.grpc.pb.h"  // Include the gRPC-generated header for the KV lifecycle service

class BackendMasterClient {
public:
    // Constructor and Destructor
    explicit BackendMasterClient(const std::vector<std::string>& daemonAddresses, const std::vector<std::string>& serverAddresses, int group);
    ~BackendMasterClient();

    // Public methods to send gRPC requests
    void sendShutdown(const std::string& address);
    void sendRestart(const std::string& address);
    void sendSetPrimary(const std::string& address);
    void checkNodeHealth(const std::string& address);
    void processNotifyRecovered(const std::string& address);
    void sendActiveNodes();

    void updateActiveAddressSet();
    void takeSnapShot();
    bool anyUpdates() {return activeAddressSet != activeAddressSnap;}
    void checkAndSetPrimary();

    INodeStatusManager& get_status_manager() {
        if (group_ == 1) {
            return NodeStatusManager1::GetInstance();
        } else if (group_ == 2) {
            return NodeStatusManager2::GetInstance();
        } else {
            throw std::runtime_error("Invalid group number");
        }
    }

    std::vector<std::string> getDaemonAddresses( ){return daemonAddresses_;}

    

private:
    bool noActivePrimary();
    bool noAvailablePrimary();
    void setNewPrimary();
    void sendSetPrimaryAll();

    int group_;

    // Helper method to initialize the gRPC stubs for communicating with KV nodes
    void initStubs(const std::vector<std::string>& daemonAddresses);
    
    std::string primary_address_ = "";
    // Member variables
    std::unordered_map<std::string, std::unique_ptr<kvstore::KVNodeLifecycle::Stub>> stubs;
    // std::unordered_map<std::string, std::string> nodeStatuses; // Maps node addresses to their current status

    std::set<std::string> activeAddressSet;
    std::set<std::string> activeAddressSnap;

    std::unordered_map<std::string, std::string> daemonMapToServer;
    std::vector<std::string> daemonAddresses_;
};

#endif // BACKEND_MASTER_CLIENT_HPP
