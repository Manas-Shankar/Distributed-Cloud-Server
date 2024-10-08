// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: backend_master_kv.proto

#include "backend_master_kv.pb.h"
#include "backend_master_kv.grpc.pb.h"

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
namespace backendmasterkv {

static const char* BackendMasterKVService_method_names[] = {
  "/backendmasterkv.BackendMasterKVService/NotifyRecovered",
};

std::unique_ptr< BackendMasterKVService::Stub> BackendMasterKVService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< BackendMasterKVService::Stub> stub(new BackendMasterKVService::Stub(channel, options));
  return stub;
}

BackendMasterKVService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_NotifyRecovered_(BackendMasterKVService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status BackendMasterKVService::Stub::NotifyRecovered(::grpc::ClientContext* context, const ::backendmasterkv::NotifyRecoveredRequest& request, ::backendmasterkv::NotifyRecoveredResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::backendmasterkv::NotifyRecoveredRequest, ::backendmasterkv::NotifyRecoveredResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_NotifyRecovered_, context, request, response);
}

void BackendMasterKVService::Stub::async::NotifyRecovered(::grpc::ClientContext* context, const ::backendmasterkv::NotifyRecoveredRequest* request, ::backendmasterkv::NotifyRecoveredResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::backendmasterkv::NotifyRecoveredRequest, ::backendmasterkv::NotifyRecoveredResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_NotifyRecovered_, context, request, response, std::move(f));
}

void BackendMasterKVService::Stub::async::NotifyRecovered(::grpc::ClientContext* context, const ::backendmasterkv::NotifyRecoveredRequest* request, ::backendmasterkv::NotifyRecoveredResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_NotifyRecovered_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::backendmasterkv::NotifyRecoveredResponse>* BackendMasterKVService::Stub::PrepareAsyncNotifyRecoveredRaw(::grpc::ClientContext* context, const ::backendmasterkv::NotifyRecoveredRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::backendmasterkv::NotifyRecoveredResponse, ::backendmasterkv::NotifyRecoveredRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_NotifyRecovered_, context, request);
}

::grpc::ClientAsyncResponseReader< ::backendmasterkv::NotifyRecoveredResponse>* BackendMasterKVService::Stub::AsyncNotifyRecoveredRaw(::grpc::ClientContext* context, const ::backendmasterkv::NotifyRecoveredRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncNotifyRecoveredRaw(context, request, cq);
  result->StartCall();
  return result;
}

BackendMasterKVService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      BackendMasterKVService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< BackendMasterKVService::Service, ::backendmasterkv::NotifyRecoveredRequest, ::backendmasterkv::NotifyRecoveredResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](BackendMasterKVService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::backendmasterkv::NotifyRecoveredRequest* req,
             ::backendmasterkv::NotifyRecoveredResponse* resp) {
               return service->NotifyRecovered(ctx, req, resp);
             }, this)));
}

BackendMasterKVService::Service::~Service() {
}

::grpc::Status BackendMasterKVService::Service::NotifyRecovered(::grpc::ServerContext* context, const ::backendmasterkv::NotifyRecoveredRequest* request, ::backendmasterkv::NotifyRecoveredResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace backendmasterkv

