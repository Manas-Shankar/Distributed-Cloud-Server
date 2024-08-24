
#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <vector>
#include <pthread.h>
#include <iostream>
#include <csignal>
#include <atomic>
#include <chrono>
#include <memory>
#include <sys/file.h>

using namespace std;

// global variable to store debugging flag
extern bool debug_flag;
// Global atomic flag to signal threads to shutdown
extern atomic<bool> shutdown_flag;

// connectionHandler thread args:
struct ConnectionHandlerThreadArgs
{
    int socket_fd;
    std::string server_type;
};

// helper functions in utils.cc
bool do_write(int fd, const char *buf, int len);
// bool do_write(int fd, const char *buf, int len)
int do_read(int fd, vector<char> &message);
// int do_read(int fd, vector<char> &buf, shared_ptr<chrono::system_clock::time_point> time_stamp_received);
void handle_inputs(int argc, char *argv[], int &portnr);
void block_sigint_in_threads();
void *shutdown_signal_handler_threadfunc(void *);
bool new_connection_available(int fd, int timeout_ms);
string string_to_lowercase(string str);

// connectionHandler.cc:
// void receive_message(int &socket_fd, vector<char> &buf, unsigned short rlen);
// void send_message(int &socket_fd, string &buf, unsigned short rlen);
// void close_connection(int socket_fd);
// void *thread_handler(void *arg);

#endif