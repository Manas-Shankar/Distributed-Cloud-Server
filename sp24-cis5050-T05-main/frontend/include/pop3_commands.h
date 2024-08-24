#ifndef POP3_COMMANDS_H
#define POP3_COMMANDS_H

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <grpcpp/grpcpp.h>
#include <memory>
#include <string>


//grpc Files
#include "../grpc_proto/webmail_grpc_proto/webmailgrpc.grpc.pb.h"
#include "../grpc_proto/webmail_grpc_proto/webmailgrpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::Channel;
using webmailgrpc::CommandRequest;
using webmailgrpc::CommandResponse;
using webmailgrpc::WebmailService;

using namespace std;
class POP3Client {
public:

    POP3Client(std::shared_ptr<Channel> channel) : stub_(WebmailService::NewStub(channel)){};

    std::string sendCommand(std::string cmd);
    std::string userAndPass(std::string userName, std::string password);
    std::string stat();
    std::string retr(std::string num);
    std::string list();
    std::string deleteMail(std::string num);
    std::string quit();
    std::string uidl(std::string num);

private:
    std::unique_ptr<WebmailService::Stub> stub_;
};

#endif // POP3_COMMANDS_H
