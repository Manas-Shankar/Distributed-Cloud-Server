#include "../include/adminconsole.h"
#include <fstream>
#include <iostream>

using namespace std;

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using kvstore::ShutdownRequest;
using kvstore::ShutdownResponse;
using kvstore::RestartRequest;
using kvstore::RestartResponse;
using admin::AdminKV;
using admin::GetAllRequest;
using admin::GetAllResponse;
using admin::KeyValue;
using backendmaster::ListNodesRequest;
using backendmaster::NodesList;
using backendmaster::BackendMasterService;


// A client to get the response from the backend master - Rupkatha's GRPC

std::string serverAddress;
std::map<std::string, std::string> nodesAndStatus;
std::map<std::string, std::string> nodesAndGroup;
std::map<std::string, std::string> kvStore;
// std::map<std::string,std::string> nodes;

class KVNodeClient {
public:
    KVNodeClient(std::shared_ptr<Channel> channel): stub_(KVNodeLifecycle::NewStub(channel)) {}

    // Calls Shutdown RPC
    std::string Shutdown() {
        ShutdownRequest request;
        ShutdownResponse response;
        ClientContext context;

        Status status = stub_->Shutdown(&context, request, &response);
        if (status.ok()) {
            return "Shutdown successful";
        } else {
            return "Shutdown failed: " + status.error_message();
        }
    }

    // Calls Restart RPC
    std::string  Restart() {
        RestartRequest request;
        RestartResponse response;
        ClientContext context;

        Status status = stub_->Restart(&context, request, &response);
        if (status.ok()) {
            return "Restart successful";
        } else {
            return "Restart failed: " + status.error_message();
        }
    }

private:
    std::unique_ptr<KVNodeLifecycle::Stub> stub_;
};

//A client to get the status from the backend - Paul's GRPC


class AdminKVClient {
public:
    AdminKVClient(std::shared_ptr<Channel> channel): stub_(AdminKV::NewStub(channel)) {}

    // Function to call the GetAllKeyValuePairs RPC
    string GetAllKeyValuePairs() {
        GetAllRequest request; 
        GetAllResponse response;
        ClientContext context;

        // Making the RPC call
        Status status = stub_->GetAllKeyValuePairs(&context, request, &response);

        if (status.ok()) {
            //flush out existing data
            kvStore.clear();

            cout << "RPC Success. Retrieved Data:\n";
            for (auto& pair : response.pairs()) {

                string key = pair.row() + " " + pair.column();
                string value = pair.value();
                cout << "Key " << key << "Value " << value << endl;

                kvStore[key] = value;
            }
        
            return "OK";
        } else {
        
            return status.error_message();
        }
    }

private:
    std::unique_ptr<AdminKV::Stub> stub_;
};

//To get the status of all the nodes
class BackendMasterClient {
public:
    BackendMasterClient(std::shared_ptr<Channel> channel): stub_(BackendMasterService::NewStub(channel)) {}

    // Asynchronously calls the ListNodes RPC
    void ListNodes() {
        // Data we are sending to the server.
        ListNodesRequest request;

        // Container for the data we expect from the server.
        NodesList reply;

        // Context for the client. It could be used to convey extra information to
        ClientContext context;

        // The actual RPC.
        Status status = stub_->ListNodes(&context, request, &reply);

        // Act upon its status.
        if (status.ok()) {
            std::cout << "ListNodes RPC succeeded." << std::endl;
            for (const auto& node : reply.nodes()) {
                nodesAndStatus[node.address()] = node.status();
                nodesAndGroup[node.address()] = to_string(node.group());
            }
        } else {
            std::cerr << "ListNodes RPC failed." << std::endl;
        }
    }

private:
    std::unique_ptr<BackendMasterService::Stub> stub_;
};




// Function to Fetch the Node Status and KV details usign GRPC

void AdminConsole::getNodeStatus(){

    BackendMasterClient client(grpc::CreateChannel("127.0.0.1:5056", grpc::InsecureChannelCredentials()));
    client.ListNodes();
}


// Fetch the latest data from the KV Store
void AdminConsole::getKVData(){

    vector<string> backendAddresses = {"127.0.0.1:5050","127.0.0.1:5051","127.0.0.1:5052"};

    for (int i = 0; i < backendAddresses.size();i++) {
    
        AdminKVClient client(grpc::CreateChannel(backendAddresses.at(i), grpc::InsecureChannelCredentials()));
        string response = client.GetAllKeyValuePairs();

        //break out if we get an active replica
        if (response == "OK") {
            return;
        }
    }
}



// Function to handle nodes endpoint : Called after a request is parsed
map<string,string> AdminConsole::handleNodes() {

    return nodesAndStatus;
}

// Function to handle KV-store endpoint : Called after a request is parsed : 
map<string,string> AdminConsole::handleKVStore() {

    return kvStore;
}

//start to receive the nodes data
map<string,string> AdminConsole::startNodes() { 

    //get the status of the nodes from the backend master
    getNodeStatus(); 

    //return the json string 
    return handleNodes();

}

//start to receive the nodes data
map<string,string> AdminConsole::nodesAndGroups() { 

    //get the status of the nodes from the backend master
    return nodesAndGroup;
}


//start KV store
map<string,string> AdminConsole::startKVStore() { 

    //get the data of the nodes from the KS store
    getKVData();

    //return the json string 
    return handleKVStore();

}

// Function to handle nodes endpoint : Called after a request is parsed
std::string AdminConsole::nodeOperations(std::string command,std::string nodeId) {


    KVNodeClient client(grpc::CreateChannel(nodeId, grpc::InsecureChannelCredentials()));

    if (command == "shutdown") {
        
        return client.Shutdown();

    } else if (command == "restart"){

        return client.Restart();
    }
}

