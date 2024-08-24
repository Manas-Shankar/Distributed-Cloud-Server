#include "../include/server_socket.hpp"
#include "../include/connection_handler.hpp"
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include "../include/header.h"

using namespace std;

ServerSocket::ServerSocket(int portnr) : portnr_(portnr)
{
}

void ServerSocket::create_socket()
{
    // creating and binding and listening to a socket
    listen_fd_ = socket(PF_INET, SOCK_STREAM, 0);
    if (listen_fd_ < 0)
    {
        cerr << "socket creation failed" << endl;
        close(listen_fd_);
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(portnr_);

    int yes = 1;
    if (setsockopt(listen_fd_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
    {
        cerr << "setsockopt failed" << endl;
        exit(EXIT_FAILURE);
    }

    if (bind(listen_fd_, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        cerr << "bind failed" << endl;
        close(listen_fd_);
        exit(EXIT_FAILURE);
    }
    if (listen(listen_fd_, 10) < 0)
    {
        cerr << "listen failed" << endl;
        close(listen_fd_);
        exit(EXIT_FAILURE);
    }
}

void ServerSocket::connect_client(int &socket_fd)
{
    struct sockaddr_in clientaddr;
    socklen_t clientaddrlen = sizeof(clientaddr);
    socket_fd = accept(listen_fd_, (struct sockaddr *)&clientaddr, &clientaddrlen);
    if (debug_flag)
    {
        cerr << "[" << socket_fd << "] New connection" << endl;
    }
}

void ServerSocket::start_listening()
{
    // create new socket
    create_socket();

    while (true)
    {
        if (shutdown_flag.load())
        {
            // stop the listener loop and start closing threads and shutting down
            break;
        }
        // Connecting the server to a client and storing socket fd in our array
        int socket_fd;
        // only connect to client when new connection is available to avoid infinite blocking
        if (new_connection_available(listen_fd_, 500))
        {
            connect_client(socket_fd);
            socket_fds_.push_back(socket_fd);

            // create a new thread to handle the new connection
            pthread_t thread;
            if (pthread_create(&thread, NULL, ConnectionHandler::thread_handler, new int(socket_fd)) == 0)
            {
                threads_.push_back(thread);
            }
        }

        // join any completed threads
        for (int i = 0; i < threads_.size();)
        {
            if (pthread_tryjoin_np(threads_.at(i), NULL) == 0)
            {
                // and remove them from the threads array
                threads_.erase(threads_.begin() + i);
            }
            else
            {
                i++;
            }
        }
    }
    // close listening socket
    close(listen_fd_);
    // wait for all threads to finish
    for (auto thread : threads_)
    {
        if (pthread_join(thread, nullptr) != 0)
        {
            cerr << "Failed to join thread: " << thread << endl;
        }
    }
}

// destructor for server socket
ServerSocket::~ServerSocket()
{
}
