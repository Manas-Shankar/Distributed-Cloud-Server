// BackendMasterServerImpl.hpp

#ifndef BACKEND_MASTER_SERVER_IMPL_HPP
#define BACKEND_MASTER_SERVER_IMPL_HPP

#include "backend_master_as_server.grpc.pb.h" // Ensure this includes the correct .grpc.pb.h file generated from the .proto
#include <grpcpp/grpcpp.h>
#include <unordered_map>
#include <mutex>
#include <string>

#include "node_status_manager.hpp"

// gRPC service implementation for backend master server
class BackendMasterServerImpl final : public backendmaster::BackendMasterService::Service
{

private:
    int group_;
    std::set<std::string> group1Addresses{
        "127.0.0.1:5050", "127.0.0.1:5051", "127.0.0.1:5052",
        "127.0.0.1:5053", "127.0.0.1:5054", "127.0.0.1:5055"
    };
    std::set<std::string> group2Addresses{
        "127.0.0.1:5057", "127.0.0.1:5058", "127.0.0.1:5059",
        "127.0.0.1:5060", "127.0.0.1:5061", "127.0.0.1:5062"
    };
    // std::unordered_map<std::string, std::string> nodeStatuses;
    std::mutex mutex_;

public:
    grpc::Status NotifyRecovery(grpc::ServerContext *context,
                                const backendmaster::NotifyRecoveryRequest *request,
                                backendmaster::NotifyRecoveryResponse *response) override;

    grpc::Status GetPrimary(grpc::ServerContext *context,
                            const backendmaster::PrimaryRequest *request,
                            backendmaster::PrimaryNode *response) override;

    grpc::Status ListNodes(grpc::ServerContext *context, const backendmaster::ListNodesRequest *request,
                           backendmaster::NodesList *response) override;

    grpc::Status GetNodeAddress(grpc::ServerContext* context, const backendmaster::GetNodeAddressRequest* request,
                              backendmaster::GetNodeAddressResponse* response) override;
    INodeStatusManager& get_status_manager();
    void setGroup(int g) {group_ = g;}
    int getGroup(const std::string& nodeAddress);
};

#endif // BACKEND_MASTER_SERVER_IMPL_HPP
