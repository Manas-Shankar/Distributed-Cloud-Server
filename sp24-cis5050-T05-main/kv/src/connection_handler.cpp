#include "../include/header.h"
#include <cstdio>
#include <stdio.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include "../include/connection_handler.hpp"
#include <iostream>

using namespace std;

ConnectionHandler::ConnectionHandler(int socket_fd) : socket_fd_(socket_fd), buffer_(), connection_open(true)
{
}

ConnectionHandler::~ConnectionHandler()
{
    if (connection_open)
    {
        close_connection();
    }
}

void ConnectionHandler::receive_message(vector<char> &buf)
{
    // read message
    if (do_read(socket_fd_, buf) >= 0)
    {
        if (debug_flag)
        {
            string message_string(buf.begin(), buf.end());
            string debug_message = "[" + to_string(socket_fd_) + "] " + "C: " + message_string;
            cerr << debug_message;
            // cerr << "[" << socket_fd_ << "] " << "C: " << message_string;
        }
    }
    else
    {
        cerr << "Failed to read message" << endl;
    }
}

void ConnectionHandler::send_message(string &response, unsigned short rlen)
{
    // unsigned short wlen = htons(rlen);
    // do_write(socket_fd_, (char *)&wlen, sizeof(wlen));
    if (do_write(socket_fd_, response.data(), rlen))
    {
        if (debug_flag)
        {
            string debug_message = "[" + to_string(socket_fd_) + "] " + "S: " + response;
            cerr << debug_message;
        }
    }
    else
    {
        cerr << "Failed to send message: " << response << endl;
    }
}

void ConnectionHandler::close_connection()
{
    // print
    if (debug_flag)
    {
        cerr << "[" << socket_fd_ << "] "
             << "Connection closed" << endl;
    }
    // close channel
    close(socket_fd_);

    connection_open = false;

    // close thread when done
    pthread_exit(NULL);
}

void *ConnectionHandler::thread_handler(void *arg)
{
    int *socket_fd_ptr = static_cast<int *>(arg);
    int socket_fd = *socket_fd_ptr;
    ConnectionHandler handler(socket_fd);
    string welcome_message = "+OK Server ready (Author: Paul Kathmann / kathmann)\r\n";
    handler.send_message(welcome_message, welcome_message.length());
    delete socket_fd_ptr;
    handler.listen_connection();

    return nullptr;
}

void ConnectionHandler::listen_connection()
{
    // read from client how many chars it will send:
    unsigned short rlen;
    // run a while loop until interrupted by QUIT or CTRL + C
    while (true)
    {
        if (shutdown_flag.load())
        {
            string shutdown_message = "-ERR Server shutting down\r\n";
            send_message(shutdown_message, (unsigned short)(shutdown_message.length() * sizeof(char)));
            close_connection();
        }

        // block for 500ms or until data is available (whatever happens first) and if there is data available start reading it
        if (data_available(500))
        {
            // allocate buffer size according to how many bytes will be read
            vector<char> buffer;
            // server receives a message from client
            receive_message(buffer);
            // handle the message depending
            string message(buffer.begin(), buffer.end());
            process_message(message);
        }
    }
}

void ConnectionHandler::process_message(string message)
{
    // parse message into command and text
    // size_t pos = message.find(' ');
    // string command = message.substr(0, pos);
    string command;
    string text;
    size_t pos = 4;
    if (message.length() >= 6)
    {
        command = string_to_lowercase(message.substr(0, pos));
        text = message.substr(pos + 1);
    }

    if (command == "echo" && (message.at(pos) == ' ' || message.at(pos) == '\r'))
    {
        // respond to message with +OK <text>
        string response = "+OK " + text;
        unsigned short res_len = sizeof(char) * response.length();
        send_message(response, res_len);
    }
    else if (command == "quit" && message.length() == 6)
    {
        string response = "+OK Goodbye!\r\n";
        unsigned short res_len = sizeof(char) * response.length();
        send_message(response, res_len);
        close_connection();
    }
    else
    {
        string response = "-ERR Unknown command\r\n";
        unsigned short res_len = sizeof(char) * response.length();
        send_message(response, res_len);
    }
}

bool ConnectionHandler::data_available(int timeout_ms)
{
    // setup my fd set
    fd_set read_fds;
    // setting set to empty set
    FD_ZERO(&read_fds);
    // adding my socket_fd_ to the read_fds set
    FD_SET(socket_fd_, &read_fds);

    // parse timeout into timeval struct to pass into select function
    struct timeval timeout;
    timeout.tv_sec = timeout_ms / 1000;
    timeout.tv_usec = (timeout_ms % 1000) * 1000;

    if (select(socket_fd_ + 1, &read_fds, NULL, NULL, &timeout) == -1)
    {
        return false;
    }

    return FD_ISSET(socket_fd_, &read_fds);
}