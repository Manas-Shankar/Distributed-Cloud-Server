# Variables
PROTOC=protoc
GRPC_CPP_PLUGIN_PATH ?= `which grpc_cpp_plugin`
PROTO_PATH=./
CPP_OUT_PATH=./

# Specify proto files
PROTO_FILES=$(wildcard $(PROTO_PATH)/*.proto)

# Target for proto files (change your proto files names accordingly)
all: $(PROTO_FILES:$(PROTO_PATH)/%.proto=$(CPP_OUT_PATH)/%.pb.cc)

# Rule to generate .pb.cc, .pb.h, .grpc.pb.cc, and .grpc.pb.h files from .proto
$(CPP_OUT_PATH)/%.pb.cc: $(PROTO_PATH)/%.proto
	$(PROTOC) --proto_path=$(PROTO_PATH) --cpp_out=$(CPP_OUT_PATH) $<
	$(PROTOC) --proto_path=$(PROTO_PATH) --grpc_out=$(CPP_OUT_PATH) --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

clean:
	rm -f $(CPP_OUT_PATH)/*.pb.cc $(CPP_OUT_PATH)/*.pb.h $(CPP_OUT_PATH)/*.grpc.pb.cc $(CPP_OUT_PATH)/*.grpc.pb.h

.PHONY: all clean
