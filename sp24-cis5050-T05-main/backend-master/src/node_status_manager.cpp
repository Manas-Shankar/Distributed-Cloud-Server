#include <iostream>
#include <random>
#include <ctime>
#include "node_status_manager.hpp"

void NodeStatusManager1::SetNodeStatus(const std::string &nodeAddress, const std::string &status)
{
    std::lock_guard<std::mutex> lock(mutex_);
    std::cout << "Setting status of node " << nodeAddress << " to " << status << std::endl;
    nodeStatuses[nodeAddress] = status;
}

std::string NodeStatusManager1::GetNodeStatus(const std::string &nodeAddress)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = nodeStatuses.find(nodeAddress);
    if (it != nodeStatuses.end())
    {
        return it->second;
    }
    return "Unknown";
}

std::unordered_map<std::string, std::string> NodeStatusManager1::GetAllStatuses()
{
    std::lock_guard<std::mutex> lock(mutex_);
    return nodeStatuses;
}

bool NodeStatusManager1::isIn(const std::string &nodeAddress)
{
    return nodeStatuses.find(nodeAddress) != nodeStatuses.end();
}

std::string NodeStatusManager1::getServerFromDaemon(std::string &addr)
{
    if (daemonMapToServer_.find(addr) == daemonMapToServer_.end())
    {
        // std::cout<<"\nInvalid address\n";
        return addr;
    }
    return daemonMapToServer_[addr];
}

void NodeStatusManager1::showAllNodes()
{
    for (const auto &pair : nodeStatuses)
    {
        std::cout << pair.first << ":" << pair.second << std::endl;
    }
};

void NodeStatusManager1::SetPrimary(const std::string& address) {
    std::lock_guard<std::mutex> lock(mutex_);
    primary_address_ = address;
}

void NodeStatusManager1::setUpMap(std::unordered_map<std::string, std::string>& map) {
    std::lock_guard<std::mutex> lock(mutex_);
    daemonMapToServer_ = map;
}

std::string NodeStatusManager1::GetPrimary() {
    return primary_address_;
}

std::string NodeStatusManager1::GetRandomActiveNode() {
    std::vector<std::string> activeNodes;

    // Collect all active nodes
    for (const auto& node : nodeStatuses) {
        if (node.second == "active") {
            activeNodes.push_back(node.first);
        }
    }

    // Check if there are any active nodes
    if (activeNodes.empty()) {
        return "No active nodes available.";
    }

    // Generate a random index to select a node
    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr))); // random-number engine (seeded with time)
    std::uniform_int_distribution<int> dist(0, static_cast<int>(activeNodes.size()) - 1);
    int randomIndex = dist(rng);

    // Return a random active node
    return activeNodes[randomIndex];
}