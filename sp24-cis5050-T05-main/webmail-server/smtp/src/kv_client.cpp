#include "../include/kv_client.hpp"

KVClient::KVClient(std::shared_ptr<grpc::Channel> channel) : stub_(kvstore::KeyValue::NewStub(channel)) {}

bool KVClient::put(const std::string& row, const std::string& column, const std::string& value) {
    kvstore::PutRequest request;
    request.set_row(row);
    request.set_column(column);
    request.set_value(value);

    kvstore::PutResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->Put(&context, request, &response);

    if (status.ok()) {
        return response.success();
    } else {
        std::cerr << "Put failed: " << status.error_message() << std::endl;
        return false;
    }
}

std::string KVClient::get(const std::string& row, const std::string& column) {
    kvstore::GetRequest request;
    request.set_row(row);
    request.set_column(column);

    kvstore::GetResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->Get(&context, request, &response);

    if (status.ok()) {
        // std::cout<<"\nGet worked and got something\n";
        return response.value();  // Return the retrieved value
    } else {
        std::cerr << "Get failed: " << status.error_message() << std::endl;
        return "";  // Return empty if there's an error
    }
}