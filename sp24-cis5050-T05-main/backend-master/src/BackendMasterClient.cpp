#include "BackendMasterClient.hpp"
#include <iostream>
#include <random>

BackendMasterClient::BackendMasterClient(const std::vector<std::string> &daemonAddresses, const std::vector<std::string> &serverAddresses, int group)
{
    daemonAddresses_ = daemonAddresses;
    group_ = group;
    initStubs(daemonAddresses);
    for (size_t i = 0; i < daemonAddresses.size(); ++i)
    {
        daemonMapToServer[daemonAddresses[i]] = serverAddresses[i];
    }
    get_status_manager().setUpMap(daemonMapToServer);
}

BackendMasterClient::~BackendMasterClient() {}

void BackendMasterClient::initStubs(const std::vector<std::string> &daemonAddresses)
{
    for (const auto &address : daemonAddresses)
    {
        auto channel = grpc::CreateChannel(address, grpc::InsecureChannelCredentials());
        stubs[address] = kvstore::KVNodeLifecycle::NewStub(channel);
        get_status_manager().SetNodeStatus(address, "active");
        // Initially all nodes are considered active
    }
}

void BackendMasterClient::sendShutdown(const std::string &address)
{
    if (get_status_manager().GetNodeStatus(address) == "inactive")
    {
        std::cout << "Node " << address << " is already inactive." << std::endl;
        return;
    }
    kvstore::ShutdownRequest request;
    grpc::ClientContext context;
    kvstore::ShutdownResponse response;
    grpc::Status status = stubs[address]->Shutdown(&context, request, &response);
}

void BackendMasterClient::sendRestart(const std::string &address)
{
    if (get_status_manager().GetNodeStatus(address) != "inactive")
    {
        std::cout << "Node " << address << " is already active." << std::endl;
        return;
    }
    kvstore::RestartRequest request;
    grpc::ClientContext context;
    kvstore::RestartResponse response;
    grpc::Status status = stubs[address]->Restart(&context, request, &response);
}

void BackendMasterClient::sendSetPrimary(const std::string &address)
{
    kvstore::SetPrimaryRequest request;
    std::string send_address;
    if (get_status_manager().GetPrimary() == "-1")
    {
        send_address = "-1";
    }
    else
    {
        send_address = daemonMapToServer[primary_address_];
    }
    request.set_primaryaddress(send_address);
    std::cout << "Sending primary(daemon) address\n";
    // request.set_primaryaddress(primary_address_);
    grpc::ClientContext context;
    kvstore::SetPrimaryResponse response;
    grpc::Status status = stubs[address]->SetPrimary(&context, request, &response);
}

bool BackendMasterClient::noActivePrimary()
{
    if (primary_address_.empty() || activeAddressSet.find(primary_address_) == activeAddressSet.end())
    {
        return true;
    }
    return false;
}

bool BackendMasterClient::noAvailablePrimary()
{
    return (activeAddressSet.size() == 0);
}

void BackendMasterClient::setNewPrimary()
{
    int num_addr = activeAddressSet.size();
    std::random_device rd;                                  // Obtain a random number from hardware
    std::mt19937 eng(rd());                                 // Seed the generator
    std::uniform_int_distribution<> distr(0, num_addr - 1); // Define the range

    int idx = distr(eng);
    auto iter = activeAddressSet.begin(); // Obtain an iterator to the start of the set
    std::advance(iter, idx);              // Advance the iterator a random number of steps

    primary_address_ = *iter;
    std::cout << "\nSetting new primary address: " << primary_address_ << "\n";
    get_status_manager().SetPrimary(primary_address_);
}

void BackendMasterClient::sendSetPrimaryAll()
{
    for (const auto &sendto : activeAddressSet)
    {
        sendSetPrimary(sendto);
    }
}

void BackendMasterClient::checkAndSetPrimary()
{
    if (noActivePrimary())
    {
        if (noAvailablePrimary())
        {
            std::cout << "\nNo available active nodes, setting primary to 0\n";
            primary_address_ = "";
            std::string temp_primary = "-1";
            get_status_manager().SetPrimary(temp_primary);
            return;
        }
        else
        {
            setNewPrimary();
            sendSetPrimaryAll();
            return;
        }
    }
}

void BackendMasterClient::checkNodeHealth(const std::string &address)
{
    kvstore::HealthCheckRequest request;
    grpc::ClientContext context;
    kvstore::HealthCheckResponse response;
    grpc::Status status = stubs[address]->CheckNodeHealth(&context, request, &response);

    if (!status.ok() || !response.ishealthy())
    {
        std::cout << "Node " << address << " is not responding. Marking as inactive." << std::endl;
        get_status_manager().SetNodeStatus(address, "inactive");
    }
    else if (response.ishealthy())
    {
        std::cout<<"\nReceived response: "<<response.recovery_status();
        get_status_manager().SetNodeStatus(address, response.recovery_status());
        // std::cout << "Node " << address << " is recovering. Initiating primary designation." << std::endl;

        checkAndSetPrimary();
        sendSetPrimary(address);
    }
    else if (response.ishealthy())
    {
        std::cout << "Node " << address << " is fine." << std::endl;
    }
}

void BackendMasterClient::processNotifyRecovered(const std::string &address)
{
    std::cout << "Node " << address << " has recovered. Updating status to active." << std::endl;
    get_status_manager().SetNodeStatus(address, "active");
}

void BackendMasterClient::sendActiveNodes()
{
    // Create the request and response objects
    kvstore::ActiveNodesRequest request;
    for (const auto &addr : activeAddressSet)
    {
        std::cout << "active address being sent: " << addr << std::endl;
        request.add_nodeaddresses(addr);
    }
    for (const auto &sendto : activeAddressSet)
    {
        grpc::ClientContext context;
        kvstore::ActiveNodesResponse response;
        grpc::Status status = stubs[sendto]->ActiveNodes(&context, request, &response);
        if (!status.ok())
        {
            std::cerr << "Failed to send active nodes to " << sendto << ": " << status.error_message() << std::endl;
        }
        else
        {
            std::cout << "Active nodes updated on " << sendto << std::endl;
        }
    }
}

void BackendMasterClient::updateActiveAddressSet()
{
    std::cout << "\nUPDATING ACTIVE NODES\n";

    get_status_manager().showAllNodes();
    activeAddressSet.clear(); // Clear existing entries to avoid duplicates
    for (const auto &node : daemonMapToServer)
    {
        if (get_status_manager().GetNodeStatus(node.first) == "active")
        {
            activeAddressSet.insert(node.first);
        }
    }

    std::cout << "\nActive addresses: ";
    for (auto n : activeAddressSet)
    {
        std::cout << n << " ";
    }
    std::cout << "\n";
}

void BackendMasterClient::takeSnapShot()
{
    activeAddressSnap.clear(); // Clear the destination set to ensure it's empty before copying
    activeAddressSnap.insert(activeAddressSet.begin(), activeAddressSet.end());
}

// Additional utility or internal functions can be added as needed
