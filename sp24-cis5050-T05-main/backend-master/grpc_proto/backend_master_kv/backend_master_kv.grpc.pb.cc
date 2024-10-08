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
namespace penncloud {
namespace backend {

static const char* BackendMasterKVService_method_names[] = {
  "/penncloud.backend.BackendMasterKVService/CheckNodeHealth",
  "/penncloud.backend.BackendMasterKVService/ReportNodeLoad",
};

std::unique_ptr< BackendMasterKVService::Stub> BackendMasterKVService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< BackendMasterKVService::Stub> stub(new BackendMasterKVService::Stub(channel, options));
  return stub;
}

BackendMasterKVService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_CheckNodeHealth_(BackendMasterKVService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_ReportNodeLoad_(BackendMasterKVService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status BackendMasterKVService::Stub::CheckNodeHealth(::grpc::ClientContext* context, const ::penncloud::backend::HealthCheckRequest& request, ::penncloud::backend::HealthCheckResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::penncloud::backend::HealthCheckRequest, ::penncloud::backend::HealthCheckResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_CheckNodeHealth_, context, request, response);
}

void BackendMasterKVService::Stub::async::CheckNodeHealth(::grpc::ClientContext* context, const ::penncloud::backend::HealthCheckRequest* request, ::penncloud::backend::HealthCheckResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::penncloud::backend::HealthCheckRequest, ::penncloud::backend::HealthCheckResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CheckNodeHealth_, context, request, response, std::move(f));
}

void BackendMasterKVService::Stub::async::CheckNodeHealth(::grpc::ClientContext* context, const ::penncloud::backend::HealthCheckRequest* request, ::penncloud::backend::HealthCheckResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CheckNodeHealth_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::penncloud::backend::HealthCheckResponse>* BackendMasterKVService::Stub::PrepareAsyncCheckNodeHealthRaw(::grpc::ClientContext* context, const ::penncloud::backend::HealthCheckRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::penncloud::backend::HealthCheckResponse, ::penncloud::backend::HealthCheckRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_CheckNodeHealth_, context, request);
}

::grpc::ClientAsyncResponseReader< ::penncloud::backend::HealthCheckResponse>* BackendMasterKVService::Stub::AsyncCheckNodeHealthRaw(::grpc::ClientContext* context, const ::penncloud::backend::HealthCheckRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncCheckNodeHealthRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status BackendMasterKVService::Stub::ReportNodeLoad(::grpc::ClientContext* context, const ::penncloud::backend::LoadReport& request, ::penncloud::backend::Acknowledgment* response) {
  return ::grpc::internal::BlockingUnaryCall< ::penncloud::backend::LoadReport, ::penncloud::backend::Acknowledgment, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_ReportNodeLoad_, context, request, response);
}

void BackendMasterKVService::Stub::async::ReportNodeLoad(::grpc::ClientContext* context, const ::penncloud::backend::LoadReport* request, ::penncloud::backend::Acknowledgment* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::penncloud::backend::LoadReport, ::penncloud::backend::Acknowledgment, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ReportNodeLoad_, context, request, response, std::move(f));
}

void BackendMasterKVService::Stub::async::ReportNodeLoad(::grpc::ClientContext* context, const ::penncloud::backend::LoadReport* request, ::penncloud::backend::Acknowledgment* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ReportNodeLoad_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::penncloud::backend::Acknowledgment>* BackendMasterKVService::Stub::PrepareAsyncReportNodeLoadRaw(::grpc::ClientContext* context, const ::penncloud::backend::LoadReport& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::penncloud::backend::Acknowledgment, ::penncloud::backend::LoadReport, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_ReportNodeLoad_, context, request);
}

::grpc::ClientAsyncResponseReader< ::penncloud::backend::Acknowledgment>* BackendMasterKVService::Stub::AsyncReportNodeLoadRaw(::grpc::ClientContext* context, const ::penncloud::backend::LoadReport& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncReportNodeLoadRaw(context, request, cq);
  result->StartCall();
  return result;
}

BackendMasterKVService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      BackendMasterKVService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< BackendMasterKVService::Service, ::penncloud::backend::HealthCheckRequest, ::penncloud::backend::HealthCheckResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](BackendMasterKVService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::penncloud::backend::HealthCheckRequest* req,
             ::penncloud::backend::HealthCheckResponse* resp) {
               return service->CheckNodeHealth(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      BackendMasterKVService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< BackendMasterKVService::Service, ::penncloud::backend::LoadReport, ::penncloud::backend::Acknowledgment, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](BackendMasterKVService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::penncloud::backend::LoadReport* req,
             ::penncloud::backend::Acknowledgment* resp) {
               return service->ReportNodeLoad(ctx, req, resp);
             }, this)));
}

BackendMasterKVService::Service::~Service() {
}

::grpc::Status BackendMasterKVService::Service::CheckNodeHealth(::grpc::ServerContext* context, const ::penncloud::backend::HealthCheckRequest* request, ::penncloud::backend::HealthCheckResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status BackendMasterKVService::Service::ReportNodeLoad(::grpc::ServerContext* context, const ::penncloud::backend::LoadReport* request, ::penncloud::backend::Acknowledgment* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace penncloud
}  // namespace backend

