#ifndef ADMIN_CONSOLE_HPP
#define ADMIN_CONSOLE_HPP

#include<map>
#include<vector>
#include<chrono>
#include <thread>
#include"Node.hpp"

//GRPC
#include <grpcpp/grpcpp.h>
#include "../grpc_proto/admin_console.grpc.pb.h"
#include "../grpc_proto/admin_console.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using admin_console::NodeInfoRequest;
using admin_console::NodeInfoResponse;
using admin_console::NodeInfoService;
using admin_console::NodeMessagesRequest;
using admin_console::NodeMessagesResponse;
using admin_console::NodeStatusRequest;
using admin_console::NodeStatusResponse;
using namespace std;

class AdminConsole {
    
public:

    Node* fetchDataSingleNode(std::string nodeId);
    std::vector<std::string> fetchMessagesSingleNode(std::string nodeId);
    void printMap(std::map<std::string,Node*> map) ;
    void fetch(std::map<std::string,Node*> map1,std::map<std::string,Node*> map2);
    void fetchData();
    void displayData();
    void displayCycle();
    void crashNode(std::string nodeId);

};

#endif //ADMIN_CONSOLE_HPP