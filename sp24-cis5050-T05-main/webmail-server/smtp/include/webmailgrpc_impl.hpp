// webmailgrpc_impl.hh
#ifndef WEBMAILGRPC_IMPL_HH
#define WEBMAILGRPC_IMPL_HH

#include "../grpc_proto/webmailgrpc.grpc.pb.h"
#include "server.hpp"  // Ensure EmailServer is declared

using grpc::ServerContext;
using grpc::Status;
using webmailgrpc::CommandRequest;
using webmailgrpc::CommandResponse;
using webmailgrpc::WebmailService;

class WebmailServiceImpl final : public WebmailService::Service {
    EmailServer& server;

public:
    explicit WebmailServiceImpl(EmailServer& serv);

    Status SendCommand(ServerContext* context, const CommandRequest* request, CommandResponse* response) override;
};

#endif // WEBMAILGRPC_IMPL_HH
