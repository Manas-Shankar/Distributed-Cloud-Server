// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: backend_master_as_server.proto

#include "backend_master_as_server.pb.h"
#include "backend_master_as_server.grpc.pb.h"

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
namespace backendmaster {

static const char* BackendMasterService_method_names[] = {
  "/backendmaster.BackendMasterService/NotifyRecovery",
  "/backendmaster.BackendMasterService/GetPrimary",
  "/backendmaster.BackendMasterService/ListNodes",
  "/backendmaster.BackendMasterService/GetNodeAddress",
};

std::unique_ptr< BackendMasterService::Stub> BackendMasterService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< BackendMasterService::Stub> stub(new BackendMasterService::Stub(channel, options));
  return stub;
}

BackendMasterService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_NotifyRecovery_(BackendMasterService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetPrimary_(BackendMasterService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_ListNodes_(BackendMasterService_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetNodeAddress_(BackendMasterService_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status BackendMasterService::Stub::NotifyRecovery(::grpc::ClientContext* context, const ::backendmaster::NotifyRecoveryRequest& request, ::backendmaster::NotifyRecoveryResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::backendmaster::NotifyRecoveryRequest, ::backendmaster::NotifyRecoveryResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_NotifyRecovery_, context, request, response);
}

void BackendMasterService::Stub::async::NotifyRecovery(::grpc::ClientContext* context, const ::backendmaster::NotifyRecoveryRequest* request, ::backendmaster::NotifyRecoveryResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::backendmaster::NotifyRecoveryRequest, ::backendmaster::NotifyRecoveryResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_NotifyRecovery_, context, request, response, std::move(f));
}

void BackendMasterService::Stub::async::NotifyRecovery(::grpc::ClientContext* context, const ::backendmaster::NotifyRecoveryRequest* request, ::backendmaster::NotifyRecoveryResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_NotifyRecovery_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::backendmaster::NotifyRecoveryResponse>* BackendMasterService::Stub::PrepareAsyncNotifyRecoveryRaw(::grpc::ClientContext* context, const ::backendmaster::NotifyRecoveryRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::backendmaster::NotifyRecoveryResponse, ::backendmaster::NotifyRecoveryRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_NotifyRecovery_, context, request);
}

::grpc::ClientAsyncResponseReader< ::backendmaster::NotifyRecoveryResponse>* BackendMasterService::Stub::AsyncNotifyRecoveryRaw(::grpc::ClientContext* context, const ::backendmaster::NotifyRecoveryRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncNotifyRecoveryRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status BackendMasterService::Stub::GetPrimary(::grpc::ClientContext* context, const ::backendmaster::PrimaryRequest& request, ::backendmaster::PrimaryNode* response) {
  return ::grpc::internal::BlockingUnaryCall< ::backendmaster::PrimaryRequest, ::backendmaster::PrimaryNode, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_GetPrimary_, context, request, response);
}

void BackendMasterService::Stub::async::GetPrimary(::grpc::ClientContext* context, const ::backendmaster::PrimaryRequest* request, ::backendmaster::PrimaryNode* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::backendmaster::PrimaryRequest, ::backendmaster::PrimaryNode, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetPrimary_, context, request, response, std::move(f));
}

void BackendMasterService::Stub::async::GetPrimary(::grpc::ClientContext* context, const ::backendmaster::PrimaryRequest* request, ::backendmaster::PrimaryNode* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetPrimary_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::backendmaster::PrimaryNode>* BackendMasterService::Stub::PrepareAsyncGetPrimaryRaw(::grpc::ClientContext* context, const ::backendmaster::PrimaryRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::backendmaster::PrimaryNode, ::backendmaster::PrimaryRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_GetPrimary_, context, request);
}

::grpc::ClientAsyncResponseReader< ::backendmaster::PrimaryNode>* BackendMasterService::Stub::AsyncGetPrimaryRaw(::grpc::ClientContext* context, const ::backendmaster::PrimaryRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncGetPrimaryRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status BackendMasterService::Stub::ListNodes(::grpc::ClientContext* context, const ::backendmaster::ListNodesRequest& request, ::backendmaster::NodesList* response) {
  return ::grpc::internal::BlockingUnaryCall< ::backendmaster::ListNodesRequest, ::backendmaster::NodesList, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_ListNodes_, context, request, response);
}

void BackendMasterService::Stub::async::ListNodes(::grpc::ClientContext* context, const ::backendmaster::ListNodesRequest* request, ::backendmaster::NodesList* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::backendmaster::ListNodesRequest, ::backendmaster::NodesList, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ListNodes_, context, request, response, std::move(f));
}

void BackendMasterService::Stub::async::ListNodes(::grpc::ClientContext* context, const ::backendmaster::ListNodesRequest* request, ::backendmaster::NodesList* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ListNodes_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::backendmaster::NodesList>* BackendMasterService::Stub::PrepareAsyncListNodesRaw(::grpc::ClientContext* context, const ::backendmaster::ListNodesRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::backendmaster::NodesList, ::backendmaster::ListNodesRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_ListNodes_, context, request);
}

::grpc::ClientAsyncResponseReader< ::backendmaster::NodesList>* BackendMasterService::Stub::AsyncListNodesRaw(::grpc::ClientContext* context, const ::backendmaster::ListNodesRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncListNodesRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status BackendMasterService::Stub::GetNodeAddress(::grpc::ClientContext* context, const ::backendmaster::GetNodeAddressRequest& request, ::backendmaster::GetNodeAddressResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::backendmaster::GetNodeAddressRequest, ::backendmaster::GetNodeAddressResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_GetNodeAddress_, context, request, response);
}

void BackendMasterService::Stub::async::GetNodeAddress(::grpc::ClientContext* context, const ::backendmaster::GetNodeAddressRequest* request, ::backendmaster::GetNodeAddressResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::backendmaster::GetNodeAddressRequest, ::backendmaster::GetNodeAddressResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetNodeAddress_, context, request, response, std::move(f));
}

void BackendMasterService::Stub::async::GetNodeAddress(::grpc::ClientContext* context, const ::backendmaster::GetNodeAddressRequest* request, ::backendmaster::GetNodeAddressResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetNodeAddress_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::backendmaster::GetNodeAddressResponse>* BackendMasterService::Stub::PrepareAsyncGetNodeAddressRaw(::grpc::ClientContext* context, const ::backendmaster::GetNodeAddressRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::backendmaster::GetNodeAddressResponse, ::backendmaster::GetNodeAddressRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_GetNodeAddress_, context, request);
}

::grpc::ClientAsyncResponseReader< ::backendmaster::GetNodeAddressResponse>* BackendMasterService::Stub::AsyncGetNodeAddressRaw(::grpc::ClientContext* context, const ::backendmaster::GetNodeAddressRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncGetNodeAddressRaw(context, request, cq);
  result->StartCall();
  return result;
}

BackendMasterService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      BackendMasterService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< BackendMasterService::Service, ::backendmaster::NotifyRecoveryRequest, ::backendmaster::NotifyRecoveryResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](BackendMasterService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::backendmaster::NotifyRecoveryRequest* req,
             ::backendmaster::NotifyRecoveryResponse* resp) {
               return service->NotifyRecovery(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      BackendMasterService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< BackendMasterService::Service, ::backendmaster::PrimaryRequest, ::backendmaster::PrimaryNode, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](BackendMasterService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::backendmaster::PrimaryRequest* req,
             ::backendmaster::PrimaryNode* resp) {
               return service->GetPrimary(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      BackendMasterService_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< BackendMasterService::Service, ::backendmaster::ListNodesRequest, ::backendmaster::NodesList, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](BackendMasterService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::backendmaster::ListNodesRequest* req,
             ::backendmaster::NodesList* resp) {
               return service->ListNodes(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      BackendMasterService_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< BackendMasterService::Service, ::backendmaster::GetNodeAddressRequest, ::backendmaster::GetNodeAddressResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](BackendMasterService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::backendmaster::GetNodeAddressRequest* req,
             ::backendmaster::GetNodeAddressResponse* resp) {
               return service->GetNodeAddress(ctx, req, resp);
             }, this)));
}

BackendMasterService::Service::~Service() {
}

::grpc::Status BackendMasterService::Service::NotifyRecovery(::grpc::ServerContext* context, const ::backendmaster::NotifyRecoveryRequest* request, ::backendmaster::NotifyRecoveryResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status BackendMasterService::Service::GetPrimary(::grpc::ServerContext* context, const ::backendmaster::PrimaryRequest* request, ::backendmaster::PrimaryNode* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status BackendMasterService::Service::ListNodes(::grpc::ServerContext* context, const ::backendmaster::ListNodesRequest* request, ::backendmaster::NodesList* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status BackendMasterService::Service::GetNodeAddress(::grpc::ServerContext* context, const ::backendmaster::GetNodeAddressRequest* request, ::backendmaster::GetNodeAddressResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace backendmaster

