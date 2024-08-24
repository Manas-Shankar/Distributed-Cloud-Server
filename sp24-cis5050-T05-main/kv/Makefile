# Compiler FLAGS
CXX=g++
CXXFLAGS=-std=c++20 -Wall -O2 $(shell pkg-config --cflags protobuf grpc++ grpc)
LDFLAGS=$(shell pkg-config --libs protobuf grpc++ grpc)
PROTOC_FLAGS=$(shell pkg-config --cflags protobuf grpc++)

# Proto files for gRPC:
PROTO_SRC=grpc_proto/kv_store.proto grpc_proto/replication.proto grpc_proto/checkpoint.proto grpc_proto/recovery.proto grpc_proto/kv_lifecycle.proto grpc_proto/kv_admin_console.proto grpc_proto/backend_master_as_server.proto
PROTO_GEN=grpc_proto/kv_store.grpc.pb.cc grpc_proto/kv_store.pb.cc \
           grpc_proto/replication.grpc.pb.cc grpc_proto/replication.pb.cc \
           grpc_proto/checkpoint.grpc.pb.cc grpc_proto/checkpoint.pb.cc \
              grpc_proto/recovery.grpc.pb.cc grpc_proto/recovery.pb.cc \
                grpc_proto/kv_lifecycle.grpc.pb.cc grpc_proto/kv_lifecycle.pb.cc \
                grpc_proto/kv_admin_console.grpc.pb.cc grpc_proto/kv_admin_console.pb.cc \
                grpc_proto/backend_master_as_server.grpc.pb.cc grpc_proto/backend_master_as_server.pb.cc


PROTO_HEADERS=grpc_proto/kv_store.grpc.pb.h grpc_proto/kv_store.pb.h \
              grpc_proto/replication.grpc.pb.h grpc_proto/replication.pb.h \
              grpc_proto/checkpoint.grpc.pb.h grpc_proto/checkpoint.pb.h \
              grpc_proto/recovery.grpc.pb.h grpc_proto/recovery.pb.h \
              grpc_proto/kv_lifecycle.grpc.pb.h grpc_proto/kv_lifecycle.pb.h \
              grpc_proto/kv_admin_console.grpc.pb.h grpc_proto/kv_admin_console.pb.h \
              grpc_proto/backend_master_as_server.grpc.pb.h grpc_proto/backend_master_as_server.pb.h


CPP_SOURCES=src/kv_main.cpp \
            src/controller.cpp \
            src/tablet_manager.cpp \
			src/tablet.cpp 	\
            src/replication_coordinator.cpp \
            src/replication_service_impl.cpp \
            src/kv_service_impl.cpp \
            src/checkpoint_controller.cpp \
            src/checkpoint_service_impl.cpp \
            src/recovery_controller.cpp \
            src/recovery_service_impl.cpp \
            src/KVNodeLifecycleServiceImpl.cpp \
            src/ServiceManager.cpp \
            src/Status_Manager.cpp \
            src/kv_admin_service_impl.cpp\
            

OBJECTS=$(CPP_SOURCES:.cpp=.o) $(PROTO_GEN:.cc=.o)

EXECUTABLE=kvstore_server

# Generate gRPC and protobuf sources from .proto files
$(PROTO_GEN) $(PROTO_HEADERS): $(PROTO_SRC)
    protoc --grpc_out=grpc_proto --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` grpc_proto/kv_store.proto
    protoc --cpp_out=grpc_proto grpc_proto/kv_store.proto
    protoc --grpc_out=grpc_proto --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` grpc_proto/replication.proto
    protoc --cpp_out=grpc_proto grpc_proto/replication.proto

all: $(PROTO_HEADERS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $^ -g $(LDFLAGS) -o $@

%.o: %.cpp $(PROTO_HEADERS)
	$(CXX) $(CXXFLAGS) $(PROTOC_FLAGS) -c $< -o $@

%.o: %.cc $(PROTO_HEADERS)
	$(CXX) $(CXXFLAGS) $(PROTOC_FLAGS) -c $< -o $@


# Clean up
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean



