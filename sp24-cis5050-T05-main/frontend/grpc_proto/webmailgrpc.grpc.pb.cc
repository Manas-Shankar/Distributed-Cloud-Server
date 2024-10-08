// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: webmailgrpc.proto

#include "webmailgrpc.pb.h"
#include "webmailgrpc.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>
namespace webmailgrpc {

static const char* WebmailService_method_names[] = {
  "/webmailgrpc.WebmailService/SendCommand",
};

std::unique_ptr< WebmailService::Stub> WebmailService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< WebmailService::Stub> stub(new WebmailService::Stub(channel, options));
  return stub;
}

WebmailService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_SendCommand_(WebmailService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status WebmailService::Stub::SendCommand(::grpc::ClientContext* context, const ::webmailgrpc::CommandRequest& request, ::webmailgrpc::CommandResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::webmailgrpc::CommandRequest, ::webmailgrpc::CommandResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_SendCommand_, context, request, response);
}

void WebmailService::Stub::async::SendCommand(::grpc::ClientContext* context, const ::webmailgrpc::CommandRequest* request, ::webmailgrpc::CommandResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::webmailgrpc::CommandRequest, ::webmailgrpc::CommandResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SendCommand_, context, request, response, std::move(f));
}

void WebmailService::Stub::async::SendCommand(::grpc::ClientContext* context, const ::webmailgrpc::CommandRequest* request, ::webmailgrpc::CommandResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SendCommand_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::webmailgrpc::CommandResponse>* WebmailService::Stub::PrepareAsyncSendCommandRaw(::grpc::ClientContext* context, const ::webmailgrpc::CommandRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::webmailgrpc::CommandResponse, ::webmailgrpc::CommandRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_SendCommand_, context, request);
}

::grpc::ClientAsyncResponseReader< ::webmailgrpc::CommandResponse>* WebmailService::Stub::AsyncSendCommandRaw(::grpc::ClientContext* context, const ::webmailgrpc::CommandRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncSendCommandRaw(context, request, cq);
  result->StartCall();
  return result;
}

WebmailService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      WebmailService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< WebmailService::Service, ::webmailgrpc::CommandRequest, ::webmailgrpc::CommandResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](WebmailService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::webmailgrpc::CommandRequest* req,
             ::webmailgrpc::CommandResponse* resp) {
               return service->SendCommand(ctx, req, resp);
             }, this)));
}

WebmailService::Service::~Service() {
}

::grpc::Status WebmailService::Service::SendCommand(::grpc::ServerContext* context, const ::webmailgrpc::CommandRequest* request, ::webmailgrpc::CommandResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace webmailgrpc

