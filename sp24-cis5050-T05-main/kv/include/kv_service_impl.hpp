#include "../grpc_proto/kv_store.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include "../include/controller.hpp"
#include "../include/replication_coordinator.hpp"
#include <string>
#include <optional>

class KeyValueServiceImpl final : public kvstore::KeyValue::Service
{
public:
    KeyValueServiceImpl(Replication_Coordinator &replication_coordinator);

    grpc::Status Put(grpc::ServerContext *context, const kvstore::PutRequest *request, kvstore::PutResponse *response) override;
    grpc::Status Get(grpc::ServerContext *context, const kvstore::GetRequest *request, kvstore::GetResponse *response) override;
    grpc::Status CPut(grpc::ServerContext *context, const kvstore::CPutRequest *request, kvstore::CPutResponse *response) override;
    grpc::Status Delete(grpc::ServerContext *context, const kvstore::DeleteRequest *request, kvstore::DeleteResponse *response) override;

private:
    KV_Controller controller;
    Replication_Coordinator &replication_coordinator;
};
