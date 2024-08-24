# Compiler and linker settings
CXX=g++
CXXFLAGS=-std=c++20 -Wall -O2 $(shell pkg-config --cflags protobuf grpc++) -I./include -I./grpc_proto/
LDFLAGS=$(shell pkg-config --libs protobuf grpc++ grpc)
LDFLAGS += -lgrpc++_reflection $(shell pkg-config --libs protobuf grpc++)


# Source files
CPP_SOURCES = src/main.cpp \
              src/webmailgrpc_impl.cpp \
			  src/session_manager.cpp \
			  src/server.cpp \
			  src/kv_client.cpp \


# Proto sources and outputs
PROTO_DIR=grpc_proto/
PROTO_SOURCES := $(wildcard $(PROTO_DIR)/*.proto)
PROTO_CC_SOURCES := $(PROTO_SOURCES:.proto=.grpc.pb.cc) $(PROTO_SOURCES:.proto=.pb.cc)
PROTO_HEADERS := $(PROTO_SOURCES:.proto=.grpc.pb.h) $(PROTO_SOURCES:.proto=.pb.h)
PROTO_OBJECTS := $(PROTO_CC_SOURCES:.cc=.o)

# Combine all object files
OBJECTS := $(CPP_SOURCES:.cpp=.o) $(PROTO_OBJECTS)

# Executable
EXECUTABLE=smtp

all: $(EXECUTABLE)
	echo "Building everything..."

$(EXECUTABLE): $(OBJECTS)
	echo "Linking object files to create executable..."
	$(CXX) $^ $(LDFLAGS) -o $@ -v

%.o: %.cpp
	echo "Compiling $< to $@..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(PROTO_DIR)/%.grpc.pb.cc $(PROTO_DIR)/%.grpc.pb.h $(PROTO_DIR)/%.pb.cc $(PROTO_DIR)/%.pb.h: $(PROTO_DIR)/%.proto
	echo "Compiling proto file $<..."
	protoc --proto_path=$(PROTO_DIR) --grpc_out=$(PROTO_DIR) --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` $<
	protoc --proto_path=$(PROTO_DIR) --cpp_out=$(PROTO_DIR) $<

$(PROTO_DIR)/%.o: $(PROTO_DIR)/%.cc
	echo "Compiling proto generated CC file $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	echo "Cleaning up..."
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean
