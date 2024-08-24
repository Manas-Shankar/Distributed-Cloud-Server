#ifndef REPLICATION_MANAGER_HPP
#define REPLICATION_MANAGER_HPP

#include <fstream>
#include <string>
#include <memory>
#include <unordered_map>
#include <stdint.h>
#include "tablet.hpp"
#include "../include/replication_service_impl.hpp"
#include "../include/checkpoint_controller.hpp"
#include "../include/recovery_controller.hpp"
#include <condition_variable>

// forward declaration of Checkpoint_Controller
class Checkpoint_Controller;

// implements the Primary replication protocol
class Replication_Coordinator
{
public:
    // Replication_Coordinator();
    Replication_Coordinator(const std::string &server_address,
                            const std::string &primary_address,
                            const std::unordered_map<std::string, std::shared_ptr<grpc::Channel>> &channels, Checkpoint_Controller &checkpointing_controller, Recovery_Controller &recovery_controller);
    ~Replication_Coordinator();

    bool replicate_transaction(const std::string &row, const std::string &column, const std::string &old_value, const std::string &value, const replication::Operation &operation_type); // this function is triggered whenever there is a write call from the webserver and forwards message
    bool is_primary();
    bool forward_to_primary(const std::string &row, const std::string &column, const std::string &old_value, const std::string &value, const replication::Operation &operation_type);
    bool forward_to_subordinates(const std::string &row, const std::string &column, const std::string &old_value, const std::string &value, const replication::Operation &operation_type);

private:
    int get_new_sequence_number();
    std::string get_primary_node_address();
    replication::Transaction setup_request(const std::string &row, const std::string &column, const std::string &oldvalue, const std::string &value, const replication::Operation &operation_type);
    bool execute_transaction(const std::string &row, const std::string &column, const std::string &old_value, const std::string &value, const replication::Operation &operation_type);

    std::string primary_node_address_;
    uint64_t max_sequence_number_;
    KV_Controller controller_;                                                                      // controller object to delegate the transaction to the controller for processing
    std::unordered_map<std::string, std::unique_ptr<replication::ReplicationService::Stub>> stubs_; // gRPC stub to communicate with other replica nodes
    // std::unique_ptr<replication::ReplicationService::Stub> primary_stub_;                           // gRPC stub to communicate with the primary node
    std::string server_address_;                                               // address of the current node
    std::unordered_map<std::string, std::shared_ptr<grpc::Channel>> channels_; // map of all the channels to the other nodes
    Checkpoint_Controller &checkpoint_controller_;                             // checkpointing controller object
    std::vector<replication::Transaction> outbound_messages_;                  // queue of messages to be sent out
    Recovery_Controller &recovery_controller_;                                 // recovery controller object to check if we are in Recovery mode

    // file path for the transaction log
    // std::string transaction_log_path_;
    // log of all transactions stream
    // std::unique_ptr<std::fstream> transaction_log_stream_;
};

#endif // REPLICATION_MANAGER_HPP