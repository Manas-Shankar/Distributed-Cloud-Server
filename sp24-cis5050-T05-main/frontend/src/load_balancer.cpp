#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include<arpa/inet.h>
#include <fstream>
#include <iostream>
#include <map>
#include <pthread.h>
#include "../include/utils.h"


#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)

using namespace std;

// Server class, to store details regarding active servers
class Server {

    public:
    	int id;         // associated ID of the server
    	string ip;     // ip address of server
    	int port;      // port of operation
    	bool running;  // active status
};


// all servers
int NUM_OF_SERVERS;
map<int, Server> servers;

// mutex lock
pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER;
int parse_all_servers(const char* filename)
{
  ifstream ifs(filename);
	string line = "";
	int id = 1;

  // read config file
	while (getline(ifs, line)) {
        // get IP address and port number
        size_t colon = line.find(":");
        if (colon == string::npos) {
            fprintf(stderr, "Wrong IP address and port number format !\n");
            exit(1);
        }
        string ip_addr = line.substr(0, colon);
        int port = atoi(line.substr(colon+1).c_str());

		Server server;
        server.id = id;
        server.ip = ip_addr;
        server.port = port;
        server.running = false;
        servers[id++] = server;
	}

  return id - 1;
}


/*
 * loop to check server state every 3 seconds. Opens a socket to the associated server and attempts a connection to check status.
 */
void* check_server_state(void* arg) {
	while (true) {
		for (int i = 1; i <= NUM_OF_SERVERS; i++) {
			int sockfd = socket(PF_INET, SOCK_STREAM, 0);
      struct sockaddr_in servaddr;
      inet_pton(AF_INET ,servers[i].ip.c_str(), &(servaddr.sin_addr));
      servaddr.sin_port = htons(servers[i].port);
      servaddr.sin_family = AF_INET;

			if (connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) == 0) {
				pthread_mutex_lock(&mutex_lock);
				servers[i].running = true;
				pthread_mutex_unlock(&mutex_lock);

				cout << "server #" << i << " is active" << endl;
			} else {
				pthread_mutex_lock(&mutex_lock);
				servers[i].running = false;
				pthread_mutex_unlock(&mutex_lock);

				cout << "server #" << i << " is down" << endl;
			}

			close(sockfd);
		}

    cout << "#######"<< endl;   // delimiter
		sleep(3);
	}

	return NULL;
}


int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "[Usage]: ./lb -p <PORT NUMBER> <CONFIG FILE NAME>\n");
        exit(1);
    }

    // local variables
    int port = 0;

    // parse command line arguments
    int c;
    while ((c = getopt(argc, argv, "p:")) != -1) {
        switch (c) {
            case 'p':
                port = atoi(optarg);
                break;
            default:
                exit(1);
        }
    }

    // parse server config file
    const char* filename = argv[optind];
    NUM_OF_SERVERS = parse_all_servers(filename);

    // create socket for listening
    int listen_fd = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(port);

    bind(listen_fd, (struct sockaddr*) &servaddr, sizeof(servaddr));

    // listen on port number and accept connection
    listen(listen_fd, 1000);

    // check server state
    pthread_t state_thread;
    pthread_create(&state_thread, NULL, check_server_state, NULL);

    int handler_server_id = 1;
    while (true) {
        // accept a connection from client
        struct sockaddr_in client_addr;
        socklen_t client_addrlen = sizeof(client_addr);

        int fd = accept(listen_fd, (struct sockaddr*) &client_addr, &client_addrlen);
        if (fd < 0) continue;

        // find next available server to handle this request
    		int count = 0;
    		pthread_mutex_lock(&mutex_lock);

    		while (!servers[handler_server_id].running) {
    			handler_server_id = (handler_server_id + 1) % NUM_OF_SERVERS;
          if (handler_server_id == 0) {
            handler_server_id = NUM_OF_SERVERS;
          }
    			count++;
    			if (count >= NUM_OF_SERVERS) break;

    		}
    		pthread_mutex_unlock(&mutex_lock);

        // http header
        string header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: ";

        // no server is running now
        if (count >= NUM_OF_SERVERS) {
          cout << "No server is running now" << endl;
          string content = "NO server is RUNNING !";
          string response = header + to_string(content.length()) + "\r\n\r\n";
          response += content;
          write(fd, response.c_str(), response.length());
        }

        else {
          cout << "Accept a new connection, redirect to server #"
          << to_string(handler_server_id) << endl;

          string content = get_file_content_as_string("html/redirect.html");
          string server = servers[handler_server_id].ip+":"+to_string(servers[handler_server_id].port);
          replace_all(content, "$server", server);
          string response = header + to_string(content.length()) + "\r\n\r\n";
          response += content;
          write(fd, response.c_str(), response.length());

          handler_server_id = (handler_server_id + 1) % NUM_OF_SERVERS;
          if (handler_server_id == 0) {
            handler_server_id = NUM_OF_SERVERS;
          }
        }

        close(fd);
    }

    // close load balancer
	  close(listen_fd);
    return 0;
}
