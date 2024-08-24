#ifndef SERVICE_MANAGER_HPP
#define SERVICE_MANAGER_HPP

#include <grpcpp/grpcpp.h>
#include <string>
#include <unordered_map>

// Forward declarations for classes used in ServiceManager
class Checkpoint_Controller;
class Replication_Coordinator;
class KeyValueServiceImpl;
class ReplicationServiceImpl;
class CheckpointServiceImpl;
class Tablet_Manager;

class ServiceManager
{
public:
    static ServiceManager &GetInstance();

    void Initialize(const int &server_num, const int &group_num, const int &max_write, std::string &address, const std::vector<std::string> &addresses, std::string &daemon_address);
    void StartServices();
    void ShutdownServices();

private:
    ServiceManager();

    std::unique_ptr<grpc::Server> server;
    std::unique_ptr<grpc::ServerBuilder> builder;
    std::unordered_map<std::string, std::shared_ptr<grpc::Channel>> channels;

    int server_number;
    int group_number;
    int max_write_count;

    std::string node_address;
    std::vector<std::string> server_addresses_;
    std::string daemon_address_;
};

#endif // SERVICE_MANAGER_HPP
