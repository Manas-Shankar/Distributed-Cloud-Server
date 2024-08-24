#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include "../include/header.h"

using namespace std;

/*
bool do_read(int fd, char *buf, int len)
{
    int rcvd = 0;
    while (rcvd < len)
    {
        int n = read(fd, &buf[rcvd], len - rcvd);
        if (n < 0)
            return false;
        rcvd += n;
        printf("read %d characters\n", n);
    }
    return true;
}*/

int do_read(int fd, vector<char> &message)
{
    int rcvd = 0;
    char temp;
    while (true)
    {
        int n = read(fd, &temp, sizeof(char));
        if (n < 0)
            return -1;
        message.push_back(temp);
        ++rcvd;
        if (rcvd >= 2 && message.at(rcvd - 1) == '\n' && message.at(rcvd - 2) == '\r')
        {
            break;
        }
    }
    // buf.at(rcvd - 2) = 0;
    return rcvd;
}

/*
int do_read(int fd, vector<char> &message)
{
    int rcvd = 0;
    char buffer[1024];
    while (true)
    {
        int n = read(fd, &temp, sizeof(buffer) - 1);
        if (n < 0)
            return -1;
        message.push_back(temp);
        ++rcvd;
        if (rcvd >= 2 && message.at(rcvd - 1) == '\n' && message.at(rcvd - 2) == '\r')
        {
            break;
        }
    }
    // buf.at(rcvd - 2) = 0;
    return rcvd;
}*/

bool do_write(int fd, const char *buf, int len)
{
    int sent = 0;
    while (sent < len)
    {
        int n = write(fd, &buf[sent], len - sent);
        if (n < 0)
        {
            return false;
        }
        sent += n;
    }
    return true;
}

void handle_inputs(int argc, char *argv[], int &portnr)
{
    int opt;

    // use getopt to retrieve user input
    while ((opt = getopt(argc, argv, "p:av")) != -1)
    {
        switch (opt)
        {
        case 'p':
            portnr = atoi(optarg);
            break;
        case 'a':
            cerr << "Paul Kathmann (kathmann)" << endl;
            exit(EXIT_SUCCESS);
            break;
        case 'v':
            debug_flag = true;
            break;
        case '?':
            cerr << "Usage: " << argv[0] << "[-p portnumber] [-a] [-v]" << endl;
            exit(EXIT_FAILURE);
        }
    }
}

void block_sigint_in_threads()
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    pthread_sigmask(SIG_BLOCK, &set, NULL);
}

void *shutdown_signal_handler_threadfunc(void *)
{
    sigset_t set;
    int sig;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);

    // Wait for SIGINT
    if (sigwait(&set, &sig) == 0)
    {
        shutdown_flag.store(true);
    }
    else
    {
        std::cerr << "Error waiting for SIGINT\n";
    }

    // close thread when done
    pthread_exit(NULL);
}

bool new_connection_available(int fd, int timeout_ms)
{
    // setup my fd set
    fd_set read_fds;
    // setting set to empty set
    FD_ZERO(&read_fds);
    // adding my socket_fd_ to the read_fds set
    FD_SET(fd, &read_fds);

    // parse timeout into timeval struct to pass into select function
    struct timeval timeout;
    timeout.tv_sec = timeout_ms / 1000;
    timeout.tv_usec = (timeout_ms % 1000) * 1000;

    if (select(fd + 1, &read_fds, NULL, NULL, &timeout) == -1)
    {
        return false;
    }

    return FD_ISSET(fd, &read_fds);
}

string string_to_lowercase(string str)
{
    for (auto it = str.begin(); it < str.end(); it++)
    {
        if (*it >= 'A' && *it <= 'Z')
        {
            *it += 32;
        }
    }
    return str;
}