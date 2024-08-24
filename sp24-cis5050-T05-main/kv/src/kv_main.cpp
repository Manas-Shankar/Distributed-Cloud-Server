#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <vector>
#include <pthread.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "../include/header.h"
#include "../include/server_socket.hpp"
#include "../include/kv_service_impl.hpp"
#include "../grpc_proto/replication.grpc.pb.h"
#include "../grpc_proto/kv_store.grpc.pb.h"
#include "../grpc_proto/kv_lifecycle.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include "../include/replication_coordinator.hpp"
#include "../include/checkpoint_controller.hpp"
#include "../include/checkpoint_service_impl.hpp"
#include "../include/KVNodeLifecycleServiceImpl.hpp"
#include "../include/tablet_manager.hpp"
#include "../include/status_manager.hpp"
// #include "service_management.hpp"
#include "../include/ServiceManager.hpp"

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
string get_server_addresses(int server_number, vector<string> &server_addresses, int group_number)
{
    // read from the config.txt file to get the server address
    string server_address = "";
    string line;
    ifstream config_file;
    if (group_number == 1)
    {
        config_file.open("config.txt");
    }
    else if (group_number == 2)
    {
        config_file.open("config_2.txt");
    }
    else
    {
        cerr << "Invalid group number" << endl;
        exit(EXIT_FAILURE);
    }
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

// retrieve the daemon address from the server number
string get_daemon_address(int server_number, int group_number)
{
    ifstream config_file;
    if (group_number == 1)
    {
        config_file.open("daemon_config.txt");
    }
    else if (group_number == 2)
    {
        config_file.open("daemon_config_2.txt");
    }
    else
    {
        cerr << "Invalid group number" << endl;
        exit(EXIT_FAILURE);
    }
    string line;
    int current_line = 0;
    if (config_file.is_open())
    {
        while (getline(config_file, line))
        {
            if (current_line == server_number)
            {
                return line;
            }
            current_line++;
        }
    }
    else
    {
        cerr << "Unable to open file" << endl;
    }
    cerr << "Server number exceeds config file lines.";
    return line;
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
    string node_address = get_server_addresses(server_number, server_addresses, group_number);
    std::cout << "Node address: " << node_address << std::endl;

    // gets address of daemon
    string daemon_address = get_daemon_address(server_number, group_number);
    cout << "Daemon address: " << daemon_address << std::endl;

    Status_Manager::GetInstance().set_current_address(daemon_address);

    // Populate the ServiceManager class with command line arg states
    ServiceManager::GetInstance().Initialize(server_number, group_number, max_write_count, node_address, server_addresses, daemon_address);

    // initialize the lifecycle services.
    KVNodeLifecycleServiceImpl lifecycleService;

    // create the control server
    grpc::ServerBuilder control_builder;
    control_builder.AddListeningPort(daemon_address, grpc::InsecureServerCredentials());
    control_builder.RegisterService(&lifecycleService);

    // start the control server
    std::unique_ptr<grpc::Server> control_server(control_builder.BuildAndStart());
    std::cout << "Control server listening on " << daemon_address << std::endl;

    while (Status_Manager::GetInstance().get_primary_address().empty())
    {
        std::cout << "Waiting for primary address to be set..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    ServiceManager::GetInstance().StartServices();

    control_server->Wait();

    /*
    // handle user input
    int portnr = 5050;
    handle_inputs(argc, argv, portnr);

    // block the SIGINT listener in all threads:
    block_sigint_in_threads();
    // create a new thread to listen for SIGINT:
    pthread_t sigint_thread;
    if (pthread_create(&sigint_thread, nullptr, &shutdown_signal_handler_threadfunc, nullptr) != 0)
    {
        cerr << "Couldn't create thread to handle shutdown signal. Terminating program" << endl;
    }

    // create server socket and start listening for new connections
    ServerSocket server_socket = ServerSocket(portnr);
    server_socket.start_listening();

    // join the thread for the sigint handler
    if (pthread_join(sigint_thread, nullptr) != 0)
    {
        cerr << "Failed to join thread: " << sigint_thread << endl;
    }
    */
    // program finished successfully
    return 0;
}