// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: kv_lifecycle.proto

#include "kv_lifecycle.pb.h"
#include "kv_lifecycle.grpc.pb.h"

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
namespace kvstore {

static const char* KVNodeLifecycle_method_names[] = {
  "/kvstore.KVNodeLifecycle/Shutdown",
  "/kvstore.KVNodeLifecycle/Restart",
  "/kvstore.KVNodeLifecycle/CheckNodeHealth",
  "/kvstore.KVNodeLifecycle/SetPrimary",
  "/kvstore.KVNodeLifecycle/ActiveNodes",
};

std::unique_ptr< KVNodeLifecycle::Stub> KVNodeLifecycle::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< KVNodeLifecycle::Stub> stub(new KVNodeLifecycle::Stub(channel, options));
  return stub;
}

KVNodeLifecycle::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_Shutdown_(KVNodeLifecycle_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Restart_(KVNodeLifecycle_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_CheckNodeHealth_(KVNodeLifecycle_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_SetPrimary_(KVNodeLifecycle_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_ActiveNodes_(KVNodeLifecycle_method_names[4], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status KVNodeLifecycle::Stub::Shutdown(::grpc::ClientContext* context, const ::kvstore::ShutdownRequest& request, ::kvstore::ShutdownResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::kvstore::ShutdownRequest, ::kvstore::ShutdownResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_Shutdown_, context, request, response);
}

void KVNodeLifecycle::Stub::async::Shutdown(::grpc::ClientContext* context, const ::kvstore::ShutdownRequest* request, ::kvstore::ShutdownResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::kvstore::ShutdownRequest, ::kvstore::ShutdownResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Shutdown_, context, request, response, std::move(f));
}

void KVNodeLifecycle::Stub::async::Shutdown(::grpc::ClientContext* context, const ::kvstore::ShutdownRequest* request, ::kvstore::ShutdownResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Shutdown_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::kvstore::ShutdownResponse>* KVNodeLifecycle::Stub::PrepareAsyncShutdownRaw(::grpc::ClientContext* context, const ::kvstore::ShutdownRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::kvstore::ShutdownResponse, ::kvstore::ShutdownRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_Shutdown_, context, request);
}

::grpc::ClientAsyncResponseReader< ::kvstore::ShutdownResponse>* KVNodeLifecycle::Stub::AsyncShutdownRaw(::grpc::ClientContext* context, const ::kvstore::ShutdownRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncShutdownRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status KVNodeLifecycle::Stub::Restart(::grpc::ClientContext* context, const ::kvstore::RestartRequest& request, ::kvstore::RestartResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::kvstore::RestartRequest, ::kvstore::RestartResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_Restart_, context, request, response);
}

void KVNodeLifecycle::Stub::async::Restart(::grpc::ClientContext* context, const ::kvstore::RestartRequest* request, ::kvstore::RestartResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::kvstore::RestartRequest, ::kvstore::RestartResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Restart_, context, request, response, std::move(f));
}

void KVNodeLifecycle::Stub::async::Restart(::grpc::ClientContext* context, const ::kvstore::RestartRequest* request, ::kvstore::RestartResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Restart_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::kvstore::RestartResponse>* KVNodeLifecycle::Stub::PrepareAsyncRestartRaw(::grpc::ClientContext* context, const ::kvstore::RestartRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::kvstore::RestartResponse, ::kvstore::RestartRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_Restart_, context, request);
}

::grpc::ClientAsyncResponseReader< ::kvstore::RestartResponse>* KVNodeLifecycle::Stub::AsyncRestartRaw(::grpc::ClientContext* context, const ::kvstore::RestartRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncRestartRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status KVNodeLifecycle::Stub::CheckNodeHealth(::grpc::ClientContext* context, const ::kvstore::HealthCheckRequest& request, ::kvstore::HealthCheckResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::kvstore::HealthCheckRequest, ::kvstore::HealthCheckResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_CheckNodeHealth_, context, request, response);
}

void KVNodeLifecycle::Stub::async::CheckNodeHealth(::grpc::ClientContext* context, const ::kvstore::HealthCheckRequest* request, ::kvstore::HealthCheckResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::kvstore::HealthCheckRequest, ::kvstore::HealthCheckResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CheckNodeHealth_, context, request, response, std::move(f));
}

void KVNodeLifecycle::Stub::async::CheckNodeHealth(::grpc::ClientContext* context, const ::kvstore::HealthCheckRequest* request, ::kvstore::HealthCheckResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CheckNodeHealth_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::kvstore::HealthCheckResponse>* KVNodeLifecycle::Stub::PrepareAsyncCheckNodeHealthRaw(::grpc::ClientContext* context, const ::kvstore::HealthCheckRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::kvstore::HealthCheckResponse, ::kvstore::HealthCheckRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_CheckNodeHealth_, context, request);
}

::grpc::ClientAsyncResponseReader< ::kvstore::HealthCheckResponse>* KVNodeLifecycle::Stub::AsyncCheckNodeHealthRaw(::grpc::ClientContext* context, const ::kvstore::HealthCheckRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncCheckNodeHealthRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status KVNodeLifecycle::Stub::SetPrimary(::grpc::ClientContext* context, const ::kvstore::SetPrimaryRequest& request, ::kvstore::SetPrimaryResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::kvstore::SetPrimaryRequest, ::kvstore::SetPrimaryResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_SetPrimary_, context, request, response);
}

void KVNodeLifecycle::Stub::async::SetPrimary(::grpc::ClientContext* context, const ::kvstore::SetPrimaryRequest* request, ::kvstore::SetPrimaryResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::kvstore::SetPrimaryRequest, ::kvstore::SetPrimaryResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SetPrimary_, context, request, response, std::move(f));
}

void KVNodeLifecycle::Stub::async::SetPrimary(::grpc::ClientContext* context, const ::kvstore::SetPrimaryRequest* request, ::kvstore::SetPrimaryResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SetPrimary_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::kvstore::SetPrimaryResponse>* KVNodeLifecycle::Stub::PrepareAsyncSetPrimaryRaw(::grpc::ClientContext* context, const ::kvstore::SetPrimaryRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::kvstore::SetPrimaryResponse, ::kvstore::SetPrimaryRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_SetPrimary_, context, request);
}

::grpc::ClientAsyncResponseReader< ::kvstore::SetPrimaryResponse>* KVNodeLifecycle::Stub::AsyncSetPrimaryRaw(::grpc::ClientContext* context, const ::kvstore::SetPrimaryRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncSetPrimaryRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status KVNodeLifecycle::Stub::ActiveNodes(::grpc::ClientContext* context, const ::kvstore::ActiveNodesRequest& request, ::kvstore::ActiveNodesResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::kvstore::ActiveNodesRequest, ::kvstore::ActiveNodesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_ActiveNodes_, context, request, response);
}

void KVNodeLifecycle::Stub::async::ActiveNodes(::grpc::ClientContext* context, const ::kvstore::ActiveNodesRequest* request, ::kvstore::ActiveNodesResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::kvstore::ActiveNodesRequest, ::kvstore::ActiveNodesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ActiveNodes_, context, request, response, std::move(f));
}

void KVNodeLifecycle::Stub::async::ActiveNodes(::grpc::ClientContext* context, const ::kvstore::ActiveNodesRequest* request, ::kvstore::ActiveNodesResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ActiveNodes_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::kvstore::ActiveNodesResponse>* KVNodeLifecycle::Stub::PrepareAsyncActiveNodesRaw(::grpc::ClientContext* context, const ::kvstore::ActiveNodesRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::kvstore::ActiveNodesResponse, ::kvstore::ActiveNodesRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_ActiveNodes_, context, request);
}

::grpc::ClientAsyncResponseReader< ::kvstore::ActiveNodesResponse>* KVNodeLifecycle::Stub::AsyncActiveNodesRaw(::grpc::ClientContext* context, const ::kvstore::ActiveNodesRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncActiveNodesRaw(context, request, cq);
  result->StartCall();
  return result;
}

KVNodeLifecycle::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      KVNodeLifecycle_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< KVNodeLifecycle::Service, ::kvstore::ShutdownRequest, ::kvstore::ShutdownResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](KVNodeLifecycle::Service* service,
             ::grpc::ServerContext* ctx,
             const ::kvstore::ShutdownRequest* req,
             ::kvstore::ShutdownResponse* resp) {
               return service->Shutdown(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      KVNodeLifecycle_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< KVNodeLifecycle::Service, ::kvstore::RestartRequest, ::kvstore::RestartResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](KVNodeLifecycle::Service* service,
             ::grpc::ServerContext* ctx,
             const ::kvstore::RestartRequest* req,
             ::kvstore::RestartResponse* resp) {
               return service->Restart(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      KVNodeLifecycle_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< KVNodeLifecycle::Service, ::kvstore::HealthCheckRequest, ::kvstore::HealthCheckResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](KVNodeLifecycle::Service* service,
             ::grpc::ServerContext* ctx,
             const ::kvstore::HealthCheckRequest* req,
             ::kvstore::HealthCheckResponse* resp) {
               return service->CheckNodeHealth(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      KVNodeLifecycle_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< KVNodeLifecycle::Service, ::kvstore::SetPrimaryRequest, ::kvstore::SetPrimaryResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](KVNodeLifecycle::Service* service,
             ::grpc::ServerContext* ctx,
             const ::kvstore::SetPrimaryRequest* req,
             ::kvstore::SetPrimaryResponse* resp) {
               return service->SetPrimary(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      KVNodeLifecycle_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< KVNodeLifecycle::Service, ::kvstore::ActiveNodesRequest, ::kvstore::ActiveNodesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](KVNodeLifecycle::Service* service,
             ::grpc::ServerContext* ctx,
             const ::kvstore::ActiveNodesRequest* req,
             ::kvstore::ActiveNodesResponse* resp) {
               return service->ActiveNodes(ctx, req, resp);
             }, this)));
}

KVNodeLifecycle::Service::~Service() {
}

::grpc::Status KVNodeLifecycle::Service::Shutdown(::grpc::ServerContext* context, const ::kvstore::ShutdownRequest* request, ::kvstore::ShutdownResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status KVNodeLifecycle::Service::Restart(::grpc::ServerContext* context, const ::kvstore::RestartRequest* request, ::kvstore::RestartResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status KVNodeLifecycle::Service::CheckNodeHealth(::grpc::ServerContext* context, const ::kvstore::HealthCheckRequest* request, ::kvstore::HealthCheckResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status KVNodeLifecycle::Service::SetPrimary(::grpc::ServerContext* context, const ::kvstore::SetPrimaryRequest* request, ::kvstore::SetPrimaryResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status KVNodeLifecycle::Service::ActiveNodes(::grpc::ServerContext* context, const ::kvstore::ActiveNodesRequest* request, ::kvstore::ActiveNodesResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace kvstore

