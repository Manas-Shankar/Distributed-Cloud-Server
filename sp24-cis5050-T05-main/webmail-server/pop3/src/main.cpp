// main.cpp
#include <iostream>
#include <string>
#include "../include/server.hpp"  // Assume EmailServer is correctly implemented
#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include "../include/webmailgrpc_impl.hpp"

void RunServer(const std::string& server_address, EmailServer& server);

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <port> <mailboxDir>" << std::endl;
        return 1;
    }

    int port = std::stoi(argv[1]);
    std::string mailboxDir = argv[2];
    EmailServer emailServer(port, false, mailboxDir);

    std::string server_address("127.0.0.1:" + std::to_string(port));
    RunServer(server_address, emailServer);

    return 0;
}

void RunServer(const std::string& server_address, EmailServer& server) {
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    WebmailServiceImpl service(server);

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> grpcServer(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    grpcServer->Wait();
}

//TODO: check login
//Validate user
//check which kv node to send
//frontend shpuld take care every message is unique: add date etc to first line
//if  sending to external