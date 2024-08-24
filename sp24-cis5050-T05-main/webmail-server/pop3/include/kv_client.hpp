#ifndef KVCLIENT_H
#define KVCLIENT_H

#include <string>
#include <grpcpp/grpcpp.h>
#include "../grpc_proto/kv_store.grpc.pb.h"

class KVClient {
public:
    KVClient(std::shared_ptr<grpc::Channel> channel);

    bool put(const std::string& row, const std::string& column, const std::string& value);
    std::string get(const std::string& row, const std::string& column);
    bool deletes(const std::string& row, const std::string& column);

private:
    std::unique_ptr<kvstore::KeyValue::Stub> stub_;
};

#endif // KVCLIENT_H
