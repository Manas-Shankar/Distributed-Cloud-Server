#ifndef ADMIN_CONSOLE_H
#define ADMIN_CONSOLE_H

#include <map>
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sstream>
#include <arpa/inet.h>
#include "request.h"
#include "response.h"

//GRPC
#include <grpcpp/grpcpp.h>
#include "../grpc_proto/kv_grpc_proto/kv_lifecycle.grpc.pb.h"
#include "../grpc_proto/kv_grpc_proto/kv_admin_console.grpc.pb.h"
#include "../grpc_proto/kv_grpc_proto/backend_master_as_server.grpc.pb.h"

const std::string HTTP_HEADER = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n";


using namespace std;

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using kvstore::KVNodeLifecycle;
using kvstore::ShutdownRequest;
using kvstore::ShutdownResponse;
using kvstore::RestartRequest;
using kvstore::RestartResponse;
using kvstore::ActiveNodesRequest;
using kvstore::ActiveNodesResponse;
using admin::AdminKV;
using admin::GetAllRequest;
using admin::GetAllResponse;
using admin::KeyValue;


class AdminConsole {
public:
    AdminConsole(){};
    std::string handleRequest(Request& req);
    void initializeNodes();
    void getNodeStatus();
    void getKVData();
    map<string,string> handleNodes();
    map<string,string> handleKVStore();
    std::string nodeOperations(std::string command,std::string nodeId);
    std::string dataUpdater(Request& req);

    map<string,string> startNodes();
    map<string,string> startKVStore();
    map<string,string> nodesAndGroups();
};

#endif // ADMIN_CONSOLE_H
