#include "../include/KVNodeLifecycleServiceImpl.hpp"
#include <iostream>
#include <vector>
#include <thread>
#include "../include/status_manager.hpp" // Make sure this path is correct
#include "../include/ServiceManager.hpp"

extern std::atomic<bool> shutdown_flag;
extern std::vector<std::thread> worker_threads;

grpc::Status KVNodeLifecycleServiceImpl::Shutdown(grpc::ServerContext *context, const kvstore::ShutdownRequest *request, kvstore::ShutdownResponse *response)
{
    shutdown_flag.store(true);
    ServiceManager::GetInstance().ShutdownServices();
    // Status_Manager::GetInstance().set_to_recovered(false); // Assuming this takes a parameter now
    return grpc::Status::OK;
}

grpc::Status KVNodeLifecycleServiceImpl::Restart(grpc::ServerContext *context, const kvstore::RestartRequest *request, kvstore::RestartResponse *response)
{
    if (!shutdown_flag.load())
    {
        ServiceManager::GetInstance().StartServices();
    }
    shutdown_flag.store(false);
    return grpc::Status::OK;
}

grpc::Status KVNodeLifecycleServiceImpl::CheckNodeHealth(grpc::ServerContext *context, const kvstore::HealthCheckRequest *request, kvstore::HealthCheckResponse *response)
{
    response->set_ishealthy(!shutdown_flag.load());
    response->set_recovery_status(Status_Manager::GetInstance().get_recovery_status());
    return grpc::Status::OK;
}

grpc::Status KVNodeLifecycleServiceImpl::SetPrimary(grpc::ServerContext *context, const kvstore::SetPrimaryRequest *request, kvstore::SetPrimaryResponse *response)
{
    Status_Manager::GetInstance().set_primary_address(request->primaryaddress());
    return grpc::Status::OK;
}

grpc::Status KVNodeLifecycleServiceImpl::ActiveNodes(grpc::ServerContext *context, const kvstore::ActiveNodesRequest *request, kvstore::ActiveNodesResponse *response)
{
    // std::cout << "Received active nodes request." << std::endl;
    Status_Manager &manager = Status_Manager::GetInstance();
    manager.set_all_nodes_inactive();
    for (const auto &node : request->nodeaddresses())
    {
        // std::cout << "Setting node " << node << " to active." << std::endl;
        manager.update_active_node(node, true);
    }
    return grpc::Status::OK;
}
