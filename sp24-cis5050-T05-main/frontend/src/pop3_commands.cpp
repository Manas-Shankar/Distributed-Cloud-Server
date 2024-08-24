#include "../include/pop3_commands.h"

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <grpcpp/grpcpp.h>
#include <memory>
#include <string>
#include "../include/utils.h"

//grpc Files
#include "../grpc_proto/webmail_grpc_proto/webmailgrpc.grpc.pb.h"
#include "../grpc_proto/webmail_grpc_proto/webmailgrpc.pb.h"

using webmailgrpc::CommandRequest;
using webmailgrpc::CommandResponse;
using webmailgrpc::WebmailService;

using namespace std;

int numMessages = 0; // store the number of mails

std::string POP3Client::sendCommand(std::string cmd) {

    // Prepare the request
    CommandRequest request;
    request.set_command(cmd);

    // Prepare the response
    CommandResponse response;

    // Context for the client
    grpc::ClientContext context;

    // The actual RPC
    grpc::Status status = stub_->SendCommand(&context, request, &response);

    // Act upon its status
    if (status.ok()) {
        return response.response(); //TODO Receive messages from Rupkatha 
    } else {
        return status.error_message();
    }
}


std::string POP3Client::userAndPass(std::string userName, std::string password) { //To be Done when the user starts the session

    std::string response = "";
    cout<< "POP3 Username" << userName << endl;
    cout<< "POP3 Password" << password << endl;
    response = sendCommand("USER " + userName);

    if (response.substr(0,3) != "+OK") {
        return "Error in User ID!";
    }

    response = sendCommand("PASS " + password);

    if (response.substr(0,3) != "+OK") {
        return "Error in Password!";
    }

    return "Login Successful!"; //Display Message Discuss with Rupkatha
}

std::string POP3Client::stat() { 
    std::string response = "";

    response = sendCommand("STAT"); // Command to get mailbox statistics

    if (response.substr(0,3) != "+OK") {
        return "Error in Retreiving Statistics!";
    }

    std::stringstream ss(response);
    std::string temp;
    int middleNumber;
    
    // Assuming the format is always "+OK number number"
    ss >> temp;          // Read the first part ("+OK")
    ss >> middleNumber;  // Read the middle number

    return to_string(middleNumber); //Size of the mailbox
}

std::string POP3Client::retr(std::string num) { 
    
    std::string response = "";

    response = sendCommand("RETR "+ num); // Command to get mailbox statistics
    cout << "POP3 RETR CONTENT" << response << endl;

    if (response.substr(0,3) != "+OK") {
        return "Error in Retreiving email!";
    }

    string message = extractSubstring(response);

    return message; //Mails to display
}


std::string POP3Client::list() { 
    
    std::string response = "";
    response = sendCommand("LIST"); // Terminate the session

    if (response.substr(0,3) != "+OK") {
        cout << "LIST " <<  response << endl;
        return "Error in Listing";
    }

    // Find the position of "OK" and "messages"
    size_t posOK = response.find("OK");
    size_t posMessages = response.find("messages");

    // Extract the substring between "OK" and "messages"
    std::string numberStr = response.substr(posOK + 3, posMessages - posOK - 3);
    
    // Convert the extracted substring to an integer
    numMessages = std::stoi(numberStr);

    return numberStr;//Return the number of messages
}


std::string POP3Client::deleteMail(std::string num) {
    std::string response = "";
    response = sendCommand("DELE "+num); // Terminate the session

    if (response.substr(0,3) != "+OK") {
        return "Error in Deleting";
    }

    return "Delete Successful!"; //Display Message

}

std::string POP3Client::quit() {
    
    std::string response = "";
    response = sendCommand("QUIT"); // Terminate the session

    if (response.substr(0,3) != "+OK") {
        return "Error in Quitting";
    }

    return "Quit Successful!"; //Display Message
}


std::string POP3Client::uidl(std::string num) {
    
    std::string response = "";
    response = sendCommand("UIDL "+num); // Terminate the session

    return "Quit Successful!"; //Display Message
}

