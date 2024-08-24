#include "../include/status_manager.hpp" // Correct the include path case
#include <grpcpp/grpcpp.h>
#include <thread>

Status_Manager &Status_Manager::GetInstance()
{
    static Status_Manager instance; // Guaranteed to be destroyed and instantiated on first use
    return instance;
}

Status_Manager::Status_Manager() : is_active_(true), recovery_status_("recovering")
{
    // Initialize communication with backend master
    auto channel = grpc::CreateChannel("127.0.0.1:5056", grpc::InsecureChannelCredentials());
    be_master_stub_ = backendmaster::BackendMasterService::NewStub(channel);
    auto channel_2 = grpc::CreateChannel("127.0.0.1:5056", grpc::InsecureChannelCredentials());
    notify_be_master_stub_ = backendmaster::BackendMasterService::NewStub(channel_2);
    // TODO: Temporary fix so we can check which node addresses are active
    node_addresses_to_daemon_addresses_map_["127.0.0.1:5050"] = "127.0.0.1:5053";
    node_addresses_to_daemon_addresses_map_["127.0.0.1:5051"] = "127.0.0.1:5054";
    node_addresses_to_daemon_addresses_map_["127.0.0.1:5052"] = "127.0.0.1:5055";
    node_addresses_to_daemon_addresses_map_["127.0.0.1:5057"] = "127.0.0.1:5060";
    node_addresses_to_daemon_addresses_map_["127.0.0.1:5058"] = "127.0.0.1:5061";
    node_addresses_to_daemon_addresses_map_["127.0.0.1:5059"] = "127.0.0.1:5062";
}

bool Status_Manager::is_active(const std::string &address)
{
    std::string daemon_address = node_addresses_to_daemon_addresses_map_[address];
    // //std::cout << "active nodes size" << active_nodes_.size() << std::endl;
    // for (auto &node : active_nodes_)
    // {
    //     std::cout << node.first << ": " << node.second << std::endl;
    // }
    return active_nodes_.find(daemon_address) != active_nodes_.end() && active_nodes_[daemon_address];
}

std::string Status_Manager::get_primary_address()
{
    if (primary_address_.empty())
    {
        int retries = 3;
        int sleep_time = 1;
        while (retries > 0)
        {
            if (fetch_primary_address())
            {
                return primary_address_;
            }
            std::this_thread::sleep_for(std::chrono::seconds(sleep_time));
            retries--;
            sleep_time *= 2;
        }
    }
    return primary_address_;
}

bool Status_Manager::fetch_primary_address()
{
    backendmaster::PrimaryRequest request;
    backendmaster::PrimaryNode response;
    grpc::ClientContext context;

    request.set_caller_address(current_node_address_);
    auto status = be_master_stub_->GetPrimary(&context, request, &response);
    if (status.ok())
    {
        primary_address_ = response.primary_address();
        return true;
    }
    std::cerr << "Failed to fetch primary address: " << status.error_message() << std::endl;
    return false;
}

void Status_Manager::set_to_recovered()
{
    recovery_status_ = "active";
    /*
    is_active_ = true;
    int retries = 3;
    int sleep_time = 1;
    for (int i = 0; i < retries; i++)
    {
        if (send_recovery_notification())
        {
            return;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        sleep_time *= 2;
    }*/
}

bool Status_Manager::send_recovery_notification()
{
    backendmaster::NotifyRecoveryRequest request;
    backendmaster::NotifyRecoveryResponse response;
    grpc::ClientContext context;
    request.set_node_address(current_node_address_);
    auto status = notify_be_master_stub_->NotifyRecovery(&context, request, &response);
    if (status.ok())
    {
        std::cout << "Recovery notification sent successfully." << std::endl;
        return true;
    }
    else
    {
        std::cerr << "Failed to send recovery notification: " << status.error_message() << std::endl;
        return false;
    }
}

// Updates the active status of a node
void Status_Manager::update_active_node(const std::string &node, bool status)
{
    std::lock_guard<std::mutex> lock(map_mutex);
    active_nodes_[node] = status;
}

// Returns a list of all node addresses known to the manager
std::vector<std::string> Status_Manager::get_all_node_addresses()
{
    std::lock_guard<std::mutex> lock(map_mutex); // Ensure thread safety
    std::vector<std::string> addresses;
    for (const auto &node : active_nodes_)
    {
        addresses.push_back(node.first);
    }
    return addresses;
}

// Reset all nodes to inactive
void Status_Manager::set_all_nodes_inactive()
{
    std::lock_guard<std::mutex> lock(map_mutex);
    for (auto &node : active_nodes_)
    {
        node.second = false;
    }
}

void Status_Manager::set_primary_address(const std::string &address)
{
    primary_address_ = address;
}
