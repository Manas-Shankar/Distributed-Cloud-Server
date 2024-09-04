###Repo for the Distributed cloud server project done as part of the Software Systems course at Upenn.###

###Built together with Priya D'Costa, Paul Kathmann, and Rupkatha Hira at the University of Pennsylvania.###

# Making All Files

    1. Make all in backend-master
    2. Make all in kv
    3. Make all in frontend
    4. Make lb in frontend (For frontend load balancer)
    5. Make all in webmail-server > pop3 
    6. Make all in webmail-server > smtp 
    
# Running The Files
## Running KV nodes: From KV 

In separate terminals, run the following commands. -n is for node number, -g is group number, -c is number of write requests until checkpoint.

    1. Group 1: 

./kvstore_server -n 0 -g 1 -c 10

./kvstore_server -n 1 -g 1 -c 10

./kvstore_server -n 2 -g 1 -c 10

    2. Group 2: 

./kvstore_server -n 0 -g 2 -c 10

./kvstore_server -n 1 -g 2 -c 10

./kvstore_server -n 2 -g 2 -c 10

## Running Backend Master

./backend-master

## Running POP3

./pop3 5000 abc (pop3 is running on port 5000)

## Running SMTP
./smtp 5020 abc (smtp is running on port 5020)

## Running Frontend Server and Load Balancer
    1. Running the frontend load balancer: 

./lb
    
    2. Running the frontend servers: 

./frontend -p 8000

./frontend -p 8001

./frontend -p 8002

./frontend -p 8003

# Running in the browser
   1. Once all the above files are running the terminal, open a browser tab and type localhost/8000/register to go to the registration page. From here, you can register a user and view all the functionalities of this software.
      
   2. Use localhost/8000/admin-console to view the admin console

# Packages to Install

We have installed the following packages using homebrew on Mac OS

    1. brew install openssl
    2. brew install protobuf
    3. brew install grpc

# Common Issues

## Open SSL Version: 
Makefiles in pop3 and smtp contain a path to openssl in homebrew. Our systems have Openssl3 3.3.0, which is included in the path in the makefiles. Please ensure this is in sync with the openssl version on your system

## Update c_cpp_properties.json config file:
The includePath should be "${workspaceFolder}/**","/opt/homebrew/include"


