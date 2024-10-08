// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: webmailgrpc.proto
// Protobuf C++ Version: 5.26.1

#ifndef GOOGLE_PROTOBUF_INCLUDED_webmailgrpc_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_webmailgrpc_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include "google/protobuf/port_def.inc"
#if PROTOBUF_VERSION != 5026001
#error "Protobuf C++ gencode is built with an incompatible version of"
#error "Protobuf C++ headers/runtime. See"
#error "https://protobuf.dev/support/cross-version-runtime-guarantee/#cpp"
#endif
#include "google/protobuf/port_undef.inc"
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_tctable_decl.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_webmailgrpc_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_webmailgrpc_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_webmailgrpc_2eproto;
namespace webmailgrpc {
class CommandRequest;
struct CommandRequestDefaultTypeInternal;
extern CommandRequestDefaultTypeInternal _CommandRequest_default_instance_;
class CommandResponse;
struct CommandResponseDefaultTypeInternal;
extern CommandResponseDefaultTypeInternal _CommandResponse_default_instance_;
}  // namespace webmailgrpc
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace webmailgrpc {

// ===================================================================


// -------------------------------------------------------------------

class CommandResponse final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:webmailgrpc.CommandResponse) */ {
 public:
  inline CommandResponse() : CommandResponse(nullptr) {}
  ~CommandResponse() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR CommandResponse(
      ::google::protobuf::internal::ConstantInitialized);

  inline CommandResponse(const CommandResponse& from) : CommandResponse(nullptr, from) {}
  inline CommandResponse(CommandResponse&& from) noexcept
      : CommandResponse(nullptr, std::move(from)) {}
  inline CommandResponse& operator=(const CommandResponse& from) {
    CopyFrom(from);
    return *this;
  }
  inline CommandResponse& operator=(CommandResponse&& from) noexcept {
    if (this == &from) return *this;
    if (GetArena() == from.GetArena()
#ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetArena() != nullptr
#endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const CommandResponse& default_instance() {
    return *internal_default_instance();
  }
  static inline const CommandResponse* internal_default_instance() {
    return reinterpret_cast<const CommandResponse*>(
        &_CommandResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 1;
  friend void swap(CommandResponse& a, CommandResponse& b) { a.Swap(&b); }
  inline void Swap(CommandResponse* other) {
    if (other == this) return;
#ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() != nullptr && GetArena() == other->GetArena()) {
#else   // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() == other->GetArena()) {
#endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(CommandResponse* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  CommandResponse* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::Message::DefaultConstruct<CommandResponse>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const CommandResponse& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const CommandResponse& from) { CommandResponse::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::google::protobuf::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void InternalSwap(CommandResponse* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "webmailgrpc.CommandResponse"; }

 protected:
  explicit CommandResponse(::google::protobuf::Arena* arena);
  CommandResponse(::google::protobuf::Arena* arena, const CommandResponse& from);
  CommandResponse(::google::protobuf::Arena* arena, CommandResponse&& from) noexcept
      : CommandResponse(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::MessageLite::ClassData* GetClassData()
      const final;

 public:
  ::google::protobuf::Metadata GetMetadata() const final;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kResponseFieldNumber = 1,
    kSuccessFieldNumber = 2,
  };
  // string response = 1;
  void clear_response() ;
  const std::string& response() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_response(Arg_&& arg, Args_... args);
  std::string* mutable_response();
  PROTOBUF_NODISCARD std::string* release_response();
  void set_allocated_response(std::string* value);

  private:
  const std::string& _internal_response() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_response(
      const std::string& value);
  std::string* _internal_mutable_response();

  public:
  // bool success = 2;
  void clear_success() ;
  bool success() const;
  void set_success(bool value);

  private:
  bool _internal_success() const;
  void _internal_set_success(bool value);

  public:
  // @@protoc_insertion_point(class_scope:webmailgrpc.CommandResponse)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      1, 2, 0,
      44, 2>
      _table_;
  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from);
    ::google::protobuf::internal::ArenaStringPtr response_;
    bool success_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_webmailgrpc_2eproto;
};
// -------------------------------------------------------------------

class CommandRequest final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:webmailgrpc.CommandRequest) */ {
 public:
  inline CommandRequest() : CommandRequest(nullptr) {}
  ~CommandRequest() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR CommandRequest(
      ::google::protobuf::internal::ConstantInitialized);

  inline CommandRequest(const CommandRequest& from) : CommandRequest(nullptr, from) {}
  inline CommandRequest(CommandRequest&& from) noexcept
      : CommandRequest(nullptr, std::move(from)) {}
  inline CommandRequest& operator=(const CommandRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline CommandRequest& operator=(CommandRequest&& from) noexcept {
    if (this == &from) return *this;
    if (GetArena() == from.GetArena()
#ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetArena() != nullptr
#endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const CommandRequest& default_instance() {
    return *internal_default_instance();
  }
  static inline const CommandRequest* internal_default_instance() {
    return reinterpret_cast<const CommandRequest*>(
        &_CommandRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(CommandRequest& a, CommandRequest& b) { a.Swap(&b); }
  inline void Swap(CommandRequest* other) {
    if (other == this) return;
#ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() != nullptr && GetArena() == other->GetArena()) {
#else   // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() == other->GetArena()) {
#endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(CommandRequest* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  CommandRequest* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::Message::DefaultConstruct<CommandRequest>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const CommandRequest& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const CommandRequest& from) { CommandRequest::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::google::protobuf::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void InternalSwap(CommandRequest* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "webmailgrpc.CommandRequest"; }

 protected:
  explicit CommandRequest(::google::protobuf::Arena* arena);
  CommandRequest(::google::protobuf::Arena* arena, const CommandRequest& from);
  CommandRequest(::google::protobuf::Arena* arena, CommandRequest&& from) noexcept
      : CommandRequest(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::MessageLite::ClassData* GetClassData()
      const final;

 public:
  ::google::protobuf::Metadata GetMetadata() const final;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kSessionIdFieldNumber = 1,
    kCommandFieldNumber = 2,
  };
  // string session_id = 1;
  void clear_session_id() ;
  const std::string& session_id() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_session_id(Arg_&& arg, Args_... args);
  std::string* mutable_session_id();
  PROTOBUF_NODISCARD std::string* release_session_id();
  void set_allocated_session_id(std::string* value);

  private:
  const std::string& _internal_session_id() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_session_id(
      const std::string& value);
  std::string* _internal_mutable_session_id();

  public:
  // string command = 2;
  void clear_command() ;
  const std::string& command() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_command(Arg_&& arg, Args_... args);
  std::string* mutable_command();
  PROTOBUF_NODISCARD std::string* release_command();
  void set_allocated_command(std::string* value);

  private:
  const std::string& _internal_command() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_command(
      const std::string& value);
  std::string* _internal_mutable_command();

  public:
  // @@protoc_insertion_point(class_scope:webmailgrpc.CommandRequest)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      1, 2, 0,
      52, 2>
      _table_;
  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from);
    ::google::protobuf::internal::ArenaStringPtr session_id_;
    ::google::protobuf::internal::ArenaStringPtr command_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_webmailgrpc_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// CommandRequest

// string session_id = 1;
inline void CommandRequest::clear_session_id() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.session_id_.ClearToEmpty();
}
inline const std::string& CommandRequest::session_id() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:webmailgrpc.CommandRequest.session_id)
  return _internal_session_id();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void CommandRequest::set_session_id(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.session_id_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:webmailgrpc.CommandRequest.session_id)
}
inline std::string* CommandRequest::mutable_session_id() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_session_id();
  // @@protoc_insertion_point(field_mutable:webmailgrpc.CommandRequest.session_id)
  return _s;
}
inline const std::string& CommandRequest::_internal_session_id() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.session_id_.Get();
}
inline void CommandRequest::_internal_set_session_id(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.session_id_.Set(value, GetArena());
}
inline std::string* CommandRequest::_internal_mutable_session_id() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  return _impl_.session_id_.Mutable( GetArena());
}
inline std::string* CommandRequest::release_session_id() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:webmailgrpc.CommandRequest.session_id)
  return _impl_.session_id_.Release();
}
inline void CommandRequest::set_allocated_session_id(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.session_id_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.session_id_.IsDefault()) {
          _impl_.session_id_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:webmailgrpc.CommandRequest.session_id)
}

// string command = 2;
inline void CommandRequest::clear_command() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.command_.ClearToEmpty();
}
inline const std::string& CommandRequest::command() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:webmailgrpc.CommandRequest.command)
  return _internal_command();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void CommandRequest::set_command(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.command_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:webmailgrpc.CommandRequest.command)
}
inline std::string* CommandRequest::mutable_command() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_command();
  // @@protoc_insertion_point(field_mutable:webmailgrpc.CommandRequest.command)
  return _s;
}
inline const std::string& CommandRequest::_internal_command() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.command_.Get();
}
inline void CommandRequest::_internal_set_command(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.command_.Set(value, GetArena());
}
inline std::string* CommandRequest::_internal_mutable_command() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  return _impl_.command_.Mutable( GetArena());
}
inline std::string* CommandRequest::release_command() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:webmailgrpc.CommandRequest.command)
  return _impl_.command_.Release();
}
inline void CommandRequest::set_allocated_command(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.command_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.command_.IsDefault()) {
          _impl_.command_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:webmailgrpc.CommandRequest.command)
}

// -------------------------------------------------------------------

// CommandResponse

// string response = 1;
inline void CommandResponse::clear_response() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.response_.ClearToEmpty();
}
inline const std::string& CommandResponse::response() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:webmailgrpc.CommandResponse.response)
  return _internal_response();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void CommandResponse::set_response(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.response_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:webmailgrpc.CommandResponse.response)
}
inline std::string* CommandResponse::mutable_response() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_response();
  // @@protoc_insertion_point(field_mutable:webmailgrpc.CommandResponse.response)
  return _s;
}
inline const std::string& CommandResponse::_internal_response() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.response_.Get();
}
inline void CommandResponse::_internal_set_response(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.response_.Set(value, GetArena());
}
inline std::string* CommandResponse::_internal_mutable_response() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  return _impl_.response_.Mutable( GetArena());
}
inline std::string* CommandResponse::release_response() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:webmailgrpc.CommandResponse.response)
  return _impl_.response_.Release();
}
inline void CommandResponse::set_allocated_response(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.response_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.response_.IsDefault()) {
          _impl_.response_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:webmailgrpc.CommandResponse.response)
}

// bool success = 2;
inline void CommandResponse::clear_success() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.success_ = false;
}
inline bool CommandResponse::success() const {
  // @@protoc_insertion_point(field_get:webmailgrpc.CommandResponse.success)
  return _internal_success();
}
inline void CommandResponse::set_success(bool value) {
  _internal_set_success(value);
  // @@protoc_insertion_point(field_set:webmailgrpc.CommandResponse.success)
}
inline bool CommandResponse::_internal_success() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.success_;
}
inline void CommandResponse::_internal_set_success(bool value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.success_ = value;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace webmailgrpc


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_webmailgrpc_2eproto_2epb_2eh
