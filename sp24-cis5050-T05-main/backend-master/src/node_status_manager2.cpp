#include <iostream>

#include "node_status_manager.hpp"

void NodeStatusManager2::SetNodeStatus(const std::string &nodeAddress, const std::string &status)
{
    std::lock_guard<std::mutex> lock(mutex_);
    std::cout << "Setting status of node " << nodeAddress << " to " << status << std::endl;
    nodeStatuses[nodeAddress] = status;
}

std::string NodeStatusManager2::GetNodeStatus(const std::string &nodeAddress)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = nodeStatuses.find(nodeAddress);
    if (it != nodeStatuses.end())
    {
        return it->second;
    }
    return "Unknown";
}

std::unordered_map<std::string, std::string> NodeStatusManager2::GetAllStatuses()
{
    std::lock_guard<std::mutex> lock(mutex_);
    return nodeStatuses;
}

bool NodeStatusManager2::isIn(const std::string &nodeAddress)
{
    return nodeStatuses.find(nodeAddress) != nodeStatuses.end();
}

std::string NodeStatusManager2::getServerFromDaemon(std::string &addr)
{
    if (daemonMapToServer_.find(addr) == daemonMapToServer_.end())
    {
        // std::cout<<"\nInvalid address\n";
        return addr;
    }
    return daemonMapToServer_[addr];
}

void NodeStatusManager2::showAllNodes()
{
    for (const auto &pair : nodeStatuses)
    {
        std::cout << pair.first << ":" << pair.second << std::endl;
    }
};

void NodeStatusManager2::SetPrimary(const std::string& address) {
    std::lock_guard<std::mutex> lock(mutex_);
    primary_address_ = address;
}

void NodeStatusManager2::setUpMap(std::unordered_map<std::string, std::string>& map) {
    std::lock_guard<std::mutex> lock(mutex_);
    daemonMapToServer_ = map;
}

std::string NodeStatusManager2::GetPrimary() {
    return primary_address_;
}

std::string NodeStatusManager2::GetRandomActiveNode() {
    return primary_address_;
}