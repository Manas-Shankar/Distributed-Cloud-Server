// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: frontend_backend_master.proto
// Protobuf C++ Version: 5.26.1

#include "frontend_backend_master.pb.h"

#include <algorithm>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
#include "google/protobuf/generated_message_tctable_impl.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::google::protobuf;
namespace _pbi = ::google::protobuf::internal;
namespace _fl = ::google::protobuf::internal::field_layout;
namespace penncloud {
namespace frontend {

inline constexpr Node::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : id_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        address_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        port_{0},
        ishealthy_{false},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR Node::Node(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct NodeDefaultTypeInternal {
  PROTOBUF_CONSTEXPR NodeDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~NodeDefaultTypeInternal() {}
  union {
    Node _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 NodeDefaultTypeInternal _Node_default_instance_;
      template <typename>
PROTOBUF_CONSTEXPR Empty::Empty(::_pbi::ConstantInitialized) {}
struct EmptyDefaultTypeInternal {
  PROTOBUF_CONSTEXPR EmptyDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~EmptyDefaultTypeInternal() {}
  union {
    Empty _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 EmptyDefaultTypeInternal _Empty_default_instance_;

inline constexpr Acknowledgment::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : message_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        success_{false},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR Acknowledgment::Acknowledgment(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct AcknowledgmentDefaultTypeInternal {
  PROTOBUF_CONSTEXPR AcknowledgmentDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~AcknowledgmentDefaultTypeInternal() {}
  union {
    Acknowledgment _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 AcknowledgmentDefaultTypeInternal _Acknowledgment_default_instance_;

inline constexpr NodeUpdate::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : nodes_{},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR NodeUpdate::NodeUpdate(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct NodeUpdateDefaultTypeInternal {
  PROTOBUF_CONSTEXPR NodeUpdateDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~NodeUpdateDefaultTypeInternal() {}
  union {
    NodeUpdate _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 NodeUpdateDefaultTypeInternal _NodeUpdate_default_instance_;
}  // namespace frontend
}  // namespace penncloud
static ::_pb::Metadata file_level_metadata_frontend_5fbackend_5fmaster_2eproto[4];
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_frontend_5fbackend_5fmaster_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_frontend_5fbackend_5fmaster_2eproto = nullptr;
const ::uint32_t
    TableStruct_frontend_5fbackend_5fmaster_2eproto::offsets[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
        protodesc_cold) = {
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::penncloud::frontend::Empty, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::penncloud::frontend::Acknowledgment, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::penncloud::frontend::Acknowledgment, _impl_.success_),
        PROTOBUF_FIELD_OFFSET(::penncloud::frontend::Acknowledgment, _impl_.message_),
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::penncloud::frontend::Node, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::penncloud::frontend::Node, _impl_.id_),
        PROTOBUF_FIELD_OFFSET(::penncloud::frontend::Node, _impl_.address_),
        PROTOBUF_FIELD_OFFSET(::penncloud::frontend::Node, _impl_.port_),
        PROTOBUF_FIELD_OFFSET(::penncloud::frontend::Node, _impl_.ishealthy_),
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::penncloud::frontend::NodeUpdate, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::penncloud::frontend::NodeUpdate, _impl_.nodes_),
};

static const ::_pbi::MigrationSchema
    schemas[] ABSL_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
        {0, -1, -1, sizeof(::penncloud::frontend::Empty)},
        {8, -1, -1, sizeof(::penncloud::frontend::Acknowledgment)},
        {18, -1, -1, sizeof(::penncloud::frontend::Node)},
        {30, -1, -1, sizeof(::penncloud::frontend::NodeUpdate)},
};
static const ::_pb::Message* const file_default_instances[] = {
    &::penncloud::frontend::_Empty_default_instance_._instance,
    &::penncloud::frontend::_Acknowledgment_default_instance_._instance,
    &::penncloud::frontend::_Node_default_instance_._instance,
    &::penncloud::frontend::_NodeUpdate_default_instance_._instance,
};
const char descriptor_table_protodef_frontend_5fbackend_5fmaster_2eproto[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
    protodesc_cold) = {
    "\n\035frontend_backend_master.proto\022\022pennclo"
    "ud.frontend\"\007\n\005Empty\"2\n\016Acknowledgment\022\017"
    "\n\007success\030\001 \001(\010\022\017\n\007message\030\002 \001(\t\"D\n\004Node"
    "\022\n\n\002id\030\001 \001(\t\022\017\n\007address\030\002 \001(\t\022\014\n\004port\030\003 "
    "\001(\005\022\021\n\tisHealthy\030\004 \001(\010\"5\n\nNodeUpdate\022\'\n\005"
    "nodes\030\001 \003(\0132\030.penncloud.frontend.Node2\307\001"
    "\n\025FrontendMasterService\022S\n\020RegisterFront"
    "end\022\031.penncloud.frontend.Empty\032\".pennclo"
    "ud.frontend.Acknowledgment\"\000\022Y\n\021ReceiveN"
    "odeUpdate\022\036.penncloud.frontend.NodeUpdat"
    "e\032\".penncloud.frontend.Acknowledgment\"\000b"
    "\006proto3"
};
static ::absl::once_flag descriptor_table_frontend_5fbackend_5fmaster_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_frontend_5fbackend_5fmaster_2eproto = {
    false,
    false,
    447,
    descriptor_table_protodef_frontend_5fbackend_5fmaster_2eproto,
    "frontend_backend_master.proto",
    &descriptor_table_frontend_5fbackend_5fmaster_2eproto_once,
    nullptr,
    0,
    4,
    schemas,
    file_default_instances,
    TableStruct_frontend_5fbackend_5fmaster_2eproto::offsets,
    file_level_metadata_frontend_5fbackend_5fmaster_2eproto,
    file_level_enum_descriptors_frontend_5fbackend_5fmaster_2eproto,
    file_level_service_descriptors_frontend_5fbackend_5fmaster_2eproto,
};

// This function exists to be marked as weak.
// It can significantly speed up compilation by breaking up LLVM's SCC
// in the .pb.cc translation units. Large translation units see a
// reduction of more than 35% of walltime for optimized builds. Without
// the weak attribute all the messages in the file, including all the
// vtables and everything they use become part of the same SCC through
// a cycle like:
// GetMetadata -> descriptor table -> default instances ->
//   vtables -> GetMetadata
// By adding a weak function here we break the connection from the
// individual vtables back into the descriptor table.
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_frontend_5fbackend_5fmaster_2eproto_getter() {
  return &descriptor_table_frontend_5fbackend_5fmaster_2eproto;
}
namespace penncloud {
namespace frontend {
// ===================================================================

class Empty::_Internal {
 public:
};

Empty::Empty(::google::protobuf::Arena* arena)
    : ::google::protobuf::internal::ZeroFieldsBase(arena) {
  // @@protoc_insertion_point(arena_constructor:penncloud.frontend.Empty)
}
Empty::Empty(
    ::google::protobuf::Arena* arena,
    const Empty& from)
    : ::google::protobuf::internal::ZeroFieldsBase(arena) {
  Empty* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);

  // @@protoc_insertion_point(copy_constructor:penncloud.frontend.Empty)
}









::google::protobuf::Metadata Empty::GetMetadata() const {
  return ::_pbi::AssignDescriptors(&descriptor_table_frontend_5fbackend_5fmaster_2eproto_getter,
                                   &descriptor_table_frontend_5fbackend_5fmaster_2eproto_once,
                                   file_level_metadata_frontend_5fbackend_5fmaster_2eproto[0]);
}
// ===================================================================

class Acknowledgment::_Internal {
 public:
};

Acknowledgment::Acknowledgment(::google::protobuf::Arena* arena)
    : ::google::protobuf::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:penncloud.frontend.Acknowledgment)
}
inline PROTOBUF_NDEBUG_INLINE Acknowledgment::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from)
      : message_(arena, from.message_),
        _cached_size_{0} {}

Acknowledgment::Acknowledgment(
    ::google::protobuf::Arena* arena,
    const Acknowledgment& from)
    : ::google::protobuf::Message(arena) {
  Acknowledgment* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_);
  _impl_.success_ = from._impl_.success_;

  // @@protoc_insertion_point(copy_constructor:penncloud.frontend.Acknowledgment)
}
inline PROTOBUF_NDEBUG_INLINE Acknowledgment::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : message_(arena),
        _cached_size_{0} {}

inline void Acknowledgment::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  _impl_.success_ = {};
}
Acknowledgment::~Acknowledgment() {
  // @@protoc_insertion_point(destructor:penncloud.frontend.Acknowledgment)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void Acknowledgment::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.message_.Destroy();
  _impl_.~Impl_();
}

const ::google::protobuf::MessageLite::ClassData*
Acknowledgment::GetClassData() const {
  PROTOBUF_CONSTINIT static const ::google::protobuf::MessageLite::
      ClassDataFull _data_ = {
          {
              nullptr,  // OnDemandRegisterArenaDtor
              PROTOBUF_FIELD_OFFSET(Acknowledgment, _impl_._cached_size_),
              false,
          },
          &Acknowledgment::MergeImpl,
          &Acknowledgment::kDescriptorMethods,
      };
  return &_data_;
}
PROTOBUF_NOINLINE void Acknowledgment::Clear() {
// @@protoc_insertion_point(message_clear_start:penncloud.frontend.Acknowledgment)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.message_.ClearToEmpty();
  _impl_.success_ = false;
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

const char* Acknowledgment::_InternalParse(
    const char* ptr, ::_pbi::ParseContext* ctx) {
  ptr = ::_pbi::TcParser::ParseLoop(this, ptr, ctx, &_table_.header);
  return ptr;
}


PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<1, 2, 0, 49, 2> Acknowledgment::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    2, 8,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967292,  // skipmap
    offsetof(decltype(_table_), field_entries),
    2,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    &_Acknowledgment_default_instance_._instance,
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::penncloud::frontend::Acknowledgment>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // string message = 2;
    {::_pbi::TcParser::FastUS1,
     {18, 63, 0, PROTOBUF_FIELD_OFFSET(Acknowledgment, _impl_.message_)}},
    // bool success = 1;
    {::_pbi::TcParser::SingularVarintNoZag1<bool, offsetof(Acknowledgment, _impl_.success_), 63>(),
     {8, 63, 0, PROTOBUF_FIELD_OFFSET(Acknowledgment, _impl_.success_)}},
  }}, {{
    65535, 65535
  }}, {{
    // bool success = 1;
    {PROTOBUF_FIELD_OFFSET(Acknowledgment, _impl_.success_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kBool)},
    // string message = 2;
    {PROTOBUF_FIELD_OFFSET(Acknowledgment, _impl_.message_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
  }},
  // no aux_entries
  {{
    "\41\0\7\0\0\0\0\0"
    "penncloud.frontend.Acknowledgment"
    "message"
  }},
};

::uint8_t* Acknowledgment::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:penncloud.frontend.Acknowledgment)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  // bool success = 1;
  if (this->_internal_success() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteBoolToArray(
        1, this->_internal_success(), target);
  }

  // string message = 2;
  if (!this->_internal_message().empty()) {
    const std::string& _s = this->_internal_message();
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "penncloud.frontend.Acknowledgment.message");
    target = stream->WriteStringMaybeAliased(2, _s, target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:penncloud.frontend.Acknowledgment)
  return target;
}

::size_t Acknowledgment::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:penncloud.frontend.Acknowledgment)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string message = 2;
  if (!this->_internal_message().empty()) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                    this->_internal_message());
  }

  // bool success = 1;
  if (this->_internal_success() != 0) {
    total_size += 2;
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}


void Acknowledgment::MergeImpl(::google::protobuf::MessageLite& to_msg, const ::google::protobuf::MessageLite& from_msg) {
  auto* const _this = static_cast<Acknowledgment*>(&to_msg);
  auto& from = static_cast<const Acknowledgment&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:penncloud.frontend.Acknowledgment)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_message().empty()) {
    _this->_internal_set_message(from._internal_message());
  }
  if (from._internal_success() != 0) {
    _this->_impl_.success_ = from._impl_.success_;
  }
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void Acknowledgment::CopyFrom(const Acknowledgment& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:penncloud.frontend.Acknowledgment)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

PROTOBUF_NOINLINE bool Acknowledgment::IsInitialized() const {
  return true;
}

void Acknowledgment::InternalSwap(Acknowledgment* PROTOBUF_RESTRICT other) {
  using std::swap;
  auto* arena = GetArena();
  ABSL_DCHECK_EQ(arena, other->GetArena());
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.message_, &other->_impl_.message_, arena);
        swap(_impl_.success_, other->_impl_.success_);
}

::google::protobuf::Metadata Acknowledgment::GetMetadata() const {
  return ::_pbi::AssignDescriptors(&descriptor_table_frontend_5fbackend_5fmaster_2eproto_getter,
                                   &descriptor_table_frontend_5fbackend_5fmaster_2eproto_once,
                                   file_level_metadata_frontend_5fbackend_5fmaster_2eproto[1]);
}
// ===================================================================

class Node::_Internal {
 public:
};

Node::Node(::google::protobuf::Arena* arena)
    : ::google::protobuf::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:penncloud.frontend.Node)
}
inline PROTOBUF_NDEBUG_INLINE Node::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from)
      : id_(arena, from.id_),
        address_(arena, from.address_),
        _cached_size_{0} {}

Node::Node(
    ::google::protobuf::Arena* arena,
    const Node& from)
    : ::google::protobuf::Message(arena) {
  Node* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_);
  ::memcpy(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, port_),
           reinterpret_cast<const char *>(&from._impl_) +
               offsetof(Impl_, port_),
           offsetof(Impl_, ishealthy_) -
               offsetof(Impl_, port_) +
               sizeof(Impl_::ishealthy_));

  // @@protoc_insertion_point(copy_constructor:penncloud.frontend.Node)
}
inline PROTOBUF_NDEBUG_INLINE Node::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : id_(arena),
        address_(arena),
        _cached_size_{0} {}

inline void Node::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  ::memset(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, port_),
           0,
           offsetof(Impl_, ishealthy_) -
               offsetof(Impl_, port_) +
               sizeof(Impl_::ishealthy_));
}
Node::~Node() {
  // @@protoc_insertion_point(destructor:penncloud.frontend.Node)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void Node::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.id_.Destroy();
  _impl_.address_.Destroy();
  _impl_.~Impl_();
}

const ::google::protobuf::MessageLite::ClassData*
Node::GetClassData() const {
  PROTOBUF_CONSTINIT static const ::google::protobuf::MessageLite::
      ClassDataFull _data_ = {
          {
              nullptr,  // OnDemandRegisterArenaDtor
              PROTOBUF_FIELD_OFFSET(Node, _impl_._cached_size_),
              false,
          },
          &Node::MergeImpl,
          &Node::kDescriptorMethods,
      };
  return &_data_;
}
PROTOBUF_NOINLINE void Node::Clear() {
// @@protoc_insertion_point(message_clear_start:penncloud.frontend.Node)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.id_.ClearToEmpty();
  _impl_.address_.ClearToEmpty();
  ::memset(&_impl_.port_, 0, static_cast<::size_t>(
      reinterpret_cast<char*>(&_impl_.ishealthy_) -
      reinterpret_cast<char*>(&_impl_.port_)) + sizeof(_impl_.ishealthy_));
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

const char* Node::_InternalParse(
    const char* ptr, ::_pbi::ParseContext* ctx) {
  ptr = ::_pbi::TcParser::ParseLoop(this, ptr, ctx, &_table_.header);
  return ptr;
}


PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<2, 4, 0, 41, 2> Node::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    4, 24,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967280,  // skipmap
    offsetof(decltype(_table_), field_entries),
    4,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    &_Node_default_instance_._instance,
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::penncloud::frontend::Node>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // bool isHealthy = 4;
    {::_pbi::TcParser::SingularVarintNoZag1<bool, offsetof(Node, _impl_.ishealthy_), 63>(),
     {32, 63, 0, PROTOBUF_FIELD_OFFSET(Node, _impl_.ishealthy_)}},
    // string id = 1;
    {::_pbi::TcParser::FastUS1,
     {10, 63, 0, PROTOBUF_FIELD_OFFSET(Node, _impl_.id_)}},
    // string address = 2;
    {::_pbi::TcParser::FastUS1,
     {18, 63, 0, PROTOBUF_FIELD_OFFSET(Node, _impl_.address_)}},
    // int32 port = 3;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint32_t, offsetof(Node, _impl_.port_), 63>(),
     {24, 63, 0, PROTOBUF_FIELD_OFFSET(Node, _impl_.port_)}},
  }}, {{
    65535, 65535
  }}, {{
    // string id = 1;
    {PROTOBUF_FIELD_OFFSET(Node, _impl_.id_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
    // string address = 2;
    {PROTOBUF_FIELD_OFFSET(Node, _impl_.address_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
    // int32 port = 3;
    {PROTOBUF_FIELD_OFFSET(Node, _impl_.port_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kInt32)},
    // bool isHealthy = 4;
    {PROTOBUF_FIELD_OFFSET(Node, _impl_.ishealthy_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kBool)},
  }},
  // no aux_entries
  {{
    "\27\2\7\0\0\0\0\0"
    "penncloud.frontend.Node"
    "id"
    "address"
  }},
};

::uint8_t* Node::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:penncloud.frontend.Node)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  // string id = 1;
  if (!this->_internal_id().empty()) {
    const std::string& _s = this->_internal_id();
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "penncloud.frontend.Node.id");
    target = stream->WriteStringMaybeAliased(1, _s, target);
  }

  // string address = 2;
  if (!this->_internal_address().empty()) {
    const std::string& _s = this->_internal_address();
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "penncloud.frontend.Node.address");
    target = stream->WriteStringMaybeAliased(2, _s, target);
  }

  // int32 port = 3;
  if (this->_internal_port() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::
        WriteInt32ToArrayWithField<3>(
            stream, this->_internal_port(), target);
  }

  // bool isHealthy = 4;
  if (this->_internal_ishealthy() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteBoolToArray(
        4, this->_internal_ishealthy(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:penncloud.frontend.Node)
  return target;
}

::size_t Node::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:penncloud.frontend.Node)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string id = 1;
  if (!this->_internal_id().empty()) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                    this->_internal_id());
  }

  // string address = 2;
  if (!this->_internal_address().empty()) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                    this->_internal_address());
  }

  // int32 port = 3;
  if (this->_internal_port() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(
        this->_internal_port());
  }

  // bool isHealthy = 4;
  if (this->_internal_ishealthy() != 0) {
    total_size += 2;
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}


void Node::MergeImpl(::google::protobuf::MessageLite& to_msg, const ::google::protobuf::MessageLite& from_msg) {
  auto* const _this = static_cast<Node*>(&to_msg);
  auto& from = static_cast<const Node&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:penncloud.frontend.Node)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_id().empty()) {
    _this->_internal_set_id(from._internal_id());
  }
  if (!from._internal_address().empty()) {
    _this->_internal_set_address(from._internal_address());
  }
  if (from._internal_port() != 0) {
    _this->_impl_.port_ = from._impl_.port_;
  }
  if (from._internal_ishealthy() != 0) {
    _this->_impl_.ishealthy_ = from._impl_.ishealthy_;
  }
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void Node::CopyFrom(const Node& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:penncloud.frontend.Node)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

PROTOBUF_NOINLINE bool Node::IsInitialized() const {
  return true;
}

void Node::InternalSwap(Node* PROTOBUF_RESTRICT other) {
  using std::swap;
  auto* arena = GetArena();
  ABSL_DCHECK_EQ(arena, other->GetArena());
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.id_, &other->_impl_.id_, arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.address_, &other->_impl_.address_, arena);
  ::google::protobuf::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Node, _impl_.ishealthy_)
      + sizeof(Node::_impl_.ishealthy_)
      - PROTOBUF_FIELD_OFFSET(Node, _impl_.port_)>(
          reinterpret_cast<char*>(&_impl_.port_),
          reinterpret_cast<char*>(&other->_impl_.port_));
}

::google::protobuf::Metadata Node::GetMetadata() const {
  return ::_pbi::AssignDescriptors(&descriptor_table_frontend_5fbackend_5fmaster_2eproto_getter,
                                   &descriptor_table_frontend_5fbackend_5fmaster_2eproto_once,
                                   file_level_metadata_frontend_5fbackend_5fmaster_2eproto[2]);
}
// ===================================================================

class NodeUpdate::_Internal {
 public:
};

NodeUpdate::NodeUpdate(::google::protobuf::Arena* arena)
    : ::google::protobuf::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:penncloud.frontend.NodeUpdate)
}
inline PROTOBUF_NDEBUG_INLINE NodeUpdate::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from)
      : nodes_{visibility, arena, from.nodes_},
        _cached_size_{0} {}

NodeUpdate::NodeUpdate(
    ::google::protobuf::Arena* arena,
    const NodeUpdate& from)
    : ::google::protobuf::Message(arena) {
  NodeUpdate* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_);

  // @@protoc_insertion_point(copy_constructor:penncloud.frontend.NodeUpdate)
}
inline PROTOBUF_NDEBUG_INLINE NodeUpdate::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : nodes_{visibility, arena},
        _cached_size_{0} {}

inline void NodeUpdate::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
}
NodeUpdate::~NodeUpdate() {
  // @@protoc_insertion_point(destructor:penncloud.frontend.NodeUpdate)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void NodeUpdate::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.~Impl_();
}

const ::google::protobuf::MessageLite::ClassData*
NodeUpdate::GetClassData() const {
  PROTOBUF_CONSTINIT static const ::google::protobuf::MessageLite::
      ClassDataFull _data_ = {
          {
              nullptr,  // OnDemandRegisterArenaDtor
              PROTOBUF_FIELD_OFFSET(NodeUpdate, _impl_._cached_size_),
              false,
          },
          &NodeUpdate::MergeImpl,
          &NodeUpdate::kDescriptorMethods,
      };
  return &_data_;
}
PROTOBUF_NOINLINE void NodeUpdate::Clear() {
// @@protoc_insertion_point(message_clear_start:penncloud.frontend.NodeUpdate)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.nodes_.Clear();
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

const char* NodeUpdate::_InternalParse(
    const char* ptr, ::_pbi::ParseContext* ctx) {
  ptr = ::_pbi::TcParser::ParseLoop(this, ptr, ctx, &_table_.header);
  return ptr;
}


PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<0, 1, 1, 0, 2> NodeUpdate::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    1, 0,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967294,  // skipmap
    offsetof(decltype(_table_), field_entries),
    1,  // num_field_entries
    1,  // num_aux_entries
    offsetof(decltype(_table_), aux_entries),
    &_NodeUpdate_default_instance_._instance,
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::penncloud::frontend::NodeUpdate>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // repeated .penncloud.frontend.Node nodes = 1;
    {::_pbi::TcParser::FastMtR1,
     {10, 63, 0, PROTOBUF_FIELD_OFFSET(NodeUpdate, _impl_.nodes_)}},
  }}, {{
    65535, 65535
  }}, {{
    // repeated .penncloud.frontend.Node nodes = 1;
    {PROTOBUF_FIELD_OFFSET(NodeUpdate, _impl_.nodes_), 0, 0,
    (0 | ::_fl::kFcRepeated | ::_fl::kMessage | ::_fl::kTvTable)},
  }}, {{
    {::_pbi::TcParser::GetTable<::penncloud::frontend::Node>()},
  }}, {{
  }},
};

::uint8_t* NodeUpdate::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:penncloud.frontend.NodeUpdate)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  // repeated .penncloud.frontend.Node nodes = 1;
  for (unsigned i = 0, n = static_cast<unsigned>(
                           this->_internal_nodes_size());
       i < n; i++) {
    const auto& repfield = this->_internal_nodes().Get(i);
    target =
        ::google::protobuf::internal::WireFormatLite::InternalWriteMessage(
            1, repfield, repfield.GetCachedSize(),
            target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:penncloud.frontend.NodeUpdate)
  return target;
}

::size_t NodeUpdate::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:penncloud.frontend.NodeUpdate)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .penncloud.frontend.Node nodes = 1;
  total_size += 1UL * this->_internal_nodes_size();
  for (const auto& msg : this->_internal_nodes()) {
    total_size += ::google::protobuf::internal::WireFormatLite::MessageSize(msg);
  }
  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}


void NodeUpdate::MergeImpl(::google::protobuf::MessageLite& to_msg, const ::google::protobuf::MessageLite& from_msg) {
  auto* const _this = static_cast<NodeUpdate*>(&to_msg);
  auto& from = static_cast<const NodeUpdate&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:penncloud.frontend.NodeUpdate)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_internal_mutable_nodes()->MergeFrom(
      from._internal_nodes());
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void NodeUpdate::CopyFrom(const NodeUpdate& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:penncloud.frontend.NodeUpdate)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

PROTOBUF_NOINLINE bool NodeUpdate::IsInitialized() const {
  return true;
}

void NodeUpdate::InternalSwap(NodeUpdate* PROTOBUF_RESTRICT other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.nodes_.InternalSwap(&other->_impl_.nodes_);
}

::google::protobuf::Metadata NodeUpdate::GetMetadata() const {
  return ::_pbi::AssignDescriptors(&descriptor_table_frontend_5fbackend_5fmaster_2eproto_getter,
                                   &descriptor_table_frontend_5fbackend_5fmaster_2eproto_once,
                                   file_level_metadata_frontend_5fbackend_5fmaster_2eproto[3]);
}
// @@protoc_insertion_point(namespace_scope)
}  // namespace frontend
}  // namespace penncloud
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(global_scope)
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2
static ::std::false_type _static_init_ PROTOBUF_UNUSED =
    (::_pbi::AddDescriptors(&descriptor_table_frontend_5fbackend_5fmaster_2eproto),
     ::std::false_type{});
#include "google/protobuf/port_undef.inc"
