#ifndef STATUS_MANAGER_HPP
#define STATUS_MANAGER_HPP

#include <string>
#include <unordered_map>
#include <grpcpp/grpcpp.h>
#include "../grpc_proto/backend_master_as_server.grpc.pb.h"
// #include "../grpc_proto/backend_master_kv.grpc.pb.h" // GRPC auto-generated header for backend master

class Status_Manager
{
public:
    static Status_Manager &GetInstance();

    Status_Manager(const Status_Manager &) = delete;            // Delete copy constructor
    Status_Manager &operator=(const Status_Manager &) = delete; // Delete copy assignment operator

    bool is_active(const std::string &address);
    void set_primary_address(const std::string &address);
    std::string get_primary_address();
    void set_to_recovered();

    std::vector<std::string> get_all_node_addresses();
    void set_all_nodes_inactive();
    void update_active_node(const std::string &node, bool status);

    void set_self_active() { is_active_ = true; }
    void reset_self_active() { is_active_ = false; }
    bool get_self_active() { return is_active_; }

    void set_current_address(std::string &addr) { current_node_address_ = addr; };
    std::string get_recovery_status() { return recovery_status_; };

private:
    Status_Manager(); // Private constructor
    bool fetch_primary_address();
    bool send_recovery_notification();

    std::string primary_address_ = "";
    std::unordered_map<std::string, bool> active_nodes_;
    std::string recovery_status_;
    bool is_active_;
    std::unique_ptr<backendmaster::BackendMasterService::Stub> be_master_stub_;
    std::unique_ptr<backendmaster::BackendMasterService::Stub> notify_be_master_stub_;
    std::string current_node_address_;
    std::unordered_map<std::string, std::string> node_addresses_to_daemon_addresses_map_;

    std::mutex map_mutex;
};

#endif
