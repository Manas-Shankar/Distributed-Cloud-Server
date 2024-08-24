#ifndef SMTP_COMMANDS_H
#define SMTP_COMMANDS_H

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
using namespace std;
//grpc Files
#include "../grpc_proto/webmail_grpc_proto/webmailgrpc.grpc.pb.h"
#include "../grpc_proto/webmail_grpc_proto/webmailgrpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ClientContext;
using grpc::Status;
using webmailgrpc::CommandRequest;
using webmailgrpc::CommandResponse;
using webmailgrpc::WebmailService;

using grpc::Status;
using grpc::Channel;

class SMTPClient {
public:
    SMTPClient(std::shared_ptr<Channel> channel) : stub_(WebmailService::NewStub(channel)){};
    std::string sendCommand(std::string cmd);
    std::string connect(std::string userID);
    std::string senderDetails(std::string senderEmail);
    std::string receiverDetails(std::string receiverEmail);
    std::string sendData(std::string data);
    std::string quit();
    std::string sendDot();

private:
std::unique_ptr<WebmailService::Stub> stub_;

};

#endif // SMTP_COMMANDS_H
