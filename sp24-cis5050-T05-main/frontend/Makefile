# Compiler FLAGS
CXX=g++
CXXFLAGS=-std=c++17 -Wall -O2 $(shell pkg-config --cflags protobuf grpc++ grpc)
LDFLAGS=-lpthread -lresolv $(shell pkg-config --libs libssl libcrypto protobuf grpc++ grpc)
# LDFLAGS=-lpthread -lssl -lcrypto -lresolv $(shell pkg-config --libs protobuf grpc++ grpc)

PROTOC_FLAGS=$(shell pkg-config --cflags protobuf grpc++)

# Proto files for gRPC:
PROTO_SRC=grpc_proto/kv_grpc_proto/kv_store.proto\
    grpc_proto/webmail_grpc_proto/webmailgrpc.proto\
    grpc_proto/kv_grpc_proto/kv_lifecycle.proto\
    grpc_proto/kv_grpc_proto/kv_admin_console.proto\
    grpc_proto/kv_grpc_proto/backend_master_as_server.proto\
    

PROTO_GEN=grpc_proto/kv_grpc_proto/kv_store.grpc.pb.cc \
    grpc_proto/kv_grpc_proto/kv_store.pb.cc\
    grpc_proto/webmail_grpc_proto/webmailgrpc.grpc.pb.cc \
    grpc_proto/webmail_grpc_proto/webmailgrpc.pb.cc\
    grpc_proto/kv_grpc_proto/kv_lifecycle.grpc.pb.cc \
    grpc_proto/kv_grpc_proto/kv_lifecycle.pb.cc\
    grpc_proto/kv_grpc_proto/kv_admin_console.grpc.pb.cc \
    grpc_proto/kv_grpc_proto/kv_admin_console.pb.cc\
    grpc_proto/kv_grpc_proto/backend_master_as_server.grpc.pb.cc \
    grpc_proto/kv_grpc_proto/backend_master_as_server.pb.cc\

PROTO_HEADERS=grpc_proto/kv_grpc_proto/kv_store.grpc.pb.h \
    grpc_proto/kv_grpc_proto/kv_store.pb.h\
    grpc_proto/webmail_grpc_proto/webmailgrpc.grpc.pb.h \
    grpc_proto/webmail_grpc_proto/webmailgrpc.pb.h\
    grpc_proto/kv_grpc_proto/kv_lifecycle.grpc.pb.h \
    grpc_proto/kv_grpc_proto/kv_lifecycle.pb.h\
    grpc_proto/kv_grpc_proto/kv_admin_console.grpc.pb.h \
    grpc_proto/kv_grpc_proto/kv_admin_console.pb.h\
    grpc_proto/kv_grpc_proto/backend_master_as_server.grpc.pb.h \
    grpc_proto/kv_grpc_proto/backend_master_as_server.pb.h\
    
# Sources 
CPP_SOURCES=src/pop3_commands.cpp	\
    src/smtp_commands.cpp	\
    src/frontend.cpp \
    src/request.cpp \
    src/response.cpp \
    src/utils.cpp \
    src/store.cpp \
    src/sample_store_kv_client.cpp	\
    src/adminconsole.cpp	\


OBJECTS=$(CPP_SOURCES:.cpp=.o) $(PROTO_GEN:.cc=.o)

EXECUTABLE=frontend

# Generate gRPC and protobuf sources from .proto files
# $(PROTO_GEN) $(PROTO_HEADERS): $(PROTO_SRC)
# 	protoc --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` $<
# 	protoc --cpp_out=.  $<

all: $(PROTO_HEADERS) $(EXECUTABLE)

lb: src/load_balancer.cpp src/utils.cpp
	g++ $^ -o $@ -lpthread

adminconsole: src/adminconsole.cpp
	g++ $^ -o $@ -lpthread -lresolv

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
