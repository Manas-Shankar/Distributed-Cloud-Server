// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: frontend_backend_master.proto
// Protobuf C++ Version: 5.26.1

#ifndef GOOGLE_PROTOBUF_INCLUDED_frontend_5fbackend_5fmaster_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_frontend_5fbackend_5fmaster_2eproto_2epb_2eh

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

#define PROTOBUF_INTERNAL_EXPORT_frontend_5fbackend_5fmaster_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_frontend_5fbackend_5fmaster_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_frontend_5fbackend_5fmaster_2eproto;
namespace penncloud {
namespace frontend {
class Acknowledgment;
struct AcknowledgmentDefaultTypeInternal;
extern AcknowledgmentDefaultTypeInternal _Acknowledgment_default_instance_;
class Empty;
struct EmptyDefaultTypeInternal;
extern EmptyDefaultTypeInternal _Empty_default_instance_;
class Node;
struct NodeDefaultTypeInternal;
extern NodeDefaultTypeInternal _Node_default_instance_;
class NodeUpdate;
struct NodeUpdateDefaultTypeInternal;
extern NodeUpdateDefaultTypeInternal _NodeUpdate_default_instance_;
}  // namespace frontend
}  // namespace penncloud
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace penncloud {
namespace frontend {

// ===================================================================


// -------------------------------------------------------------------

class Node final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:penncloud.frontend.Node) */ {
 public:
  inline Node() : Node(nullptr) {}
  ~Node() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR Node(
      ::google::protobuf::internal::ConstantInitialized);

  inline Node(const Node& from) : Node(nullptr, from) {}
  inline Node(Node&& from) noexcept
      : Node(nullptr, std::move(from)) {}
  inline Node& operator=(const Node& from) {
    CopyFrom(from);
    return *this;
  }
  inline Node& operator=(Node&& from) noexcept {
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
  static const Node& default_instance() {
    return *internal_default_instance();
  }
  static inline const Node* internal_default_instance() {
    return reinterpret_cast<const Node*>(
        &_Node_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 2;
  friend void swap(Node& a, Node& b) { a.Swap(&b); }
  inline void Swap(Node* other) {
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
  void UnsafeArenaSwap(Node* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Node* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::Message::DefaultConstruct<Node>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const Node& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const Node& from) { Node::MergeImpl(*this, from); }

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
  void InternalSwap(Node* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "penncloud.frontend.Node"; }

 protected:
  explicit Node(::google::protobuf::Arena* arena);
  Node(::google::protobuf::Arena* arena, const Node& from);
  Node(::google::protobuf::Arena* arena, Node&& from) noexcept
      : Node(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::MessageLite::ClassData* GetClassData()
      const final;

 public:
  ::google::protobuf::Metadata GetMetadata() const final;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kIdFieldNumber = 1,
    kAddressFieldNumber = 2,
    kPortFieldNumber = 3,
    kIsHealthyFieldNumber = 4,
  };
  // string id = 1;
  void clear_id() ;
  const std::string& id() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_id(Arg_&& arg, Args_... args);
  std::string* mutable_id();
  PROTOBUF_NODISCARD std::string* release_id();
  void set_allocated_id(std::string* value);

  private:
  const std::string& _internal_id() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_id(
      const std::string& value);
  std::string* _internal_mutable_id();

  public:
  // string address = 2;
  void clear_address() ;
  const std::string& address() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_address(Arg_&& arg, Args_... args);
  std::string* mutable_address();
  PROTOBUF_NODISCARD std::string* release_address();
  void set_allocated_address(std::string* value);

  private:
  const std::string& _internal_address() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_address(
      const std::string& value);
  std::string* _internal_mutable_address();

  public:
  // int32 port = 3;
  void clear_port() ;
  ::int32_t port() const;
  void set_port(::int32_t value);

  private:
  ::int32_t _internal_port() const;
  void _internal_set_port(::int32_t value);

  public:
  // bool isHealthy = 4;
  void clear_ishealthy() ;
  bool ishealthy() const;
  void set_ishealthy(bool value);

  private:
  bool _internal_ishealthy() const;
  void _internal_set_ishealthy(bool value);

  public:
  // @@protoc_insertion_point(class_scope:penncloud.frontend.Node)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      2, 4, 0,
      41, 2>
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
    ::google::protobuf::internal::ArenaStringPtr id_;
    ::google::protobuf::internal::ArenaStringPtr address_;
    ::int32_t port_;
    bool ishealthy_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_frontend_5fbackend_5fmaster_2eproto;
};
// -------------------------------------------------------------------

class Empty final : public ::google::protobuf::internal::ZeroFieldsBase
/* @@protoc_insertion_point(class_definition:penncloud.frontend.Empty) */ {
 public:
  inline Empty() : Empty(nullptr) {}
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR Empty(
      ::google::protobuf::internal::ConstantInitialized);

  inline Empty(const Empty& from) : Empty(nullptr, from) {}
  inline Empty(Empty&& from) noexcept
      : Empty(nullptr, std::move(from)) {}
  inline Empty& operator=(const Empty& from) {
    CopyFrom(from);
    return *this;
  }
  inline Empty& operator=(Empty&& from) noexcept {
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
  static const Empty& default_instance() {
    return *internal_default_instance();
  }
  static inline const Empty* internal_default_instance() {
    return reinterpret_cast<const Empty*>(
        &_Empty_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(Empty& a, Empty& b) { a.Swap(&b); }
  inline void Swap(Empty* other) {
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
  void UnsafeArenaSwap(Empty* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Empty* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::internal::ZeroFieldsBase::DefaultConstruct<Empty>(arena);
  }
  using ::google::protobuf::internal::ZeroFieldsBase::CopyFrom;
  inline void CopyFrom(const Empty& from) {
    ::google::protobuf::internal::ZeroFieldsBase::CopyImpl(*this, from);
  }
  using ::google::protobuf::internal::ZeroFieldsBase::MergeFrom;
  void MergeFrom(const Empty& from) {
    ::google::protobuf::internal::ZeroFieldsBase::MergeImpl(*this, from);
  }

  public:
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "penncloud.frontend.Empty"; }

 protected:
  explicit Empty(::google::protobuf::Arena* arena);
  Empty(::google::protobuf::Arena* arena, const Empty& from);
  Empty(::google::protobuf::Arena* arena, Empty&& from) noexcept
      : Empty(arena) {
    *this = ::std::move(from);
  }

 public:
  ::google::protobuf::Metadata GetMetadata() const final;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  // @@protoc_insertion_point(class_scope:penncloud.frontend.Empty)
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
  friend struct ::TableStruct_frontend_5fbackend_5fmaster_2eproto;
};
// -------------------------------------------------------------------

class Acknowledgment final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:penncloud.frontend.Acknowledgment) */ {
 public:
  inline Acknowledgment() : Acknowledgment(nullptr) {}
  ~Acknowledgment() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR Acknowledgment(
      ::google::protobuf::internal::ConstantInitialized);

  inline Acknowledgment(const Acknowledgment& from) : Acknowledgment(nullptr, from) {}
  inline Acknowledgment(Acknowledgment&& from) noexcept
      : Acknowledgment(nullptr, std::move(from)) {}
  inline Acknowledgment& operator=(const Acknowledgment& from) {
    CopyFrom(from);
    return *this;
  }
  inline Acknowledgment& operator=(Acknowledgment&& from) noexcept {
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
  static const Acknowledgment& default_instance() {
    return *internal_default_instance();
  }
  static inline const Acknowledgment* internal_default_instance() {
    return reinterpret_cast<const Acknowledgment*>(
        &_Acknowledgment_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 1;
  friend void swap(Acknowledgment& a, Acknowledgment& b) { a.Swap(&b); }
  inline void Swap(Acknowledgment* other) {
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
  void UnsafeArenaSwap(Acknowledgment* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Acknowledgment* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::Message::DefaultConstruct<Acknowledgment>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const Acknowledgment& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const Acknowledgment& from) { Acknowledgment::MergeImpl(*this, from); }

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
  void InternalSwap(Acknowledgment* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "penncloud.frontend.Acknowledgment"; }

 protected:
  explicit Acknowledgment(::google::protobuf::Arena* arena);
  Acknowledgment(::google::protobuf::Arena* arena, const Acknowledgment& from);
  Acknowledgment(::google::protobuf::Arena* arena, Acknowledgment&& from) noexcept
      : Acknowledgment(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::MessageLite::ClassData* GetClassData()
      const final;

 public:
  ::google::protobuf::Metadata GetMetadata() const final;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kMessageFieldNumber = 2,
    kSuccessFieldNumber = 1,
  };
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
  // @@protoc_insertion_point(class_scope:penncloud.frontend.Acknowledgment)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      1, 2, 0,
      49, 2>
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
    ::google::protobuf::internal::ArenaStringPtr message_;
    bool success_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_frontend_5fbackend_5fmaster_2eproto;
};
// -------------------------------------------------------------------

class NodeUpdate final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:penncloud.frontend.NodeUpdate) */ {
 public:
  inline NodeUpdate() : NodeUpdate(nullptr) {}
  ~NodeUpdate() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR NodeUpdate(
      ::google::protobuf::internal::ConstantInitialized);

  inline NodeUpdate(const NodeUpdate& from) : NodeUpdate(nullptr, from) {}
  inline NodeUpdate(NodeUpdate&& from) noexcept
      : NodeUpdate(nullptr, std::move(from)) {}
  inline NodeUpdate& operator=(const NodeUpdate& from) {
    CopyFrom(from);
    return *this;
  }
  inline NodeUpdate& operator=(NodeUpdate&& from) noexcept {
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
  static const NodeUpdate& default_instance() {
    return *internal_default_instance();
  }
  static inline const NodeUpdate* internal_default_instance() {
    return reinterpret_cast<const NodeUpdate*>(
        &_NodeUpdate_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 3;
  friend void swap(NodeUpdate& a, NodeUpdate& b) { a.Swap(&b); }
  inline void Swap(NodeUpdate* other) {
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
  void UnsafeArenaSwap(NodeUpdate* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  NodeUpdate* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::Message::DefaultConstruct<NodeUpdate>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const NodeUpdate& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const NodeUpdate& from) { NodeUpdate::MergeImpl(*this, from); }

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
  void InternalSwap(NodeUpdate* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "penncloud.frontend.NodeUpdate"; }

 protected:
  explicit NodeUpdate(::google::protobuf::Arena* arena);
  NodeUpdate(::google::protobuf::Arena* arena, const NodeUpdate& from);
  NodeUpdate(::google::protobuf::Arena* arena, NodeUpdate&& from) noexcept
      : NodeUpdate(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::MessageLite::ClassData* GetClassData()
      const final;

 public:
  ::google::protobuf::Metadata GetMetadata() const final;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kNodesFieldNumber = 1,
  };
  // repeated .penncloud.frontend.Node nodes = 1;
  int nodes_size() const;
  private:
  int _internal_nodes_size() const;

  public:
  void clear_nodes() ;
  ::penncloud::frontend::Node* mutable_nodes(int index);
  ::google::protobuf::RepeatedPtrField<::penncloud::frontend::Node>* mutable_nodes();

  private:
  const ::google::protobuf::RepeatedPtrField<::penncloud::frontend::Node>& _internal_nodes() const;
  ::google::protobuf::RepeatedPtrField<::penncloud::frontend::Node>* _internal_mutable_nodes();
  public:
  const ::penncloud::frontend::Node& nodes(int index) const;
  ::penncloud::frontend::Node* add_nodes();
  const ::google::protobuf::RepeatedPtrField<::penncloud::frontend::Node>& nodes() const;
  // @@protoc_insertion_point(class_scope:penncloud.frontend.NodeUpdate)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      0, 1, 1,
      0, 2>
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
    ::google::protobuf::RepeatedPtrField< ::penncloud::frontend::Node > nodes_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_frontend_5fbackend_5fmaster_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// Empty

// -------------------------------------------------------------------

// Acknowledgment

// bool success = 1;
inline void Acknowledgment::clear_success() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.success_ = false;
}
inline bool Acknowledgment::success() const {
  // @@protoc_insertion_point(field_get:penncloud.frontend.Acknowledgment.success)
  return _internal_success();
}
inline void Acknowledgment::set_success(bool value) {
  _internal_set_success(value);
  // @@protoc_insertion_point(field_set:penncloud.frontend.Acknowledgment.success)
}
inline bool Acknowledgment::_internal_success() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.success_;
}
inline void Acknowledgment::_internal_set_success(bool value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.success_ = value;
}

// string message = 2;
inline void Acknowledgment::clear_message() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.message_.ClearToEmpty();
}
inline const std::string& Acknowledgment::message() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:penncloud.frontend.Acknowledgment.message)
  return _internal_message();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void Acknowledgment::set_message(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.message_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:penncloud.frontend.Acknowledgment.message)
}
inline std::string* Acknowledgment::mutable_message() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_message();
  // @@protoc_insertion_point(field_mutable:penncloud.frontend.Acknowledgment.message)
  return _s;
}
inline const std::string& Acknowledgment::_internal_message() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.message_.Get();
}
inline void Acknowledgment::_internal_set_message(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.message_.Set(value, GetArena());
}
inline std::string* Acknowledgment::_internal_mutable_message() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  return _impl_.message_.Mutable( GetArena());
}
inline std::string* Acknowledgment::release_message() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:penncloud.frontend.Acknowledgment.message)
  return _impl_.message_.Release();
}
inline void Acknowledgment::set_allocated_message(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.message_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.message_.IsDefault()) {
          _impl_.message_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:penncloud.frontend.Acknowledgment.message)
}

// -------------------------------------------------------------------

// Node

// string id = 1;
inline void Node::clear_id() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.id_.ClearToEmpty();
}
inline const std::string& Node::id() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:penncloud.frontend.Node.id)
  return _internal_id();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void Node::set_id(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.id_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:penncloud.frontend.Node.id)
}
inline std::string* Node::mutable_id() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_id();
  // @@protoc_insertion_point(field_mutable:penncloud.frontend.Node.id)
  return _s;
}
inline const std::string& Node::_internal_id() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.id_.Get();
}
inline void Node::_internal_set_id(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.id_.Set(value, GetArena());
}
inline std::string* Node::_internal_mutable_id() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  return _impl_.id_.Mutable( GetArena());
}
inline std::string* Node::release_id() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:penncloud.frontend.Node.id)
  return _impl_.id_.Release();
}
inline void Node::set_allocated_id(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.id_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.id_.IsDefault()) {
          _impl_.id_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:penncloud.frontend.Node.id)
}

// string address = 2;
inline void Node::clear_address() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.address_.ClearToEmpty();
}
inline const std::string& Node::address() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:penncloud.frontend.Node.address)
  return _internal_address();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void Node::set_address(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.address_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:penncloud.frontend.Node.address)
}
inline std::string* Node::mutable_address() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_address();
  // @@protoc_insertion_point(field_mutable:penncloud.frontend.Node.address)
  return _s;
}
inline const std::string& Node::_internal_address() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.address_.Get();
}
inline void Node::_internal_set_address(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.address_.Set(value, GetArena());
}
inline std::string* Node::_internal_mutable_address() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  return _impl_.address_.Mutable( GetArena());
}
inline std::string* Node::release_address() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:penncloud.frontend.Node.address)
  return _impl_.address_.Release();
}
inline void Node::set_allocated_address(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.address_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.address_.IsDefault()) {
          _impl_.address_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:penncloud.frontend.Node.address)
}

// int32 port = 3;
inline void Node::clear_port() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.port_ = 0;
}
inline ::int32_t Node::port() const {
  // @@protoc_insertion_point(field_get:penncloud.frontend.Node.port)
  return _internal_port();
}
inline void Node::set_port(::int32_t value) {
  _internal_set_port(value);
  // @@protoc_insertion_point(field_set:penncloud.frontend.Node.port)
}
inline ::int32_t Node::_internal_port() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.port_;
}
inline void Node::_internal_set_port(::int32_t value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.port_ = value;
}

// bool isHealthy = 4;
inline void Node::clear_ishealthy() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.ishealthy_ = false;
}
inline bool Node::ishealthy() const {
  // @@protoc_insertion_point(field_get:penncloud.frontend.Node.isHealthy)
  return _internal_ishealthy();
}
inline void Node::set_ishealthy(bool value) {
  _internal_set_ishealthy(value);
  // @@protoc_insertion_point(field_set:penncloud.frontend.Node.isHealthy)
}
inline bool Node::_internal_ishealthy() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.ishealthy_;
}
inline void Node::_internal_set_ishealthy(bool value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.ishealthy_ = value;
}

// -------------------------------------------------------------------

// NodeUpdate

// repeated .penncloud.frontend.Node nodes = 1;
inline int NodeUpdate::_internal_nodes_size() const {
  return _internal_nodes().size();
}
inline int NodeUpdate::nodes_size() const {
  return _internal_nodes_size();
}
inline void NodeUpdate::clear_nodes() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.nodes_.Clear();
}
inline ::penncloud::frontend::Node* NodeUpdate::mutable_nodes(int index)
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_mutable:penncloud.frontend.NodeUpdate.nodes)
  return _internal_mutable_nodes()->Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField<::penncloud::frontend::Node>* NodeUpdate::mutable_nodes()
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_mutable_list:penncloud.frontend.NodeUpdate.nodes)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  return _internal_mutable_nodes();
}
inline const ::penncloud::frontend::Node& NodeUpdate::nodes(int index) const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:penncloud.frontend.NodeUpdate.nodes)
  return _internal_nodes().Get(index);
}
inline ::penncloud::frontend::Node* NodeUpdate::add_nodes() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::penncloud::frontend::Node* _add = _internal_mutable_nodes()->Add();
  // @@protoc_insertion_point(field_add:penncloud.frontend.NodeUpdate.nodes)
  return _add;
}
inline const ::google::protobuf::RepeatedPtrField<::penncloud::frontend::Node>& NodeUpdate::nodes() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_list:penncloud.frontend.NodeUpdate.nodes)
  return _internal_nodes();
}
inline const ::google::protobuf::RepeatedPtrField<::penncloud::frontend::Node>&
NodeUpdate::_internal_nodes() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.nodes_;
}
inline ::google::protobuf::RepeatedPtrField<::penncloud::frontend::Node>*
NodeUpdate::_internal_mutable_nodes() {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return &_impl_.nodes_;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace frontend
}  // namespace penncloud


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_frontend_5fbackend_5fmaster_2eproto_2epb_2eh
