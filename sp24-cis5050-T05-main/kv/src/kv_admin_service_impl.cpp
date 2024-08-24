#include "../grpc_proto/kv_admin_console.grpc.pb.h"
#include "../grpc_proto/kv_admin_console.pb.h"

#include <grpcpp/grpcpp.h>
#include "../include/controller.hpp"
#include "../include/replication_coordinator.hpp"
#include "../include/kv_service_impl.hpp"
#include "../include/kv_admin_service_impl.hpp"
#include "../include/tablet_manager.hpp"
#include <string>
#include <optional>

using admin::AdminKV;
using admin::GetAllRequest;
using admin::GetAllResponse;
using admin::KeyValue;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

AdminKVServiceImpl::AdminKVServiceImpl() {}

grpc::Status AdminKVServiceImpl::GetAllKeyValuePairs(grpc::ServerContext *context, const admin::GetAllRequest *request, admin::GetAllResponse *response)
{
    std::cout << "Received GetAllKeyValuePairs request from admin console" << std::endl;
    // Access all tablets and get all the key value pairs
    Tablet_Manager &tb_manager = Tablet_Manager::get_instance();
    std::vector<Tablet *> tablets = tb_manager.get_all_tablets();
    for (const auto &tablet : tablets)
    {
        tb_manager.update_in_memory_tablet(tablet->get_tablet_id());
        std::set<std::string> &rows = tablet->ordered_keys_;
        if (rows.empty())
        {
            std::cout << "No rows in tablet" << std::endl;
            continue;
        }
        std::cout << "Rows size: " << rows.size() << std::endl;
        for (const auto &row : rows)
        {
            std::cout << "Row: " << row << std::endl;
            Row_Data &row_data = tablet->memtable_[row];
            for (const auto &column : row_data.columns)
            {
                KeyValue *keyValue = response->add_pairs();
                keyValue->set_row(row);
                keyValue->set_column(column.first);
                keyValue->set_value(column.second);
                std::cout << "Column: " << column.first << " Value: " << column.second << std::endl;
            }
        }
    }
    response->set_success(true);
    response->set_message("Data retrieved successfully");
    return Status::OK;
}