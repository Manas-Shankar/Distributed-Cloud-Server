// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: backend_master_as_server.proto
#ifndef GRPC_backend_5fmaster_5fas_5fserver_2eproto__INCLUDED
#define GRPC_backend_5fmaster_5fas_5fserver_2eproto__INCLUDED

#include "backend_master_as_server.pb.h"

#include <functional>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/proto_utils.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/stub_options.h>
#include <grpcpp/support/sync_stream.h>

namespace backendmaster {

// Service definition
class BackendMasterService final {
 public:
  static constexpr char const* service_full_name() {
    return "backendmaster.BackendMasterService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status NotifyRecovery(::grpc::ClientContext* context, const ::backendmaster::NotifyRecoveryRequest& request, ::backendmaster::NotifyRecoveryResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::backendmaster::NotifyRecoveryResponse>> AsyncNotifyRecovery(::grpc::ClientContext* context, const ::backendmaster::NotifyRecoveryRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::backendmaster::NotifyRecoveryResponse>>(AsyncNotifyRecoveryRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::backendmaster::NotifyRecoveryResponse>> PrepareAsyncNotifyRecovery(::grpc::ClientContext* context, const ::backendmaster::NotifyRecoveryRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::backendmaster::NotifyRecoveryResponse>>(PrepareAsyncNotifyRecoveryRaw(context, request, cq));
    }
    virtual ::grpc::Status GetPrimary(::grpc::ClientContext* context, const ::backendmaster::PrimaryRequest& request, ::backendmaster::PrimaryNode* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::backendmaster::PrimaryNode>> AsyncGetPrimary(::grpc::ClientContext* context, const ::backendmaster::PrimaryRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::backendmaster::PrimaryNode>>(AsyncGetPrimaryRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::backendmaster::PrimaryNode>> PrepareAsyncGetPrimary(::grpc::ClientContext* context, const ::backendmaster::PrimaryRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::backendmaster::PrimaryNode>>(PrepareAsyncGetPrimaryRaw(context, request, cq));
    }
    virtual ::grpc::Status ListNodes(::grpc::ClientContext* context, const ::backendmaster::ListNodesRequest& request, ::backendmaster::NodesList* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::backendmaster::NodesList>> AsyncListNodes(::grpc::ClientContext* context, const ::backendmaster::ListNodesRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::backendmaster::NodesList>>(AsyncListNodesRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::backendmaster::NodesList>> PrepareAsyncListNodes(::grpc::ClientContext* context, const ::backendmaster::ListNodesRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::backendmaster::NodesList>>(PrepareAsyncListNodesRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void NotifyRecovery(::grpc::ClientContext* context, const ::backendmaster::NotifyRecoveryRequest* request, ::backendmaster::NotifyRecoveryResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void NotifyRecovery(::grpc::ClientContext* context, const ::backendmaster::NotifyRecoveryRequest* request, ::backendmaster::NotifyRecoveryResponse* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      virtual void GetPrimary(::grpc::ClientContext* context, const ::backendmaster::PrimaryRequest* request, ::backendmaster::PrimaryNode* response, std::function<void(::grpc::Status)>) = 0;
      virtual void GetPrimary(::grpc::ClientContext* context, const ::backendmaster::PrimaryRequest* request, ::backendmaster::PrimaryNode* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      virtual void ListNodes(::grpc::ClientContext* context, const ::backendmaster::ListNodesRequest* request, ::backendmaster::NodesList* response, std::function<void(::grpc::Status)>) = 0;
      virtual void ListNodes(::grpc::ClientContext* context, const ::backendmaster::ListNodesRequest* request, ::backendmaster::NodesList* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::backendmaster::NotifyRecoveryResponse>* AsyncNotifyRecoveryRaw(::grpc::ClientContext* context, const ::backendmaster::NotifyRecoveryRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::backendmaster::NotifyRecoveryResponse>* PrepareAsyncNotifyRecoveryRaw(::grpc::ClientContext* context, const ::backendmaster::NotifyRecoveryRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::backendmaster::PrimaryNode>* AsyncGetPrimaryRaw(::grpc::ClientContext* context, const ::backendmaster::PrimaryRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::backendmaster::PrimaryNode>* PrepareAsyncGetPrimaryRaw(::grpc::ClientContext* context, const ::backendmaster::PrimaryRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::backendmaster::NodesList>* AsyncListNodesRaw(::grpc::ClientContext* context, const ::backendmaster::ListNodesRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::backendmaster::NodesList>* PrepareAsyncListNodesRaw(::grpc::ClientContext* context, const ::backendmaster::ListNodesRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status NotifyRecovery(::grpc::ClientContext* context, const ::backendmaster::NotifyRecoveryRequest& request, ::backendmaster::NotifyRecoveryResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::backendmaster::NotifyRecoveryResponse>> AsyncNotifyRecovery(::grpc::ClientContext* context, const ::backendmaster::NotifyRecoveryRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::backendmaster::NotifyRecoveryResponse>>(AsyncNotifyRecoveryRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::backendmaster::NotifyRecoveryResponse>> PrepareAsyncNotifyRecovery(::grpc::ClientContext* context, const ::backendmaster::NotifyRecoveryRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::backendmaster::NotifyRecoveryResponse>>(PrepareAsyncNotifyRecoveryRaw(context, request, cq));
    }
    ::grpc::Status GetPrimary(::grpc::ClientContext* context, const ::backendmaster::PrimaryRequest& request, ::backendmaster::PrimaryNode* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::backendmaster::PrimaryNode>> AsyncGetPrimary(::grpc::ClientContext* context, const ::backendmaster::PrimaryRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::backendmaster::PrimaryNode>>(AsyncGetPrimaryRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::backendmaster::PrimaryNode>> PrepareAsyncGetPrimary(::grpc::ClientContext* context, const ::backendmaster::PrimaryRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::backendmaster::PrimaryNode>>(PrepareAsyncGetPrimaryRaw(context, request, cq));
    }
    ::grpc::Status ListNodes(::grpc::ClientContext* context, const ::backendmaster::ListNodesRequest& request, ::backendmaster::NodesList* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::backendmaster::NodesList>> AsyncListNodes(::grpc::ClientContext* context, const ::backendmaster::ListNodesRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::backendmaster::NodesList>>(AsyncListNodesRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::backendmaster::NodesList>> PrepareAsyncListNodes(::grpc::ClientContext* context, const ::backendmaster::ListNodesRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::backendmaster::NodesList>>(PrepareAsyncListNodesRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void NotifyRecovery(::grpc::ClientContext* context, const ::backendmaster::NotifyRecoveryRequest* request, ::backendmaster::NotifyRecoveryResponse* response, std::function<void(::grpc::Status)>) override;
      void NotifyRecovery(::grpc::ClientContext* context, const ::backendmaster::NotifyRecoveryRequest* request, ::backendmaster::NotifyRecoveryResponse* response, ::grpc::ClientUnaryReactor* reactor) override;
      void GetPrimary(::grpc::ClientContext* context, const ::backendmaster::PrimaryRequest* request, ::backendmaster::PrimaryNode* response, std::function<void(::grpc::Status)>) override;
      void GetPrimary(::grpc::ClientContext* context, const ::backendmaster::PrimaryRequest* request, ::backendmaster::PrimaryNode* response, ::grpc::ClientUnaryReactor* reactor) override;
      void ListNodes(::grpc::ClientContext* context, const ::backendmaster::ListNodesRequest* request, ::backendmaster::NodesList* response, std::function<void(::grpc::Status)>) override;
      void ListNodes(::grpc::ClientContext* context, const ::backendmaster::ListNodesRequest* request, ::backendmaster::NodesList* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::backendmaster::NotifyRecoveryResponse>* AsyncNotifyRecoveryRaw(::grpc::ClientContext* context, const ::backendmaster::NotifyRecoveryRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::backendmaster::NotifyRecoveryResponse>* PrepareAsyncNotifyRecoveryRaw(::grpc::ClientContext* context, const ::backendmaster::NotifyRecoveryRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::backendmaster::PrimaryNode>* AsyncGetPrimaryRaw(::grpc::ClientContext* context, const ::backendmaster::PrimaryRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::backendmaster::PrimaryNode>* PrepareAsyncGetPrimaryRaw(::grpc::ClientContext* context, const ::backendmaster::PrimaryRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::backendmaster::NodesList>* AsyncListNodesRaw(::grpc::ClientContext* context, const ::backendmaster::ListNodesRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::backendmaster::NodesList>* PrepareAsyncListNodesRaw(::grpc::ClientContext* context, const ::backendmaster::ListNodesRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_NotifyRecovery_;
    const ::grpc::internal::RpcMethod rpcmethod_GetPrimary_;
    const ::grpc::internal::RpcMethod rpcmethod_ListNodes_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status NotifyRecovery(::grpc::ServerContext* context, const ::backendmaster::NotifyRecoveryRequest* request, ::backendmaster::NotifyRecoveryResponse* response);
    virtual ::grpc::Status GetPrimary(::grpc::ServerContext* context, const ::backendmaster::PrimaryRequest* request, ::backendmaster::PrimaryNode* response);
    virtual ::grpc::Status ListNodes(::grpc::ServerContext* context, const ::backendmaster::ListNodesRequest* request, ::backendmaster::NodesList* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_NotifyRecovery : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_NotifyRecovery() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_NotifyRecovery() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status NotifyRecovery(::grpc::ServerContext* /*context*/, const ::backendmaster::NotifyRecoveryRequest* /*request*/, ::backendmaster::NotifyRecoveryResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestNotifyRecovery(::grpc::ServerContext* context, ::backendmaster::NotifyRecoveryRequest* request, ::grpc::ServerAsyncResponseWriter< ::backendmaster::NotifyRecoveryResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_GetPrimary : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_GetPrimary() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_GetPrimary() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetPrimary(::grpc::ServerContext* /*context*/, const ::backendmaster::PrimaryRequest* /*request*/, ::backendmaster::PrimaryNode* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetPrimary(::grpc::ServerContext* context, ::backendmaster::PrimaryRequest* request, ::grpc::ServerAsyncResponseWriter< ::backendmaster::PrimaryNode>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_ListNodes : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_ListNodes() {
      ::grpc::Service::MarkMethodAsync(2);
    }
    ~WithAsyncMethod_ListNodes() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ListNodes(::grpc::ServerContext* /*context*/, const ::backendmaster::ListNodesRequest* /*request*/, ::backendmaster::NodesList* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestListNodes(::grpc::ServerContext* context, ::backendmaster::ListNodesRequest* request, ::grpc::ServerAsyncResponseWriter< ::backendmaster::NodesList>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(2, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_NotifyRecovery<WithAsyncMethod_GetPrimary<WithAsyncMethod_ListNodes<Service > > > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_NotifyRecovery : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_NotifyRecovery() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::backendmaster::NotifyRecoveryRequest, ::backendmaster::NotifyRecoveryResponse>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::backendmaster::NotifyRecoveryRequest* request, ::backendmaster::NotifyRecoveryResponse* response) { return this->NotifyRecovery(context, request, response); }));}
    void SetMessageAllocatorFor_NotifyRecovery(
        ::grpc::MessageAllocator< ::backendmaster::NotifyRecoveryRequest, ::backendmaster::NotifyRecoveryResponse>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::backendmaster::NotifyRecoveryRequest, ::backendmaster::NotifyRecoveryResponse>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_NotifyRecovery() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status NotifyRecovery(::grpc::ServerContext* /*context*/, const ::backendmaster::NotifyRecoveryRequest* /*request*/, ::backendmaster::NotifyRecoveryResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* NotifyRecovery(
      ::grpc::CallbackServerContext* /*context*/, const ::backendmaster::NotifyRecoveryRequest* /*request*/, ::backendmaster::NotifyRecoveryResponse* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithCallbackMethod_GetPrimary : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_GetPrimary() {
      ::grpc::Service::MarkMethodCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::backendmaster::PrimaryRequest, ::backendmaster::PrimaryNode>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::backendmaster::PrimaryRequest* request, ::backendmaster::PrimaryNode* response) { return this->GetPrimary(context, request, response); }));}
    void SetMessageAllocatorFor_GetPrimary(
        ::grpc::MessageAllocator< ::backendmaster::PrimaryRequest, ::backendmaster::PrimaryNode>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(1);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::backendmaster::PrimaryRequest, ::backendmaster::PrimaryNode>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_GetPrimary() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetPrimary(::grpc::ServerContext* /*context*/, const ::backendmaster::PrimaryRequest* /*request*/, ::backendmaster::PrimaryNode* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* GetPrimary(
      ::grpc::CallbackServerContext* /*context*/, const ::backendmaster::PrimaryRequest* /*request*/, ::backendmaster::PrimaryNode* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithCallbackMethod_ListNodes : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_ListNodes() {
      ::grpc::Service::MarkMethodCallback(2,
          new ::grpc::internal::CallbackUnaryHandler< ::backendmaster::ListNodesRequest, ::backendmaster::NodesList>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::backendmaster::ListNodesRequest* request, ::backendmaster::NodesList* response) { return this->ListNodes(context, request, response); }));}
    void SetMessageAllocatorFor_ListNodes(
        ::grpc::MessageAllocator< ::backendmaster::ListNodesRequest, ::backendmaster::NodesList>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(2);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::backendmaster::ListNodesRequest, ::backendmaster::NodesList>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_ListNodes() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ListNodes(::grpc::ServerContext* /*context*/, const ::backendmaster::ListNodesRequest* /*request*/, ::backendmaster::NodesList* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* ListNodes(
      ::grpc::CallbackServerContext* /*context*/, const ::backendmaster::ListNodesRequest* /*request*/, ::backendmaster::NodesList* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_NotifyRecovery<WithCallbackMethod_GetPrimary<WithCallbackMethod_ListNodes<Service > > > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_NotifyRecovery : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_NotifyRecovery() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_NotifyRecovery() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status NotifyRecovery(::grpc::ServerContext* /*context*/, const ::backendmaster::NotifyRecoveryRequest* /*request*/, ::backendmaster::NotifyRecoveryResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_GetPrimary : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_GetPrimary() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_GetPrimary() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetPrimary(::grpc::ServerContext* /*context*/, const ::backendmaster::PrimaryRequest* /*request*/, ::backendmaster::PrimaryNode* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_ListNodes : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_ListNodes() {
      ::grpc::Service::MarkMethodGeneric(2);
    }
    ~WithGenericMethod_ListNodes() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ListNodes(::grpc::ServerContext* /*context*/, const ::backendmaster::ListNodesRequest* /*request*/, ::backendmaster::NodesList* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_NotifyRecovery : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_NotifyRecovery() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_NotifyRecovery() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status NotifyRecovery(::grpc::ServerContext* /*context*/, const ::backendmaster::NotifyRecoveryRequest* /*request*/, ::backendmaster::NotifyRecoveryResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestNotifyRecovery(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_GetPrimary : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_GetPrimary() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_GetPrimary() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetPrimary(::grpc::ServerContext* /*context*/, const ::backendmaster::PrimaryRequest* /*request*/, ::backendmaster::PrimaryNode* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetPrimary(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_ListNodes : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_ListNodes() {
      ::grpc::Service::MarkMethodRaw(2);
    }
    ~WithRawMethod_ListNodes() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ListNodes(::grpc::ServerContext* /*context*/, const ::backendmaster::ListNodesRequest* /*request*/, ::backendmaster::NodesList* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestListNodes(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(2, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_NotifyRecovery : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_NotifyRecovery() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->NotifyRecovery(context, request, response); }));
    }
    ~WithRawCallbackMethod_NotifyRecovery() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status NotifyRecovery(::grpc::ServerContext* /*context*/, const ::backendmaster::NotifyRecoveryRequest* /*request*/, ::backendmaster::NotifyRecoveryResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* NotifyRecovery(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_GetPrimary : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_GetPrimary() {
      ::grpc::Service::MarkMethodRawCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->GetPrimary(context, request, response); }));
    }
    ~WithRawCallbackMethod_GetPrimary() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetPrimary(::grpc::ServerContext* /*context*/, const ::backendmaster::PrimaryRequest* /*request*/, ::backendmaster::PrimaryNode* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* GetPrimary(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_ListNodes : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_ListNodes() {
      ::grpc::Service::MarkMethodRawCallback(2,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->ListNodes(context, request, response); }));
    }
    ~WithRawCallbackMethod_ListNodes() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ListNodes(::grpc::ServerContext* /*context*/, const ::backendmaster::ListNodesRequest* /*request*/, ::backendmaster::NodesList* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* ListNodes(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_NotifyRecovery : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_NotifyRecovery() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::backendmaster::NotifyRecoveryRequest, ::backendmaster::NotifyRecoveryResponse>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::backendmaster::NotifyRecoveryRequest, ::backendmaster::NotifyRecoveryResponse>* streamer) {
                       return this->StreamedNotifyRecovery(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_NotifyRecovery() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status NotifyRecovery(::grpc::ServerContext* /*context*/, const ::backendmaster::NotifyRecoveryRequest* /*request*/, ::backendmaster::NotifyRecoveryResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedNotifyRecovery(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::backendmaster::NotifyRecoveryRequest,::backendmaster::NotifyRecoveryResponse>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_GetPrimary : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_GetPrimary() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler<
          ::backendmaster::PrimaryRequest, ::backendmaster::PrimaryNode>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::backendmaster::PrimaryRequest, ::backendmaster::PrimaryNode>* streamer) {
                       return this->StreamedGetPrimary(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_GetPrimary() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status GetPrimary(::grpc::ServerContext* /*context*/, const ::backendmaster::PrimaryRequest* /*request*/, ::backendmaster::PrimaryNode* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedGetPrimary(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::backendmaster::PrimaryRequest,::backendmaster::PrimaryNode>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_ListNodes : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_ListNodes() {
      ::grpc::Service::MarkMethodStreamed(2,
        new ::grpc::internal::StreamedUnaryHandler<
          ::backendmaster::ListNodesRequest, ::backendmaster::NodesList>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::backendmaster::ListNodesRequest, ::backendmaster::NodesList>* streamer) {
                       return this->StreamedListNodes(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_ListNodes() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status ListNodes(::grpc::ServerContext* /*context*/, const ::backendmaster::ListNodesRequest* /*request*/, ::backendmaster::NodesList* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedListNodes(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::backendmaster::ListNodesRequest,::backendmaster::NodesList>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_NotifyRecovery<WithStreamedUnaryMethod_GetPrimary<WithStreamedUnaryMethod_ListNodes<Service > > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_NotifyRecovery<WithStreamedUnaryMethod_GetPrimary<WithStreamedUnaryMethod_ListNodes<Service > > > StreamedService;
};

}  // namespace backendmaster


#endif  // GRPC_backend_5fmaster_5fas_5fserver_2eproto__INCLUDED
