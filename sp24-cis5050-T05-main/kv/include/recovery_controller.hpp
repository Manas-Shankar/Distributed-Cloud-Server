#ifndef RECOVERY_CONTROLLER_HPP
#define RECOVERY_CONTROLLER_HPP

#include "../grpc_proto/recovery.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include <map>

class Recovery_Controller
{
public:
    Recovery_Controller(const std::string &server_address,
                        const std::string &primary_address,
                        const std::unordered_map<std::string, std::shared_ptr<grpc::Channel>> &channel);
    ~Recovery_Controller();

    // called whenever a node comes back up after a failure: starts the recovery process
    void start_recovery();
    bool send_chunked_checkpoint_files(std::string caller_address);
    void recover_with_checkpoint_chunks(std::string &bytes_content, const std::string &filename, const int &tablet_id, bool is_final_chunk, const std::string &starting_range);

    // setter function:
    void set_is_recovering(bool is_recovering);

    // getter function
    bool recovery_in_progress();

    // helper function to check if the logs are up to date: return true if up to date, false otherwise
    bool compare_log_numbers(const google::protobuf::RepeatedField<int64_t> &log_line_numbers_from_recovering_node, const std::vector<int64_t> &log_line_numbers);

    // test function: remove later
    bool test();

private:
    bool recover_checkpoint_files();
    bool send_start_recovery(int64_t checkpoint_number, const std::vector<int64_t> &log_line_numbers);
    bool send_recovery_complete();
    void recover_log_files(std::vector<int64_t> log_line_numbers);
    void apply_new_log_entries(const google::protobuf::RepeatedPtrField<recovery::Log_File> &log_files);
    bool is_primary();
    // TODO:
    void apply_queued_requests(); // apply all the queued requests to the memtable and log file

    std::string server_address_;                                                              // address of the current node
    bool is_primary_;                                                                         // flag to indicate if the current node is the primary node
    bool is_recovering_;                                                                      // flag to indicate if the system is currently recovering a node
    std::unordered_map<std::string, std::unique_ptr<recovery::RecoveryService::Stub>> stubs_; // gRPC stubs to communicate with all other nodes
    std::unordered_map<std::string, std::shared_ptr<grpc::Channel>> channels_;
};

#endif // RECOVERY_CONTROLLER_HPP