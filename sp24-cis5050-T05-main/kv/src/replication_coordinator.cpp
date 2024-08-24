#include "../include/controller.hpp"
#include "../include/replication_coordinator.hpp"
#include "../include/checkpoint_controller.hpp"
#include "../include/tablet.hpp"
#include "../grpc_proto/kv_store.grpc.pb.h"
#include <grpcpp/grpcpp.h>

using namespace std;

// Replication_Coordinator::Replication_Coordinator(){}; // default constructor

Replication_Coordinator::Replication_Coordinator(const std::string &server_address,
                                                 const std::string &primary_address,
                                                 const std::unordered_map<std::string, std::shared_ptr<grpc::Channel>> &channels,
                                                 Checkpoint_Controller &checkpoint_controller, Recovery_Controller &recovery_controller) : primary_node_address_(primary_address), max_sequence_number_(0), server_address_(server_address), channels_(channels), checkpoint_controller_(checkpoint_controller), recovery_controller_(recovery_controller)
{
    // setup the client stub for the replication service
    /*std::string role = is_primary() ? "primary" : "subordinate";
    std::cout << "Setting up replication coordinator as a: " << role << std::endl;
    if (!is_primary())
    {
        auto channel = channels_[primary_node_address_];
        primary_stub_ = replication::ReplicationService::NewStub(channel);
    }*/
    // create the stubs for all other subordinate nodes
    for (const auto &channel : channels_)
    {
        // skip its own address in stub setup
        if (channel.first == server_address)
            continue;
        stubs_[channel.first] = replication::ReplicationService::NewStub(channel.second);
    }
}

Replication_Coordinator::~Replication_Coordinator()
{
}

bool Replication_Coordinator::replicate_transaction(const std::string &row, const std::string &column, const std::string &old_value, const std::string &value, const replication::Operation &operation_type)
{
    std::cout << "Replicating transaction" << endl;
    if (checkpoint_controller_.is_checkpointing() || recovery_controller_.recovery_in_progress())
    {
        // if checkpointing is in progress just return false
        cout << "Checkpointing/Recovery in progress. Transaction can't be executed nor replicated." << endl;
        return false;
    }
    bool success = false;
    if (is_primary())
    {
        execute_transaction(row, column, old_value, value, operation_type);
        // forward the message to all subordinates and overwrite success with the result
        success = forward_to_subordinates(row, column, old_value, value, operation_type);
        if (success)
        {
            // increase the write count in the checkpoint controller
            checkpoint_controller_.increase_write_count();
        }
    }
    else
    {
        success = forward_to_primary(row, column, old_value, value, operation_type);
    }
    return success;
}

bool Replication_Coordinator::execute_transaction(const std::string &row, const std::string &column, const std::string &old_value, const std::string &value, const replication::Operation &operation_type)
{
    cout << "Executing transaction: " << row << " " << column << endl;
    bool success = false;
    if (operation_type == replication::Operation::PUT)
    {
        success = controller_.Put(row, column, value);
    }
    else if (operation_type == replication::Operation::CPUT)
    {
        success = controller_.Cput(row, column, old_value, value);
    }
    else if (operation_type == replication::Operation::DELETE)
    {
        success = controller_.Delete(row, column);
    }
    // increase the write count in the checkpoint controller
    return success;
}

// forward the message to the primary node
bool Replication_Coordinator::forward_to_primary(const std::string &row, const std::string &column, const std::string &old_value, const std::string &value, const replication::Operation &operation_type)
{
    cout << "Forwarding to primary: " << row << " " << column << endl;
    // Create and configure the RPC request
    replication::Transaction request = setup_request(row, column, old_value, value, operation_type);
    // declare response object and context
    replication::TransactionResponse response;
    grpc::ClientContext context;

    // Make the RPC call
    grpc::Status status = stubs_[Status_Manager::GetInstance().get_primary_address()]->forwardTransaction(&context, request, &response);
    if (response.success())
    {
        std::cout << "Successfully forwarded to primary: " << response.message() << std::endl;
    }
    else
    {
        std::cerr << "Failed to forward to primary: " << status.error_message() << std::endl;
    }
    return response.success();
}

bool Replication_Coordinator::forward_to_subordinates(const std::string &row, const std::string &column, const std::string &old_value, const std::string &value, const replication::Operation &operation_type)
{

    cout << "Forwarding to subordinates: " << row << " " << column << endl;
    // Create and configure the RPC request
    replication::Transaction request = setup_request(row, column, old_value, value, operation_type);

    // loop over list of all subordinates and forward the message
    for (const auto &stub : stubs_)
    {
        // TODO: if a subordinate is down skip it
        if (!Status_Manager::GetInstance().is_active(stub.first))
        {
            cout << "Ignoring node: " << stub.first << " as it is down." << endl;
            continue;
        }
        // declare response object and context
        replication::TransactionResponse response;
        grpc::ClientContext context;
        // Make the RPC call
        grpc::Status status = stub.second->forwardTransaction(&context, request, &response);
        if (response.success())
        {
            std::cout << "Successfully forwarded to subordinate: " << response.message() << std::endl;
        }
        else
        {
            // if any of the subordinates fail to replicate the transaction return false
            std::cerr << "Failed to forward to subordinate: " << status.error_message() << std::endl;
            sleep(1);
            if (!Status_Manager::GetInstance().is_active(stub.first))
            {
                cout << "Ignoring node: " << stub.first << " as it is down." << endl;
                continue;
            }
            return false;
        }
    }
    // if all subordinates successfully replicated the transaction return true
    return true;
}

replication::Transaction Replication_Coordinator::setup_request(const std::string &row, const std::string &column, const std::string &oldvalue, const std::string &value, const replication::Operation &operation_type)
{
    // setup the Transaction request
    replication::Transaction request;
    request.set_key(row);
    request.set_column(column);
    request.set_value(value);
    request.set_old_value(oldvalue);
    // set operation based on operation type string
    if (operation_type == replication::Operation::PUT)
        request.set_operation(replication::PUT);
    else if (operation_type == replication::Operation::CPUT)
        request.set_operation(replication::CPUT);
    else if (operation_type == replication::Operation::DELETE)
        request.set_operation(replication::DELETE);
    else
        throw std::invalid_argument("Invalid operation type");
    return request;
}

bool Replication_Coordinator::is_primary()
{
    return server_address_ == Status_Manager::GetInstance().get_primary_address();
}

int Replication_Coordinator::get_new_sequence_number()
{
    return ++max_sequence_number_;
}

std::string Replication_Coordinator::get_primary_node_address()
{
    return Status_Manager::GetInstance().get_primary_address();
}