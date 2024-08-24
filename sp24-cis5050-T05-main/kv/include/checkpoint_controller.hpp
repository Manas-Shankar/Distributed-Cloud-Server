#ifndef CHECKPOINT_CONTROLLER_HPP
#define CHECKPOINT_CONTROLLER_HPP

#include <string>
#include <mutex>
#include <unordered_map>
#include <grpcpp/grpcpp.h>
#include "../grpc_proto/checkpoint.grpc.pb.h"
#include <memory>
#include "replication_coordinator.hpp"
#include "../include/status_manager.hpp"

class Replication_Coordinator;

class Checkpoint_Controller
{
public:
    Checkpoint_Controller(const std::string &server_address,
                          const std::string &primary_address,
                          const std::unordered_map<std::string, std::shared_ptr<grpc::Channel>> &channels,
                          int max_write_count);
    ~Checkpoint_Controller();

    // done by primary node
    void init_checkpointing(); // initializes the checkpointing process: get new checkpoint number, start checkpointing, set is checkpointing to true and call multicast_checkpoint
    bool multicast_checkpoint();
    void complete_checkpointing();

    // done by secondary nodes
    bool start_checkpointing(int64_t &checkpoint_version_number);
    // same as complete_checkpointing but triggered by RPC call from primary and doesn't send any more RPC calls
    bool secondary_complete_checkpointing(int64_t &checkpoint_version_number);
    void update_checkpoint_number();

    // setters
    void set_checkpointing(bool is_checkpointing);
    void set_replication_coordinator(Replication_Coordinator *replication_coordinator);
    // getters
    bool is_checkpointing();
    bool is_primary();

    // increase write count
    void increase_write_count();

private:
    int64_t checkpoint_version_number_;
    std::mutex checkpoint_version_number_mutex_;
    bool is_primary_;
    bool is_checkpointing_;

    std::string primary_node_address_;                                                            // store address of primary node
    std::unordered_map<std::string, std::unique_ptr<checkpoint::CheckpointService::Stub>> stubs_; // gRPC stubs map to communicate with other replica nodes
    // std::unique_ptr<checkpoint::CheckpointService::Stub> primary_stub_;                           // gRPC stub to communicate with the primary node
    std::string server_address_;                                               // address of the current node
    std::unordered_map<std::string, std::shared_ptr<grpc::Channel>> channels_; // map of all the channels to the other nodes
    Replication_Coordinator *replication_coordinator_;                         // store pointer to replication coordinator
    int write_count_;                                                          // count of writes since last checkpoint
    std::mutex write_count_mutex_;                                             // mutex for write_count_
    int max_write_count_;                                                      // max number of writes before checkpointing
};

#endif // CHECKPOINT_CONTROLLER_HPP