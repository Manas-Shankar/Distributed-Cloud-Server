#include "../include/ServiceManager.hpp"
#include "../include/tablet_manager.hpp"
#include "../include/checkpoint_controller.hpp"
#include "../include/replication_coordinator.hpp"
#include "../include/kv_service_impl.hpp"
#include "../include/replication_service_impl.hpp"
#include "../include/checkpoint_service_impl.hpp"
#include "../include/status_manager.hpp"
#include "../include/recovery_controller.hpp"
#include "../include/recovery_service_impl.hpp"
#include "../include/kv_admin_service_impl.hpp"

#include <chrono>
#include <thread>
#include <iostream>

ServiceManager &ServiceManager::GetInstance()
{
    static ServiceManager instance;
    return instance;
}

ServiceManager::ServiceManager() {}

void ServiceManager::Initialize(const int &server_num, const int &group_num, const int &max_write, std::string &address, const std::vector<std::string> &addresses, std::string &daemon_address)
{
    server_number = server_num;
    group_number = group_num;
    max_write_count = max_write;
    node_address = address;
    server_addresses_ = addresses;
    daemon_address_ = daemon_address;
}

void ServiceManager::StartServices()
{
    Tablet_Manager &manager = Tablet_Manager::get_instance();
    std::cout << "Initializing tablet manager. Group number: " << group_number
              << ", server number: " << server_number << std::endl;
    manager.initialize(group_number, server_number);

    Status_Manager::GetInstance().set_current_address(daemon_address_);

    while (Status_Manager::GetInstance().get_primary_address().empty())
    {
        std::cout << "Waiting for primary address to be set..." << std::endl;
        // TODO: fetch primary from Backend and set it in Status_Manager

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::string primary_address = Status_Manager::GetInstance().get_primary_address();
    std::cout << "Primary address: " << primary_address << std::endl;

    for (const auto &address : server_addresses_)
    {
        channels[address] = grpc::CreateChannel(address, grpc::InsecureChannelCredentials());
    }

    Checkpoint_Controller checkpoint_controller(node_address, primary_address, channels, max_write_count);
    Recovery_Controller recovery_controller(node_address, primary_address, channels);
    Replication_Coordinator replication_coordinator(node_address, primary_address, channels, checkpoint_controller, recovery_controller);
    checkpoint_controller.set_replication_coordinator(&replication_coordinator);

    builder = std::make_unique<grpc::ServerBuilder>();
    std::cout << "Adding listening port at Server address:" << node_address << std::endl;
    builder->AddListeningPort(node_address, grpc::InsecureServerCredentials());

    KeyValueServiceImpl kv_service(replication_coordinator);
    ReplicationServiceImpl replication_service(replication_coordinator, checkpoint_controller);
    CheckpointServiceImpl checkpoint_service(checkpoint_controller);
    RecoveryServiceImpl recovery_service(recovery_controller);
    AdminKVServiceImpl admin_kv_service;

    builder->RegisterService(&kv_service);
    builder->RegisterService(&replication_service);
    builder->RegisterService(&checkpoint_service);
    builder->RegisterService(&recovery_service);
    builder->RegisterService(&admin_kv_service);

    server = builder->BuildAndStart();
    // if node isn't the primary node, start the recovery process
    if (primary_address != node_address)
    {
        recovery_controller.start_recovery();
    }
    std::cout << "Server listening on " << node_address << std::endl;
    server->Wait();
}

void ServiceManager::ShutdownServices()
{
    if (server)
    {
        server->Shutdown();
        server->Wait();
    }
    Status_Manager::GetInstance().set_primary_address("");
    Status_Manager::GetInstance().set_all_nodes_inactive();
    Status_Manager::GetInstance().reset_self_active();
    channels.clear();
    server.reset();
    builder.reset();
}
