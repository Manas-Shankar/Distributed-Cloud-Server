// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: kv_admin_console.proto
// Protobuf C++ Version: 5.26.1

#ifndef GOOGLE_PROTOBUF_INCLUDED_kv_5fadmin_5fconsole_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_kv_5fadmin_5fconsole_2eproto_2epb_2eh

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
#include "google/protobuf/generated_message_bases.h"
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

#define PROTOBUF_INTERNAL_EXPORT_kv_5fadmin_5fconsole_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_kv_5fadmin_5fconsole_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_kv_5fadmin_5fconsole_2eproto;
namespace admin {
class GetAllRequest;
struct GetAllRequestDefaultTypeInternal;
extern GetAllRequestDefaultTypeInternal _GetAllRequest_default_instance_;
class GetAllResponse;
struct GetAllResponseDefaultTypeInternal;
extern GetAllResponseDefaultTypeInternal _GetAllResponse_default_instance_;
class KeyValue;
struct KeyValueDefaultTypeInternal;
extern KeyValueDefaultTypeInternal _KeyValue_default_instance_;
}  // namespace admin
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace admin {

// ===================================================================


// -------------------------------------------------------------------

class KeyValue final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:admin.KeyValue) */ {
 public:
  inline KeyValue() : KeyValue(nullptr) {}
  ~KeyValue() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR KeyValue(
      ::google::protobuf::internal::ConstantInitialized);

  inline KeyValue(const KeyValue& from) : KeyValue(nullptr, from) {}
  inline KeyValue(KeyValue&& from) noexcept
      : KeyValue(nullptr, std::move(from)) {}
  inline KeyValue& operator=(const KeyValue& from) {
    CopyFrom(from);
    return *this;
  }
  inline KeyValue& operator=(KeyValue&& from) noexcept {
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
  static const KeyValue& default_instance() {
    return *internal_default_instance();
  }
  static inline const KeyValue* internal_default_instance() {
    return reinterpret_cast<const KeyValue*>(
        &_KeyValue_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 2;
  friend void swap(KeyValue& a, KeyValue& b) { a.Swap(&b); }
  inline void Swap(KeyValue* other) {
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
  void UnsafeArenaSwap(KeyValue* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  KeyValue* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::Message::DefaultConstruct<KeyValue>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const KeyValue& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const KeyValue& from) { KeyValue::MergeImpl(*this, from); }

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
  void InternalSwap(KeyValue* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "admin.KeyValue"; }

 protected:
  explicit KeyValue(::google::protobuf::Arena* arena);
  KeyValue(::google::protobuf::Arena* arena, const KeyValue& from);
  KeyValue(::google::protobuf::Arena* arena, KeyValue&& from) noexcept
      : KeyValue(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::MessageLite::ClassData* GetClassData()
      const final;

 public:
  ::google::protobuf::Metadata GetMetadata() const final;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kRowFieldNumber = 1,
    kColumnFieldNumber = 2,
    kValueFieldNumber = 3,
  };
  // string row = 1;
  void clear_row() ;
  const std::string& row() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_row(Arg_&& arg, Args_... args);
  std::string* mutable_row();
  PROTOBUF_NODISCARD std::string* release_row();
  void set_allocated_row(std::string* value);

  private:
  const std::string& _internal_row() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_row(
      const std::string& value);
  std::string* _internal_mutable_row();

  public:
  // string column = 2;
  void clear_column() ;
  const std::string& column() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_column(Arg_&& arg, Args_... args);
  std::string* mutable_column();
  PROTOBUF_NODISCARD std::string* release_column();
  void set_allocated_column(std::string* value);

  private:
  const std::string& _internal_column() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_column(
      const std::string& value);
  std::string* _internal_mutable_column();

  public:
  // string value = 3;
  void clear_value() ;
  const std::string& value() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_value(Arg_&& arg, Args_... args);
  std::string* mutable_value();
  PROTOBUF_NODISCARD std::string* release_value();
  void set_allocated_value(std::string* value);

  private:
  const std::string& _internal_value() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_value(
      const std::string& value);
  std::string* _internal_mutable_value();

  public:
  // @@protoc_insertion_point(class_scope:admin.KeyValue)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      2, 3, 0,
      37, 2>
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
    ::google::protobuf::internal::ArenaStringPtr row_;
    ::google::protobuf::internal::ArenaStringPtr column_;
    ::google::protobuf::internal::ArenaStringPtr value_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_kv_5fadmin_5fconsole_2eproto;
};
// -------------------------------------------------------------------

class GetAllRequest final : public ::google::protobuf::internal::ZeroFieldsBase
/* @@protoc_insertion_point(class_definition:admin.GetAllRequest) */ {
 public:
  inline GetAllRequest() : GetAllRequest(nullptr) {}
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR GetAllRequest(
      ::google::protobuf::internal::ConstantInitialized);

  inline GetAllRequest(const GetAllRequest& from) : GetAllRequest(nullptr, from) {}
  inline GetAllRequest(GetAllRequest&& from) noexcept
      : GetAllRequest(nullptr, std::move(from)) {}
  inline GetAllRequest& operator=(const GetAllRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline GetAllRequest& operator=(GetAllRequest&& from) noexcept {
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
  static const GetAllRequest& default_instance() {
    return *internal_default_instance();
  }
  static inline const GetAllRequest* internal_default_instance() {
    return reinterpret_cast<const GetAllRequest*>(
        &_GetAllRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(GetAllRequest& a, GetAllRequest& b) { a.Swap(&b); }
  inline void Swap(GetAllRequest* other) {
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
  void UnsafeArenaSwap(GetAllRequest* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  GetAllRequest* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::internal::ZeroFieldsBase::DefaultConstruct<GetAllRequest>(arena);
  }
  using ::google::protobuf::internal::ZeroFieldsBase::CopyFrom;
  inline void CopyFrom(const GetAllRequest& from) {
    ::google::protobuf::internal::ZeroFieldsBase::CopyImpl(*this, from);
  }
  using ::google::protobuf::internal::ZeroFieldsBase::MergeFrom;
  void MergeFrom(const GetAllRequest& from) {
    ::google::protobuf::internal::ZeroFieldsBase::MergeImpl(*this, from);
  }

  public:
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "admin.GetAllRequest"; }

 protected:
  explicit GetAllRequest(::google::protobuf::Arena* arena);
  GetAllRequest(::google::protobuf::Arena* arena, const GetAllRequest& from);
  GetAllRequest(::google::protobuf::Arena* arena, GetAllRequest&& from) noexcept
      : GetAllRequest(arena) {
    *this = ::std::move(from);
  }

 public:
  ::google::protobuf::Metadata GetMetadata() const final;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  // @@protoc_insertion_point(class_scope:admin.GetAllRequest)
 private:
  class _Internal;
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
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  friend struct ::TableStruct_kv_5fadmin_5fconsole_2eproto;
};
// -------------------------------------------------------------------

class GetAllResponse final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:admin.GetAllResponse) */ {
 public:
  inline GetAllResponse() : GetAllResponse(nullptr) {}
  ~GetAllResponse() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR GetAllResponse(
      ::google::protobuf::internal::ConstantInitialized);

  inline GetAllResponse(const GetAllResponse& from) : GetAllResponse(nullptr, from) {}
  inline GetAllResponse(GetAllResponse&& from) noexcept
      : GetAllResponse(nullptr, std::move(from)) {}
  inline GetAllResponse& operator=(const GetAllResponse& from) {
    CopyFrom(from);
    return *this;
  }
  inline GetAllResponse& operator=(GetAllResponse&& from) noexcept {
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
  static const GetAllResponse& default_instance() {
    return *internal_default_instance();
  }
  static inline const GetAllResponse* internal_default_instance() {
    return reinterpret_cast<const GetAllResponse*>(
        &_GetAllResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 1;
  friend void swap(GetAllResponse& a, GetAllResponse& b) { a.Swap(&b); }
  inline void Swap(GetAllResponse* other) {
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
  void UnsafeArenaSwap(GetAllResponse* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  GetAllResponse* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::Message::DefaultConstruct<GetAllResponse>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const GetAllResponse& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const GetAllResponse& from) { GetAllResponse::MergeImpl(*this, from); }

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
  void InternalSwap(GetAllResponse* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "admin.GetAllResponse"; }

 protected:
  explicit GetAllResponse(::google::protobuf::Arena* arena);
  GetAllResponse(::google::protobuf::Arena* arena, const GetAllResponse& from);
  GetAllResponse(::google::protobuf::Arena* arena, GetAllResponse&& from) noexcept
      : GetAllResponse(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::MessageLite::ClassData* GetClassData()
      const final;

 public:
  ::google::protobuf::Metadata GetMetadata() const final;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kPairsFieldNumber = 3,
    kMessageFieldNumber = 2,
    kSuccessFieldNumber = 1,
  };
  // repeated .admin.KeyValue pairs = 3;
  int pairs_size() const;
  private:
  int _internal_pairs_size() const;

  public:
  void clear_pairs() ;
  ::admin::KeyValue* mutable_pairs(int index);
  ::google::protobuf::RepeatedPtrField<::admin::KeyValue>* mutable_pairs();

  private:
  const ::google::protobuf::RepeatedPtrField<::admin::KeyValue>& _internal_pairs() const;
  ::google::protobuf::RepeatedPtrField<::admin::KeyValue>* _internal_mutable_pairs();
  public:
  const ::admin::KeyValue& pairs(int index) const;
  ::admin::KeyValue* add_pairs();
  const ::google::protobuf::RepeatedPtrField<::admin::KeyValue>& pairs() const;
  // string message = 2;
  void clear_message() ;
  const std::string& message() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_message(Arg_&& arg, Args_... args);
  std::string* mutable_message();
  PROTOBUF_NODISCARD std::string* release_message();
  void set_allocated_message(std::string* value);

  private:
  const std::string& _internal_message() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_message(
      const std::string& value);
  std::string* _internal_mutable_message();

  public:
  // bool success = 1;
  void clear_success() ;
  bool success() const;
  void set_success(bool value);

  private:
  bool _internal_success() const;
  void _internal_set_success(bool value);

  public:
  // @@protoc_insertion_point(class_scope:admin.GetAllResponse)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      2, 3, 1,
      36, 2>
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
    ::google::protobuf::RepeatedPtrField< ::admin::KeyValue > pairs_;
    ::google::protobuf::internal::ArenaStringPtr message_;
    bool success_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_kv_5fadmin_5fconsole_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// GetAllRequest

// -------------------------------------------------------------------

// GetAllResponse

// bool success = 1;
inline void GetAllResponse::clear_success() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.success_ = false;
}
inline bool GetAllResponse::success() const {
  // @@protoc_insertion_point(field_get:admin.GetAllResponse.success)
  return _internal_success();
}
inline void GetAllResponse::set_success(bool value) {
  _internal_set_success(value);
  // @@protoc_insertion_point(field_set:admin.GetAllResponse.success)
}
inline bool GetAllResponse::_internal_success() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.success_;
}
inline void GetAllResponse::_internal_set_success(bool value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.success_ = value;
}

// string message = 2;
inline void GetAllResponse::clear_message() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.message_.ClearToEmpty();
}
inline const std::string& GetAllResponse::message() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:admin.GetAllResponse.message)
  return _internal_message();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void GetAllResponse::set_message(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.message_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:admin.GetAllResponse.message)
}
inline std::string* GetAllResponse::mutable_message() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_message();
  // @@protoc_insertion_point(field_mutable:admin.GetAllResponse.message)
  return _s;
}
inline const std::string& GetAllResponse::_internal_message() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.message_.Get();
}
inline void GetAllResponse::_internal_set_message(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.message_.Set(value, GetArena());
}
inline std::string* GetAllResponse::_internal_mutable_message() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  return _impl_.message_.Mutable( GetArena());
}
inline std::string* GetAllResponse::release_message() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:admin.GetAllResponse.message)
  return _impl_.message_.Release();
}
inline void GetAllResponse::set_allocated_message(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.message_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.message_.IsDefault()) {
          _impl_.message_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:admin.GetAllResponse.message)
}

// repeated .admin.KeyValue pairs = 3;
inline int GetAllResponse::_internal_pairs_size() const {
  return _internal_pairs().size();
}
inline int GetAllResponse::pairs_size() const {
  return _internal_pairs_size();
}
inline void GetAllResponse::clear_pairs() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.pairs_.Clear();
}
inline ::admin::KeyValue* GetAllResponse::mutable_pairs(int index)
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_mutable:admin.GetAllResponse.pairs)
  return _internal_mutable_pairs()->Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField<::admin::KeyValue>* GetAllResponse::mutable_pairs()
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_mutable_list:admin.GetAllResponse.pairs)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  return _internal_mutable_pairs();
}
inline const ::admin::KeyValue& GetAllResponse::pairs(int index) const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:admin.GetAllResponse.pairs)
  return _internal_pairs().Get(index);
}
inline ::admin::KeyValue* GetAllResponse::add_pairs() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::admin::KeyValue* _add = _internal_mutable_pairs()->Add();
  // @@protoc_insertion_point(field_add:admin.GetAllResponse.pairs)
  return _add;
}
inline const ::google::protobuf::RepeatedPtrField<::admin::KeyValue>& GetAllResponse::pairs() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_list:admin.GetAllResponse.pairs)
  return _internal_pairs();
}
inline const ::google::protobuf::RepeatedPtrField<::admin::KeyValue>&
GetAllResponse::_internal_pairs() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.pairs_;
}
inline ::google::protobuf::RepeatedPtrField<::admin::KeyValue>*
GetAllResponse::_internal_mutable_pairs() {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return &_impl_.pairs_;
}

// -------------------------------------------------------------------

// KeyValue

// string row = 1;
inline void KeyValue::clear_row() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.row_.ClearToEmpty();
}
inline const std::string& KeyValue::row() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:admin.KeyValue.row)
  return _internal_row();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void KeyValue::set_row(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.row_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:admin.KeyValue.row)
}
inline std::string* KeyValue::mutable_row() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_row();
  // @@protoc_insertion_point(field_mutable:admin.KeyValue.row)
  return _s;
}
inline const std::string& KeyValue::_internal_row() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.row_.Get();
}
inline void KeyValue::_internal_set_row(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.row_.Set(value, GetArena());
}
inline std::string* KeyValue::_internal_mutable_row() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  return _impl_.row_.Mutable( GetArena());
}
inline std::string* KeyValue::release_row() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:admin.KeyValue.row)
  return _impl_.row_.Release();
}
inline void KeyValue::set_allocated_row(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.row_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.row_.IsDefault()) {
          _impl_.row_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:admin.KeyValue.row)
}

// string column = 2;
inline void KeyValue::clear_column() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.column_.ClearToEmpty();
}
inline const std::string& KeyValue::column() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:admin.KeyValue.column)
  return _internal_column();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void KeyValue::set_column(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.column_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:admin.KeyValue.column)
}
inline std::string* KeyValue::mutable_column() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_column();
  // @@protoc_insertion_point(field_mutable:admin.KeyValue.column)
  return _s;
}
inline const std::string& KeyValue::_internal_column() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.column_.Get();
}
inline void KeyValue::_internal_set_column(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.column_.Set(value, GetArena());
}
inline std::string* KeyValue::_internal_mutable_column() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  return _impl_.column_.Mutable( GetArena());
}
inline std::string* KeyValue::release_column() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:admin.KeyValue.column)
  return _impl_.column_.Release();
}
inline void KeyValue::set_allocated_column(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.column_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.column_.IsDefault()) {
          _impl_.column_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:admin.KeyValue.column)
}

// string value = 3;
inline void KeyValue::clear_value() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.value_.ClearToEmpty();
}
inline const std::string& KeyValue::value() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:admin.KeyValue.value)
  return _internal_value();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void KeyValue::set_value(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.value_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:admin.KeyValue.value)
}
inline std::string* KeyValue::mutable_value() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_value();
  // @@protoc_insertion_point(field_mutable:admin.KeyValue.value)
  return _s;
}
inline const std::string& KeyValue::_internal_value() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.value_.Get();
}
inline void KeyValue::_internal_set_value(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.value_.Set(value, GetArena());
}
inline std::string* KeyValue::_internal_mutable_value() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  return _impl_.value_.Mutable( GetArena());
}
inline std::string* KeyValue::release_value() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:admin.KeyValue.value)
  return _impl_.value_.Release();
}
inline void KeyValue::set_allocated_value(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.value_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.value_.IsDefault()) {
          _impl_.value_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:admin.KeyValue.value)
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace admin


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_kv_5fadmin_5fconsole_2eproto_2epb_2eh
