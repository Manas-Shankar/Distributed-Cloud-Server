#ifndef SAMPLE_STORE_KV_CLIENT_H
#define SAMPLE_STORE_KV_CLIENT_H

#include "../grpc_proto/kv_grpc_proto/kv_store.grpc.pb.h"
#include "../grpc_proto/kv_grpc_proto/backend_master_as_server.grpc.pb.h"

#include <iostream>
#include <memory>
#include <string>
#include <grpc++/grpc++.h>
#include <grpcpp/grpcpp.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using kvstore::KeyValue;
using kvstore::PutRequest;
using kvstore::PutResponse;
using kvstore::GetRequest;
using kvstore::GetResponse;
using kvstore::CPutRequest;
using kvstore::CPutResponse;
using kvstore::DeleteRequest;
using kvstore::DeleteResponse;

using backendmaster::BackendMasterService;
using backendmaster::NotifyRecoveryRequest;
using backendmaster::NotifyRecoveryResponse;
using backendmaster::PrimaryRequest;
using backendmaster::PrimaryNode;
using backendmaster::ListNodesRequest;
using backendmaster::NodesList;
using backendmaster::GetNodeAddressRequest;
using backendmaster::GetNodeAddressResponse;


using namespace std;

class kvClient {
public:
    kvClient(std::shared_ptr<Channel> channel) : stub_(KeyValue::NewStub(channel)), backendStub_(BackendMasterService::NewStub(channel)) {}
    bool putToKv(string r, string c, string value);
    pair<string, string> getFromKv(string r, string c);
    string deleteFromKv(string r, string c);
    string getNodeAddress(string key);

private:
    unique_ptr<KeyValue::Stub> stub_;
    unique_ptr<BackendMasterService::Stub> backendStub_;
};

#endif // SAMPLE_STORE_KV_CLIENT_H
