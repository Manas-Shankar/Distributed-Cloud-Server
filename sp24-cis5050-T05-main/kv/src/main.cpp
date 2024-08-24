#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <vector>
#include <pthread.h>
#include <iostream>
#include "../include/header.h"
#include "../include/server_socket.hpp"
#include "../include/kv_service_impl.hpp"
#include "../grpc_proto/replication.grpc.pb.h"
#include "../grpc_proto/kv_store.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include "../include/replication_coordinator.hpp"
#include "../include/checkpoint_controller.hpp"
#include "../include/checkpoint_service_impl.hpp"
#include "../include/recovery_controller.hpp"
#include "../include/recovery_service_impl.hpp"
#include "../include/tablet_manager.hpp"

using namespace std;

// store global flag for debugging
bool debug_flag = false;
// Global atomic flag to signal threads to shutdown
atomic<bool> shutdown_flag{false};

// handle user input
void handle_inputs(int argc, char *argv[], int &server_number, int &group_number, int &max_write_count)
{
    // use getopt to retrieve user input
    int opt;
    while ((opt = getopt(argc, argv, "n:g:c:v")) != -1)
    {
        switch (opt)
        {
        // n flag indicates the server number starting from 0
        case 'n':
            server_number = atoi(optarg);
            break;
        case 'g':
            group_number = atoi(optarg);
            break;
        case 'c':
            max_write_count = atoi(optarg);
            break;
        // setup debug flag
        case 'v':
            debug_flag = true;
            break;
        case '?':
            cerr << "Usage: " << argv[0] << "-n server_number -g group_number [-v]" << endl;
            exit(EXIT_FAILURE);
        default:
            cerr << "Usage: " << argv[0] << " -n server_number -g group_number [-v]" << endl;
            exit(EXIT_FAILURE);
        }
    }
    // if n is not set then exit the program and print error
    if (server_number == -1 || group_number == -1)
    {
        cerr << "Usage: " << argv[0] << "-n server_number -g group_number [-v]" << endl;
        exit(EXIT_FAILURE);
    }
}

// retrieve the server address from the server number
string get_server_addresses(int server_number, vector<string> &server_addresses)
{
    // read from the config.txt file to get the server address
    string server_address = "";
    string line;
    ifstream config_file("config.txt");
    if (config_file.is_open())
    {
        int line_number = 0;
        while (getline(config_file, line))
        {
            if (line_number == server_number)
            {
                server_address = line;
            }
            else
            {
                server_addresses.push_back(line);
            }
            line_number++;
        }
        config_file.close();
    }
    else
    {
        cerr << "Unable to open file" << endl;
    }
    return server_address;
}

int main(int argc, char *argv[])
{
    // get the server number from the command line
    int server_number = -1;
    int group_number = -1;
    int max_write_count = 100;
    handle_inputs(argc, argv, server_number, group_number, max_write_count);
    std::cout << "Post-parsing: server_number=" << server_number
              << ", group_number=" << group_number
              << ", max_write_count=" << max_write_count << std::endl;
    // get the server address from the config file
    vector<string> server_addresses;
    string node_address = get_server_addresses(server_number, server_addresses);
    std::cout << "Node address: " << node_address << std::endl;

    // set the server number and group number in the tablet manager so they can find the correct disk folder
    Tablet_Manager &manager = Tablet_Manager::get_instance();
    cout << "Initializing tablet manager. Group number: " << group_number << " , server_number: " << server_number << endl;
    manager.initialize(group_number, server_number);

    // If the server_number is 0 then the primary address is the same as the server address, otherwise it is the first address in server_addresses
    string primary_address = (server_number == 0) ? node_address : server_addresses[0];
    std::cout << "Primary address: " << primary_address << std::endl;

    // create the channels for the inter-node communication:
    std::unordered_map<std::string, std::shared_ptr<grpc::Channel>> channels;
    for (const auto &address : server_addresses)
    {
        std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(address, grpc::InsecureChannelCredentials());
        channels[address] = channel;
        std::cout << "Added channel for address: " << address << std::endl;
    }

    // create the checkpointing controller object
    Checkpoint_Controller checkpoint_controller(node_address, primary_address, channels, max_write_count);
    // create the replication coordinator object.
    Replication_Coordinator replication_coordinator(node_address, primary_address, channels, checkpoint_controller);
    // link the checkpointing controller to the replication coordinator
    checkpoint_controller.set_replication_coordinator(&replication_coordinator);
    // create the recovery controller object
    Recovery_Controller recovery_controller(node_address, primary_address, channels);

    // initialize the services. KV Service takes in the replication coordinator so that it can forward the transaction to the replication coordinator
    KeyValueServiceImpl kv_service(replication_coordinator);
    ReplicationServiceImpl replication_service(replication_coordinator, checkpoint_controller);
    CheckpointServiceImpl checkpoint_service(checkpoint_controller);
    RecoveryServiceImpl recovery_service(recovery_controller);

    // create the server
    grpc::ServerBuilder builder;
    cout << "Adding listening port at Server address:" << node_address << endl;
    builder.AddListeningPort(node_address, grpc::InsecureServerCredentials());

    // register the services
    cout << "Registering services" << endl;
    builder.RegisterService(&kv_service);
    builder.RegisterService(&replication_service);
    builder.RegisterService(&checkpoint_service);
    builder.RegisterService(&recovery_service);

    // start the server
    cout << "Starting server" << endl;
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    // if node isn't the primary node, start the recovery process
    if (primary_address != node_address)
    {
        recovery_controller.start_recovery();
    }
    std::cout << "Server listening on " << node_address << std::endl;

    server->Wait();

    return 0;
}