
// ConnectionHandler.hpp
#ifndef CONNECTION_HANDLER_HPP
#define CONNECTION_HANDLER_HPP

#include <string>
#include <vector>

using namespace std;

class ConnectionHandler
{
public:
    ConnectionHandler(int socket_fd);
    ~ConnectionHandler();

    static void *thread_handler(void *arg);
    void listen_connection();

private:
    int socket_fd_;
    std::vector<char> buffer_;
    bool connection_open;

    void receive_message(vector<char> &buf);
    void send_message(string &respxonse, unsigned short rlen);
    void close_connection();
    void process_message(std::string message);
    bool data_available(int timeout_ms);
};

#endif
