// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: frontend-backend_master.proto
#ifndef GRPC_frontend_2dbackend_5fmaster_2eproto__INCLUDED
#define GRPC_frontend_2dbackend_5fmaster_2eproto__INCLUDED

#include "frontend-backend_master.pb.h"

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

namespace penncloud {
namespace frontend {

// Service provided by the Backend Master for frontend servers
class FrontendMasterService final {
 public:
  static constexpr char const* service_full_name() {
    return "penncloud.frontend.FrontendMasterService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    // Registers frontend server to receive updates
    virtual ::grpc::Status RegisterFrontend(::grpc::ClientContext* context, const ::penncloud::frontend::Empty& request, ::penncloud::frontend::Acknowledgment* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::penncloud::frontend::Acknowledgment>> AsyncRegisterFrontend(::grpc::ClientContext* context, const ::penncloud::frontend::Empty& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::penncloud::frontend::Acknowledgment>>(AsyncRegisterFrontendRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::penncloud::frontend::Acknowledgment>> PrepareAsyncRegisterFrontend(::grpc::ClientContext* context, const ::penncloud::frontend::Empty& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::penncloud::frontend::Acknowledgment>>(PrepareAsyncRegisterFrontendRaw(context, request, cq));
    }
    // Asynchronous update about backend nodes' status
    virtual ::grpc::Status ReceiveNodeUpdate(::grpc::ClientContext* context, const ::penncloud::frontend::NodeUpdate& request, ::penncloud::frontend::Acknowledgment* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::penncloud::frontend::Acknowledgment>> AsyncReceiveNodeUpdate(::grpc::ClientContext* context, const ::penncloud::frontend::NodeUpdate& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::penncloud::frontend::Acknowledgment>>(AsyncReceiveNodeUpdateRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::penncloud::frontend::Acknowledgment>> PrepareAsyncReceiveNodeUpdate(::grpc::ClientContext* context, const ::penncloud::frontend::NodeUpdate& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::penncloud::frontend::Acknowledgment>>(PrepareAsyncReceiveNodeUpdateRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      // Registers frontend server to receive updates
      virtual void RegisterFrontend(::grpc::ClientContext* context, const ::penncloud::frontend::Empty* request, ::penncloud::frontend::Acknowledgment* response, std::function<void(::grpc::Status)>) = 0;
      virtual void RegisterFrontend(::grpc::ClientContext* context, const ::penncloud::frontend::Empty* request, ::penncloud::frontend::Acknowledgment* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      // Asynchronous update about backend nodes' status
      virtual void ReceiveNodeUpdate(::grpc::ClientContext* context, const ::penncloud::frontend::NodeUpdate* request, ::penncloud::frontend::Acknowledgment* response, std::function<void(::grpc::Status)>) = 0;
      virtual void ReceiveNodeUpdate(::grpc::ClientContext* context, const ::penncloud::frontend::NodeUpdate* request, ::penncloud::frontend::Acknowledgment* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::penncloud::frontend::Acknowledgment>* AsyncRegisterFrontendRaw(::grpc::ClientContext* context, const ::penncloud::frontend::Empty& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::penncloud::frontend::Acknowledgment>* PrepareAsyncRegisterFrontendRaw(::grpc::ClientContext* context, const ::penncloud::frontend::Empty& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::penncloud::frontend::Acknowledgment>* AsyncReceiveNodeUpdateRaw(::grpc::ClientContext* context, const ::penncloud::frontend::NodeUpdate& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::penncloud::frontend::Acknowledgment>* PrepareAsyncReceiveNodeUpdateRaw(::grpc::ClientContext* context, const ::penncloud::frontend::NodeUpdate& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status RegisterFrontend(::grpc::ClientContext* context, const ::penncloud::frontend::Empty& request, ::penncloud::frontend::Acknowledgment* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::penncloud::frontend::Acknowledgment>> AsyncRegisterFrontend(::grpc::ClientContext* context, const ::penncloud::frontend::Empty& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::penncloud::frontend::Acknowledgment>>(AsyncRegisterFrontendRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::penncloud::frontend::Acknowledgment>> PrepareAsyncRegisterFrontend(::grpc::ClientContext* context, const ::penncloud::frontend::Empty& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::penncloud::frontend::Acknowledgment>>(PrepareAsyncRegisterFrontendRaw(context, request, cq));
    }
    ::grpc::Status ReceiveNodeUpdate(::grpc::ClientContext* context, const ::penncloud::frontend::NodeUpdate& request, ::penncloud::frontend::Acknowledgment* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::penncloud::frontend::Acknowledgment>> AsyncReceiveNodeUpdate(::grpc::ClientContext* context, const ::penncloud::frontend::NodeUpdate& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::penncloud::frontend::Acknowledgment>>(AsyncReceiveNodeUpdateRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::penncloud::frontend::Acknowledgment>> PrepareAsyncReceiveNodeUpdate(::grpc::ClientContext* context, const ::penncloud::frontend::NodeUpdate& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::penncloud::frontend::Acknowledgment>>(PrepareAsyncReceiveNodeUpdateRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void RegisterFrontend(::grpc::ClientContext* context, const ::penncloud::frontend::Empty* request, ::penncloud::frontend::Acknowledgment* response, std::function<void(::grpc::Status)>) override;
      void RegisterFrontend(::grpc::ClientContext* context, const ::penncloud::frontend::Empty* request, ::penncloud::frontend::Acknowledgment* response, ::grpc::ClientUnaryReactor* reactor) override;
      void ReceiveNodeUpdate(::grpc::ClientContext* context, const ::penncloud::frontend::NodeUpdate* request, ::penncloud::frontend::Acknowledgment* response, std::function<void(::grpc::Status)>) override;
      void ReceiveNodeUpdate(::grpc::ClientContext* context, const ::penncloud::frontend::NodeUpdate* request, ::penncloud::frontend::Acknowledgment* response, ::grpc::ClientUnaryReactor* reactor) override;
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
    ::grpc::ClientAsyncResponseReader< ::penncloud::frontend::Acknowledgment>* AsyncRegisterFrontendRaw(::grpc::ClientContext* context, const ::penncloud::frontend::Empty& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::penncloud::frontend::Acknowledgment>* PrepareAsyncRegisterFrontendRaw(::grpc::ClientContext* context, const ::penncloud::frontend::Empty& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::penncloud::frontend::Acknowledgment>* AsyncReceiveNodeUpdateRaw(::grpc::ClientContext* context, const ::penncloud::frontend::NodeUpdate& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::penncloud::frontend::Acknowledgment>* PrepareAsyncReceiveNodeUpdateRaw(::grpc::ClientContext* context, const ::penncloud::frontend::NodeUpdate& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_RegisterFrontend_;
    const ::grpc::internal::RpcMethod rpcmethod_ReceiveNodeUpdate_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    // Registers frontend server to receive updates
    virtual ::grpc::Status RegisterFrontend(::grpc::ServerContext* context, const ::penncloud::frontend::Empty* request, ::penncloud::frontend::Acknowledgment* response);
    // Asynchronous update about backend nodes' status
    virtual ::grpc::Status ReceiveNodeUpdate(::grpc::ServerContext* context, const ::penncloud::frontend::NodeUpdate* request, ::penncloud::frontend::Acknowledgment* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_RegisterFrontend : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_RegisterFrontend() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_RegisterFrontend() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status RegisterFrontend(::grpc::ServerContext* /*context*/, const ::penncloud::frontend::Empty* /*request*/, ::penncloud::frontend::Acknowledgment* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestRegisterFrontend(::grpc::ServerContext* context, ::penncloud::frontend::Empty* request, ::grpc::ServerAsyncResponseWriter< ::penncloud::frontend::Acknowledgment>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_ReceiveNodeUpdate : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_ReceiveNodeUpdate() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_ReceiveNodeUpdate() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ReceiveNodeUpdate(::grpc::ServerContext* /*context*/, const ::penncloud::frontend::NodeUpdate* /*request*/, ::penncloud::frontend::Acknowledgment* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestReceiveNodeUpdate(::grpc::ServerContext* context, ::penncloud::frontend::NodeUpdate* request, ::grpc::ServerAsyncResponseWriter< ::penncloud::frontend::Acknowledgment>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_RegisterFrontend<WithAsyncMethod_ReceiveNodeUpdate<Service > > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_RegisterFrontend : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_RegisterFrontend() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::penncloud::frontend::Empty, ::penncloud::frontend::Acknowledgment>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::penncloud::frontend::Empty* request, ::penncloud::frontend::Acknowledgment* response) { return this->RegisterFrontend(context, request, response); }));}
    void SetMessageAllocatorFor_RegisterFrontend(
        ::grpc::MessageAllocator< ::penncloud::frontend::Empty, ::penncloud::frontend::Acknowledgment>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::penncloud::frontend::Empty, ::penncloud::frontend::Acknowledgment>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_RegisterFrontend() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status RegisterFrontend(::grpc::ServerContext* /*context*/, const ::penncloud::frontend::Empty* /*request*/, ::penncloud::frontend::Acknowledgment* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* RegisterFrontend(
      ::grpc::CallbackServerContext* /*context*/, const ::penncloud::frontend::Empty* /*request*/, ::penncloud::frontend::Acknowledgment* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithCallbackMethod_ReceiveNodeUpdate : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_ReceiveNodeUpdate() {
      ::grpc::Service::MarkMethodCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::penncloud::frontend::NodeUpdate, ::penncloud::frontend::Acknowledgment>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::penncloud::frontend::NodeUpdate* request, ::penncloud::frontend::Acknowledgment* response) { return this->ReceiveNodeUpdate(context, request, response); }));}
    void SetMessageAllocatorFor_ReceiveNodeUpdate(
        ::grpc::MessageAllocator< ::penncloud::frontend::NodeUpdate, ::penncloud::frontend::Acknowledgment>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(1);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::penncloud::frontend::NodeUpdate, ::penncloud::frontend::Acknowledgment>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_ReceiveNodeUpdate() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ReceiveNodeUpdate(::grpc::ServerContext* /*context*/, const ::penncloud::frontend::NodeUpdate* /*request*/, ::penncloud::frontend::Acknowledgment* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* ReceiveNodeUpdate(
      ::grpc::CallbackServerContext* /*context*/, const ::penncloud::frontend::NodeUpdate* /*request*/, ::penncloud::frontend::Acknowledgment* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_RegisterFrontend<WithCallbackMethod_ReceiveNodeUpdate<Service > > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_RegisterFrontend : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_RegisterFrontend() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_RegisterFrontend() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status RegisterFrontend(::grpc::ServerContext* /*context*/, const ::penncloud::frontend::Empty* /*request*/, ::penncloud::frontend::Acknowledgment* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_ReceiveNodeUpdate : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_ReceiveNodeUpdate() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_ReceiveNodeUpdate() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ReceiveNodeUpdate(::grpc::ServerContext* /*context*/, const ::penncloud::frontend::NodeUpdate* /*request*/, ::penncloud::frontend::Acknowledgment* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_RegisterFrontend : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_RegisterFrontend() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_RegisterFrontend() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status RegisterFrontend(::grpc::ServerContext* /*context*/, const ::penncloud::frontend::Empty* /*request*/, ::penncloud::frontend::Acknowledgment* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestRegisterFrontend(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_ReceiveNodeUpdate : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_ReceiveNodeUpdate() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_ReceiveNodeUpdate() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ReceiveNodeUpdate(::grpc::ServerContext* /*context*/, const ::penncloud::frontend::NodeUpdate* /*request*/, ::penncloud::frontend::Acknowledgment* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestReceiveNodeUpdate(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_RegisterFrontend : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_RegisterFrontend() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->RegisterFrontend(context, request, response); }));
    }
    ~WithRawCallbackMethod_RegisterFrontend() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status RegisterFrontend(::grpc::ServerContext* /*context*/, const ::penncloud::frontend::Empty* /*request*/, ::penncloud::frontend::Acknowledgment* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* RegisterFrontend(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_ReceiveNodeUpdate : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_ReceiveNodeUpdate() {
      ::grpc::Service::MarkMethodRawCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->ReceiveNodeUpdate(context, request, response); }));
    }
    ~WithRawCallbackMethod_ReceiveNodeUpdate() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status ReceiveNodeUpdate(::grpc::ServerContext* /*context*/, const ::penncloud::frontend::NodeUpdate* /*request*/, ::penncloud::frontend::Acknowledgment* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* ReceiveNodeUpdate(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_RegisterFrontend : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_RegisterFrontend() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::penncloud::frontend::Empty, ::penncloud::frontend::Acknowledgment>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::penncloud::frontend::Empty, ::penncloud::frontend::Acknowledgment>* streamer) {
                       return this->StreamedRegisterFrontend(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_RegisterFrontend() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status RegisterFrontend(::grpc::ServerContext* /*context*/, const ::penncloud::frontend::Empty* /*request*/, ::penncloud::frontend::Acknowledgment* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedRegisterFrontend(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::penncloud::frontend::Empty,::penncloud::frontend::Acknowledgment>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_ReceiveNodeUpdate : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_ReceiveNodeUpdate() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler<
          ::penncloud::frontend::NodeUpdate, ::penncloud::frontend::Acknowledgment>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::penncloud::frontend::NodeUpdate, ::penncloud::frontend::Acknowledgment>* streamer) {
                       return this->StreamedReceiveNodeUpdate(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_ReceiveNodeUpdate() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status ReceiveNodeUpdate(::grpc::ServerContext* /*context*/, const ::penncloud::frontend::NodeUpdate* /*request*/, ::penncloud::frontend::Acknowledgment* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedReceiveNodeUpdate(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::penncloud::frontend::NodeUpdate,::penncloud::frontend::Acknowledgment>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_RegisterFrontend<WithStreamedUnaryMethod_ReceiveNodeUpdate<Service > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_RegisterFrontend<WithStreamedUnaryMethod_ReceiveNodeUpdate<Service > > StreamedService;
};

}  // namespace frontend
}  // namespace penncloud


#endif  // GRPC_frontend_2dbackend_5fmaster_2eproto__INCLUDED
