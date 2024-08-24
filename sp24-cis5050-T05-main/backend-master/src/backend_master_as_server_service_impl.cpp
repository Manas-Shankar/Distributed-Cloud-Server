// BackendMasterServerImpl.cpp

#include "backend_master_as_server_service_impl.hpp"
#include <iostream>

grpc::Status BackendMasterServerImpl::NotifyRecovery(
    grpc::ServerContext *context,
    const backendmaster::NotifyRecoveryRequest *request,
    backendmaster::NotifyRecoveryResponse *response)
{
    std::cout << "Received recovery notification from node " << request->node_address() << std::endl;
    // std::lock_guard<std::mutex> lock(mutex_);
    const std::string &nodeAddress = request->node_address();
    int group = getGroup(nodeAddress);
    setGroup(group);

    // Check if the node address exists in the map
    
    bool found = get_status_manager().isIn(nodeAddress);
    if (!found)
    {
        // NodeStatusManager::GetInstance().SetNodeStatus(nodeAddress, "active");
        response->set_message("Node address not found in status map: " + nodeAddress);
        std::cerr << "Error: Node address not found in status map: " << nodeAddress << std::endl;
        return grpc::Status(grpc::StatusCode::NOT_FOUND, "Node address not found in status map.");
    }
    get_status_manager().SetNodeStatus(nodeAddress, "active");
    // Optionally, populate response if it has fields that need to be returned
    response->set_message("Recovery processed for node " + nodeAddress);

    return grpc::Status::OK;
}

grpc::Status BackendMasterServerImpl::GetPrimary(
    grpc::ServerContext *context,
    const backendmaster::PrimaryRequest *request,
    backendmaster::PrimaryNode *response)
{
    const std::string &nodeAddress = request->caller_address();
    int group = getGroup(nodeAddress);
    setGroup(group);
    std::lock_guard<std::mutex> lock(mutex_);
    std::string address = get_status_manager().GetPrimary();
    std::string server_address = get_status_manager().getServerFromDaemon(address);
    if (!response)
    {
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Response pointer is null");
    }
    response->set_primary_address(server_address);

    return grpc::Status::OK;
}

grpc::Status BackendMasterServerImpl::ListNodes(grpc::ServerContext *context, const backendmaster::ListNodesRequest *request,
                                                backendmaster::NodesList *response)
{

    std::unordered_map<std::string, std::string> nodeStatuses1 = NodeStatusManager1::GetInstance().GetAllStatuses();
    std::unordered_map<std::string, std::string> nodeStatuses2 = NodeStatusManager2::GetInstance().GetAllStatuses();

    for (const auto &node : nodeStatuses1)
    {
        backendmaster::Node *node_item = response->add_nodes();
        node_item->set_address(node.first);
        node_item->set_status(node.second);
        // TODO: Set group number based on actual group
        node_item->set_group(1);
    }
    for (const auto &node : nodeStatuses2)
    {
        backendmaster::Node *node_item = response->add_nodes();
        node_item->set_address(node.first);
        node_item->set_status(node.second);
        // TODO: Set group number based on actual group
        node_item->set_group(2);
    }
    return grpc::Status::OK;
}

int BackendMasterServerImpl::getGroup(const std::string& nodeAddress) {
    if (group1Addresses.find(nodeAddress) != group1Addresses.end()) {
        return 1;
    } else if (group2Addresses.find(nodeAddress) != group2Addresses.end()) {
        return 2;
    }
    return -1; // 
}

INodeStatusManager& BackendMasterServerImpl::get_status_manager() {
    if (group_ == 1) {
        return NodeStatusManager1::GetInstance();
    } else if (group_ == 2) {
        return NodeStatusManager2::GetInstance();
    } else {
        throw std::runtime_error("Invalid group number");
    }
}


grpc::Status BackendMasterServerImpl::GetNodeAddress(grpc::ServerContext* context, const backendmaster::GetNodeAddressRequest* request,
                              backendmaster::GetNodeAddressResponse* response) {
    std::string key = request->key();
    char short_key = toupper(key[0]);
    if(short_key>='A' && short_key<='M') {
        setGroup(1);
    } else {
        setGroup(2);
    }
    std::string address = get_status_manager().GetRandomActiveNode();  // Implement this function based on your data storage
    
    if (address.empty()) {
      return grpc::Status(grpc::StatusCode::NOT_FOUND, "No address found for the provided key");
    }
    std::string server_address = get_status_manager().getServerFromDaemon(address);
    response->set_address(server_address);
    return grpc::Status::OK;
  }