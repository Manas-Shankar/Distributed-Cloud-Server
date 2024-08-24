#include "BackendMasterClient.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include "backend_master_as_server_service_impl.hpp"

void start_grpc_server()
{
    std::string line;
    std::ifstream config_file("bemaster_config.txt");
    if (config_file.is_open())
    {
        getline(config_file, line);
    }
    std::string server_address = line;
    BackendMasterServerImpl service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort("127.0.0.1:5056", grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait(); // Blocks here, waiting for server shutdown
}

void get_addresses(std::vector<std::string> &server_addresses, const std::string &filename)
{
    // read from the config.txt file to get the server address
    std::string line;
    std::ifstream config_file(filename);
    if (config_file.is_open())
    {
        while (getline(config_file, line))
        {
            server_addresses.push_back(line);
        }
        config_file.close();
    }
    else
    {
        std::cerr << "Unable to open file" << std::endl;
    }
}

void doHealthCheck(BackendMasterClient &client)
{
    // Copy `client` to avoid dangling references if `client` is temporary
    std::vector<std::string> daemonAddresses = client.getDaemonAddresses(); // Assuming you can get addresses from client
    while (true)
    {
        client.takeSnapShot();
        for (const auto &address : daemonAddresses)
        {
            client.checkNodeHealth(address);
        }
        client.updateActiveAddressSet();
        client.checkAndSetPrimary();

        if (client.anyUpdates())
        {
            // std::cout << "Sending active nodes" << std::endl;
            client.sendActiveNodes();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // Either join the thread or detach it depending on your use case
    // Note: You must ensure that 'client' and any other used resources are thread-safe and stay valid
}

int main(int argc, char **argv)
{
    std::vector<std::string> daemonAddresses1;
    std::vector<std::string> daemonAddresses2;

    std::vector<std::string> serverAddresses1;
    std::vector<std::string> serverAddresses2;

    get_addresses(serverAddresses1, "config.txt");
    get_addresses(serverAddresses2, "config_2.txt");

    get_addresses(daemonAddresses1, "daemon_config.txt");
    get_addresses(daemonAddresses2, "daemon_config_2.txt");

    for (auto x : daemonAddresses1)
    {
        std::cout << x << " ";
    }

    for (auto x : daemonAddresses2)
    {
        std::cout << x << " ";
    }

    BackendMasterClient client1(daemonAddresses1, serverAddresses1, 1);
    BackendMasterClient client2(daemonAddresses2, serverAddresses2, 2);

    std::thread server_thread(start_grpc_server);

    // std::thread healthcheck1(doHealthCheck, client1);
    // std::thread healthcheck2(doHealthCheck, client2);

    // std::thread healthcheckThread1([&client1](){
    //     doHealthCheck(client1);
    // });

    // std::thread healthcheckThread2([&client2](){
    //     doHealthCheck(client2);
    // });

    std::thread healthCheckThread1([&]()
                                   {
       while (true) {
           client1.takeSnapShot();
           for (const auto& address1 : daemonAddresses1) {
               client1.checkNodeHealth(address1);
           }

           client1.checkAndSetPrimary();
           
        //    if(client1.anyUpdates()) {
        //         client1.sendActiveNodes();
        //    }
           client1.sendActiveNodes();

           client1.updateActiveAddressSet();
           std::this_thread::sleep_for(std::chrono::milliseconds(500));
    } });

    std::thread healthCheckThread2([&]()
                                   {
       while (true) {
           client2.takeSnapShot();
           for (const auto& address2 : daemonAddresses2) {
               client2.checkNodeHealth(address2);
           }

           client2.checkAndSetPrimary();
           
        //    if(client2.anyUpdates()) {
        //         client2.sendActiveNodes();
        //    }
           client2.sendActiveNodes();
           client2.updateActiveAddressSet();
           std::this_thread::sleep_for(std::chrono::milliseconds(500));
    } });

    healthCheckThread1.join();
    healthCheckThread2.join();

    server_thread.join();
    return 0;
}
