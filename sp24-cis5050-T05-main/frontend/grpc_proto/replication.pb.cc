// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: replication.proto
// Protobuf C++ Version: 5.26.1

#include "replication.pb.h"

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
namespace replication {

inline constexpr TransactionResponse::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : message_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        success_{false},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR TransactionResponse::TransactionResponse(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct TransactionResponseDefaultTypeInternal {
  PROTOBUF_CONSTEXPR TransactionResponseDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~TransactionResponseDefaultTypeInternal() {}
  union {
    TransactionResponse _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 TransactionResponseDefaultTypeInternal _TransactionResponse_default_instance_;

inline constexpr Transaction::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : key_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        column_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        value_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        old_value_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        operation_{static_cast< ::replication::Operation >(0)},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR Transaction::Transaction(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct TransactionDefaultTypeInternal {
  PROTOBUF_CONSTEXPR TransactionDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~TransactionDefaultTypeInternal() {}
  union {
    Transaction _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 TransactionDefaultTypeInternal _Transaction_default_instance_;
}  // namespace replication
static ::_pb::Metadata file_level_metadata_replication_2eproto[2];
static const ::_pb::EnumDescriptor* file_level_enum_descriptors_replication_2eproto[1];
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_replication_2eproto = nullptr;
const ::uint32_t
    TableStruct_replication_2eproto::offsets[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
        protodesc_cold) = {
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::replication::Transaction, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::replication::Transaction, _impl_.operation_),
        PROTOBUF_FIELD_OFFSET(::replication::Transaction, _impl_.key_),
        PROTOBUF_FIELD_OFFSET(::replication::Transaction, _impl_.column_),
        PROTOBUF_FIELD_OFFSET(::replication::Transaction, _impl_.value_),
        PROTOBUF_FIELD_OFFSET(::replication::Transaction, _impl_.old_value_),
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::replication::TransactionResponse, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::replication::TransactionResponse, _impl_.success_),
        PROTOBUF_FIELD_OFFSET(::replication::TransactionResponse, _impl_.message_),
};

static const ::_pbi::MigrationSchema
    schemas[] ABSL_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
        {0, -1, -1, sizeof(::replication::Transaction)},
        {13, -1, -1, sizeof(::replication::TransactionResponse)},
};
static const ::_pb::Message* const file_default_instances[] = {
    &::replication::_Transaction_default_instance_._instance,
    &::replication::_TransactionResponse_default_instance_._instance,
};
const char descriptor_table_protodef_replication_2eproto[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
    protodesc_cold) = {
    "\n\021replication.proto\022\013replication\"w\n\013Tran"
    "saction\022)\n\toperation\030\001 \001(\0162\026.replication"
    ".Operation\022\013\n\003key\030\002 \001(\t\022\016\n\006column\030\003 \001(\t\022"
    "\r\n\005value\030\004 \001(\t\022\021\n\told_value\030\005 \001(\t\"7\n\023Tra"
    "nsactionResponse\022\017\n\007success\030\001 \001(\010\022\017\n\007mes"
    "sage\030\002 \001(\t**\n\tOperation\022\007\n\003PUT\020\000\022\n\n\006DELE"
    "TE\020\001\022\010\n\004CPUT\020\0022h\n\022ReplicationService\022R\n\022"
    "forwardTransaction\022\030.replication.Transac"
    "tion\032 .replication.TransactionResponse\"\000"
    "b\006proto3"
};
static ::absl::once_flag descriptor_table_replication_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_replication_2eproto = {
    false,
    false,
    368,
    descriptor_table_protodef_replication_2eproto,
    "replication.proto",
    &descriptor_table_replication_2eproto_once,
    nullptr,
    0,
    2,
    schemas,
    file_default_instances,
    TableStruct_replication_2eproto::offsets,
    file_level_metadata_replication_2eproto,
    file_level_enum_descriptors_replication_2eproto,
    file_level_service_descriptors_replication_2eproto,
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
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_replication_2eproto_getter() {
  return &descriptor_table_replication_2eproto;
}
namespace replication {
const ::google::protobuf::EnumDescriptor* Operation_descriptor() {
  ::google::protobuf::internal::AssignDescriptors(&descriptor_table_replication_2eproto);
  return file_level_enum_descriptors_replication_2eproto[0];
}
PROTOBUF_CONSTINIT const uint32_t Operation_internal_data_[] = {
    196608u, 0u, };
bool Operation_IsValid(int value) {
  return 0 <= value && value <= 2;
}
// ===================================================================

class Transaction::_Internal {
 public:
};

Transaction::Transaction(::google::protobuf::Arena* arena)
    : ::google::protobuf::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:replication.Transaction)
}
inline PROTOBUF_NDEBUG_INLINE Transaction::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from)
      : key_(arena, from.key_),
        column_(arena, from.column_),
        value_(arena, from.value_),
        old_value_(arena, from.old_value_),
        _cached_size_{0} {}

Transaction::Transaction(
    ::google::protobuf::Arena* arena,
    const Transaction& from)
    : ::google::protobuf::Message(arena) {
  Transaction* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_);
  _impl_.operation_ = from._impl_.operation_;

  // @@protoc_insertion_point(copy_constructor:replication.Transaction)
}
inline PROTOBUF_NDEBUG_INLINE Transaction::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : key_(arena),
        column_(arena),
        value_(arena),
        old_value_(arena),
        _cached_size_{0} {}

inline void Transaction::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  _impl_.operation_ = {};
}
Transaction::~Transaction() {
  // @@protoc_insertion_point(destructor:replication.Transaction)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void Transaction::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.key_.Destroy();
  _impl_.column_.Destroy();
  _impl_.value_.Destroy();
  _impl_.old_value_.Destroy();
  _impl_.~Impl_();
}

const ::google::protobuf::MessageLite::ClassData*
Transaction::GetClassData() const {
  PROTOBUF_CONSTINIT static const ::google::protobuf::MessageLite::
      ClassDataFull _data_ = {
          {
              nullptr,  // OnDemandRegisterArenaDtor
              PROTOBUF_FIELD_OFFSET(Transaction, _impl_._cached_size_),
              false,
          },
          &Transaction::MergeImpl,
          &Transaction::kDescriptorMethods,
      };
  return &_data_;
}
PROTOBUF_NOINLINE void Transaction::Clear() {
// @@protoc_insertion_point(message_clear_start:replication.Transaction)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.key_.ClearToEmpty();
  _impl_.column_.ClearToEmpty();
  _impl_.value_.ClearToEmpty();
  _impl_.old_value_.ClearToEmpty();
  _impl_.operation_ = 0;
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

const char* Transaction::_InternalParse(
    const char* ptr, ::_pbi::ParseContext* ctx) {
  ptr = ::_pbi::TcParser::ParseLoop(this, ptr, ctx, &_table_.header);
  return ptr;
}


PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<3, 5, 0, 55, 2> Transaction::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    5, 56,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967264,  // skipmap
    offsetof(decltype(_table_), field_entries),
    5,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    &_Transaction_default_instance_._instance,
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::replication::Transaction>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    {::_pbi::TcParser::MiniParse, {}},
    // .replication.Operation operation = 1;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint32_t, offsetof(Transaction, _impl_.operation_), 63>(),
     {8, 63, 0, PROTOBUF_FIELD_OFFSET(Transaction, _impl_.operation_)}},
    // string key = 2;
    {::_pbi::TcParser::FastUS1,
     {18, 63, 0, PROTOBUF_FIELD_OFFSET(Transaction, _impl_.key_)}},
    // string column = 3;
    {::_pbi::TcParser::FastUS1,
     {26, 63, 0, PROTOBUF_FIELD_OFFSET(Transaction, _impl_.column_)}},
    // string value = 4;
    {::_pbi::TcParser::FastUS1,
     {34, 63, 0, PROTOBUF_FIELD_OFFSET(Transaction, _impl_.value_)}},
    // string old_value = 5;
    {::_pbi::TcParser::FastUS1,
     {42, 63, 0, PROTOBUF_FIELD_OFFSET(Transaction, _impl_.old_value_)}},
    {::_pbi::TcParser::MiniParse, {}},
    {::_pbi::TcParser::MiniParse, {}},
  }}, {{
    65535, 65535
  }}, {{
    // .replication.Operation operation = 1;
    {PROTOBUF_FIELD_OFFSET(Transaction, _impl_.operation_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kOpenEnum)},
    // string key = 2;
    {PROTOBUF_FIELD_OFFSET(Transaction, _impl_.key_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
    // string column = 3;
    {PROTOBUF_FIELD_OFFSET(Transaction, _impl_.column_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
    // string value = 4;
    {PROTOBUF_FIELD_OFFSET(Transaction, _impl_.value_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
    // string old_value = 5;
    {PROTOBUF_FIELD_OFFSET(Transaction, _impl_.old_value_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
  }},
  // no aux_entries
  {{
    "\27\0\3\6\5\11\0\0"
    "replication.Transaction"
    "key"
    "column"
    "value"
    "old_value"
  }},
};

::uint8_t* Transaction::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:replication.Transaction)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  // .replication.Operation operation = 1;
  if (this->_internal_operation() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteEnumToArray(
        1, this->_internal_operation(), target);
  }

  // string key = 2;
  if (!this->_internal_key().empty()) {
    const std::string& _s = this->_internal_key();
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "replication.Transaction.key");
    target = stream->WriteStringMaybeAliased(2, _s, target);
  }

  // string column = 3;
  if (!this->_internal_column().empty()) {
    const std::string& _s = this->_internal_column();
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "replication.Transaction.column");
    target = stream->WriteStringMaybeAliased(3, _s, target);
  }

  // string value = 4;
  if (!this->_internal_value().empty()) {
    const std::string& _s = this->_internal_value();
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "replication.Transaction.value");
    target = stream->WriteStringMaybeAliased(4, _s, target);
  }

  // string old_value = 5;
  if (!this->_internal_old_value().empty()) {
    const std::string& _s = this->_internal_old_value();
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "replication.Transaction.old_value");
    target = stream->WriteStringMaybeAliased(5, _s, target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:replication.Transaction)
  return target;
}

::size_t Transaction::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:replication.Transaction)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string key = 2;
  if (!this->_internal_key().empty()) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                    this->_internal_key());
  }

  // string column = 3;
  if (!this->_internal_column().empty()) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                    this->_internal_column());
  }

  // string value = 4;
  if (!this->_internal_value().empty()) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                    this->_internal_value());
  }

  // string old_value = 5;
  if (!this->_internal_old_value().empty()) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                    this->_internal_old_value());
  }

  // .replication.Operation operation = 1;
  if (this->_internal_operation() != 0) {
    total_size += 1 +
                  ::_pbi::WireFormatLite::EnumSize(this->_internal_operation());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}


void Transaction::MergeImpl(::google::protobuf::MessageLite& to_msg, const ::google::protobuf::MessageLite& from_msg) {
  auto* const _this = static_cast<Transaction*>(&to_msg);
  auto& from = static_cast<const Transaction&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:replication.Transaction)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_key().empty()) {
    _this->_internal_set_key(from._internal_key());
  }
  if (!from._internal_column().empty()) {
    _this->_internal_set_column(from._internal_column());
  }
  if (!from._internal_value().empty()) {
    _this->_internal_set_value(from._internal_value());
  }
  if (!from._internal_old_value().empty()) {
    _this->_internal_set_old_value(from._internal_old_value());
  }
  if (from._internal_operation() != 0) {
    _this->_impl_.operation_ = from._impl_.operation_;
  }
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void Transaction::CopyFrom(const Transaction& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:replication.Transaction)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

PROTOBUF_NOINLINE bool Transaction::IsInitialized() const {
  return true;
}

void Transaction::InternalSwap(Transaction* PROTOBUF_RESTRICT other) {
  using std::swap;
  auto* arena = GetArena();
  ABSL_DCHECK_EQ(arena, other->GetArena());
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.key_, &other->_impl_.key_, arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.column_, &other->_impl_.column_, arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.value_, &other->_impl_.value_, arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.old_value_, &other->_impl_.old_value_, arena);
  swap(_impl_.operation_, other->_impl_.operation_);
}

::google::protobuf::Metadata Transaction::GetMetadata() const {
  return ::_pbi::AssignDescriptors(&descriptor_table_replication_2eproto_getter,
                                   &descriptor_table_replication_2eproto_once,
                                   file_level_metadata_replication_2eproto[0]);
}
// ===================================================================

class TransactionResponse::_Internal {
 public:
};

TransactionResponse::TransactionResponse(::google::protobuf::Arena* arena)
    : ::google::protobuf::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:replication.TransactionResponse)
}
inline PROTOBUF_NDEBUG_INLINE TransactionResponse::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from)
      : message_(arena, from.message_),
        _cached_size_{0} {}

TransactionResponse::TransactionResponse(
    ::google::protobuf::Arena* arena,
    const TransactionResponse& from)
    : ::google::protobuf::Message(arena) {
  TransactionResponse* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_);
  _impl_.success_ = from._impl_.success_;

  // @@protoc_insertion_point(copy_constructor:replication.TransactionResponse)
}
inline PROTOBUF_NDEBUG_INLINE TransactionResponse::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : message_(arena),
        _cached_size_{0} {}

inline void TransactionResponse::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  _impl_.success_ = {};
}
TransactionResponse::~TransactionResponse() {
  // @@protoc_insertion_point(destructor:replication.TransactionResponse)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void TransactionResponse::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.message_.Destroy();
  _impl_.~Impl_();
}

const ::google::protobuf::MessageLite::ClassData*
TransactionResponse::GetClassData() const {
  PROTOBUF_CONSTINIT static const ::google::protobuf::MessageLite::
      ClassDataFull _data_ = {
          {
              nullptr,  // OnDemandRegisterArenaDtor
              PROTOBUF_FIELD_OFFSET(TransactionResponse, _impl_._cached_size_),
              false,
          },
          &TransactionResponse::MergeImpl,
          &TransactionResponse::kDescriptorMethods,
      };
  return &_data_;
}
PROTOBUF_NOINLINE void TransactionResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:replication.TransactionResponse)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.message_.ClearToEmpty();
  _impl_.success_ = false;
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

const char* TransactionResponse::_InternalParse(
    const char* ptr, ::_pbi::ParseContext* ctx) {
  ptr = ::_pbi::TcParser::ParseLoop(this, ptr, ctx, &_table_.header);
  return ptr;
}


PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<1, 2, 0, 47, 2> TransactionResponse::_table_ = {
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
    &_TransactionResponse_default_instance_._instance,
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::replication::TransactionResponse>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // string message = 2;
    {::_pbi::TcParser::FastUS1,
     {18, 63, 0, PROTOBUF_FIELD_OFFSET(TransactionResponse, _impl_.message_)}},
    // bool success = 1;
    {::_pbi::TcParser::SingularVarintNoZag1<bool, offsetof(TransactionResponse, _impl_.success_), 63>(),
     {8, 63, 0, PROTOBUF_FIELD_OFFSET(TransactionResponse, _impl_.success_)}},
  }}, {{
    65535, 65535
  }}, {{
    // bool success = 1;
    {PROTOBUF_FIELD_OFFSET(TransactionResponse, _impl_.success_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kBool)},
    // string message = 2;
    {PROTOBUF_FIELD_OFFSET(TransactionResponse, _impl_.message_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
  }},
  // no aux_entries
  {{
    "\37\0\7\0\0\0\0\0"
    "replication.TransactionResponse"
    "message"
  }},
};

::uint8_t* TransactionResponse::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:replication.TransactionResponse)
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
        _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "replication.TransactionResponse.message");
    target = stream->WriteStringMaybeAliased(2, _s, target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:replication.TransactionResponse)
  return target;
}

::size_t TransactionResponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:replication.TransactionResponse)
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


void TransactionResponse::MergeImpl(::google::protobuf::MessageLite& to_msg, const ::google::protobuf::MessageLite& from_msg) {
  auto* const _this = static_cast<TransactionResponse*>(&to_msg);
  auto& from = static_cast<const TransactionResponse&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:replication.TransactionResponse)
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

void TransactionResponse::CopyFrom(const TransactionResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:replication.TransactionResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

PROTOBUF_NOINLINE bool TransactionResponse::IsInitialized() const {
  return true;
}

void TransactionResponse::InternalSwap(TransactionResponse* PROTOBUF_RESTRICT other) {
  using std::swap;
  auto* arena = GetArena();
  ABSL_DCHECK_EQ(arena, other->GetArena());
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.message_, &other->_impl_.message_, arena);
        swap(_impl_.success_, other->_impl_.success_);
}

::google::protobuf::Metadata TransactionResponse::GetMetadata() const {
  return ::_pbi::AssignDescriptors(&descriptor_table_replication_2eproto_getter,
                                   &descriptor_table_replication_2eproto_once,
                                   file_level_metadata_replication_2eproto[1]);
}
// @@protoc_insertion_point(namespace_scope)
}  // namespace replication
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(global_scope)
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2
static ::std::false_type _static_init_ PROTOBUF_UNUSED =
    (::_pbi::AddDescriptors(&descriptor_table_replication_2eproto),
     ::std::false_type{});
#include "google/protobuf/port_undef.inc"
