
#ifndef SERVER_SOCKET_HPP
#define SERVER_SOCKET_HPP

#include <vector>
#include <pthread.h>
using namespace std;

class ServerSocket
{
public:
    ServerSocket(int portnr);
    ~ServerSocket();

    void start_listening();
    void create_socket();
    void connect_client(int &socket_fd);

private:
    // store all thread ids in a vector
    vector<pthread_t> threads_;
    // store all socket file descriptors in one vector
    vector<int> socket_fds_;
    // store portnumber which socket is listening to
    int portnr_;
    // fd to which our serversocket is listening
    int listen_fd_;
};

#endif // SERVER_SOCKET_HPP