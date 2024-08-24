#include "../grpc_proto/kv_store.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include "../include/controller.hpp"
#include "../include/replication_coordinator.hpp"
#include "../include/kv_service_impl.hpp"
#include <string>
#include <optional>

KeyValueServiceImpl::KeyValueServiceImpl(Replication_Coordinator &replication_coordinator) : replication_coordinator(replication_coordinator) {}

grpc::Status KeyValueServiceImpl::Put(grpc::ServerContext *context, const kvstore::PutRequest *request, kvstore::PutResponse *response)
{
    // replicate request across all nodes:
    bool replication_result = replication_coordinator.replicate_transaction(request->row(), request->column(), "", request->value(), replication::Operation::PUT);
    if (replication_result)
    {
        std::cout << "Put operation successful" << std::endl;
        response->set_success(true);
        return grpc::Status::OK;
    }
    else
    {
        response->set_success(false);
        return grpc::Status(grpc::StatusCode::INTERNAL, "Delete operation failed.");
    }
}

grpc::Status KeyValueServiceImpl::Get(grpc::ServerContext *context, const kvstore::GetRequest *request, kvstore::GetResponse *response)
{
    auto value = controller.Get(request->row(), request->column());
    if (value.has_value())
    {
        response->set_value(*value);
        return grpc::Status::OK;
    }
    else
    {
        // Here you would typically return NOT_FOUND if the key doesn't exist
        return grpc::Status(grpc::StatusCode::NOT_FOUND, "Key not found or Get operation not implemented.");
    }
}

grpc::Status KeyValueServiceImpl::CPut(grpc::ServerContext *context, const kvstore::CPutRequest *request, kvstore::CPutResponse *response)
{
    // replicate request across all nodes:
    bool replication_result = replication_coordinator.replicate_transaction(request->row(), request->column(), request->value1(), request->value2(), replication::Operation::CPUT);
    if (replication_result)
    {
        std::cout << "CPut operation successful" << std::endl;
        response->set_success(true);
        return grpc::Status::OK;
    }
    else
    {
        std::cout << "CPut operation failed" << std::endl;
        response->set_success(false);
        return grpc::Status(grpc::StatusCode::INTERNAL, "Delete operation failed.");
    }
}

grpc::Status KeyValueServiceImpl::Delete(grpc::ServerContext *context, const kvstore::DeleteRequest *request, kvstore::DeleteResponse *response)
{
    // replicate request across all nodes:
    bool replication_result = replication_coordinator.replicate_transaction(request->row(), request->column(), "", "", replication::Operation::DELETE);
    if (replication_result)
    {
        std::cout << "Delete operation successful" << std::endl;
        response->set_success(true);
        return grpc::Status::OK;
    }
    else
    {
        std::cout << "Delete operation failed" << std::endl;
        response->set_success(false);
        return grpc::Status(grpc::StatusCode::INTERNAL, "Delete operation failed.");
    }
}
