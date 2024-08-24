#include "../include/smtp_commands.h"

using namespace std;

std::string SMTPClient::sendCommand(std::string cmd) {
    // Prepare the request
    CommandRequest request;
    request.set_command(cmd);

    // Prepare the response
    CommandResponse response;

    // Context for the client
    ClientContext context;

    // The actual RPC
    Status status = stub_->SendCommand(&context, request, &response);

    // Act upon its status
    if (status.ok()) {
        std::cout<<"\nOK status after sending command "<<cmd<<"\n";
        return response.response();
    } else {
        std::cout<<"\nERROR status after sending command "<<cmd<<"\n";
        return status.error_message();
    }
}


std::string SMTPClient::connect(std::string userID) {

    std::string response = "";
    response =  sendCommand("HELO " + userID); // Send the Initial HELO

    if (response.substr(0,3) != "+OK") {
        return "Authentication Unsuccessful!";
    }

    return "Authentication Successful!"; //Display Message Discuss with Rupkatha

}

std::string SMTPClient::senderDetails(std::string senderEmail) {

    std::string response = "";

    response =  sendCommand("MAIL FROM: <" + senderEmail + "@localhost>"); // Sender email

    if (response.substr(0,6) != "250 OK") {
        return "Issue with MAIL FROM";
    } else {
        return "MAIL FROM Successful";
    }
}

std::string SMTPClient::receiverDetails(std::string receiverEmail) {

    std::string response = "";

    response = sendCommand("RCPT TO: <" + receiverEmail + ">"); // Recipient email

    if (response.substr(0,6) != "250 OK") {
        return "Issue with RCPT TO";
    } else {
        return "RCPT TO Successful";
    }
    
}

std::string SMTPClient::sendData(std::string data) {

    std::string response = "";

    response = sendCommand("DATA"); //SEND THE ACTUAL EMAIL CONTENT

    std::cout << "Response " << response << std::endl;

    if (response.substr(0,3) != "354") {
        return "Error with sending the actual data";
    } else {
        std::cout <<"\nSending actual email content"<< std::endl;
        response = sendCommand(data); //SEND THE ACTUAL EMAIL CONTENT
        std::cout << "\nResponse after sending actual data\n" << response << std::endl;
    }

    return "\nreturning from send data\n";
}

std::string SMTPClient::quit() {
    
    std::string response = "";
    response = sendCommand("QUIT"); // Terminate the session

    if (response.substr(0,3) != "221") {
        return "Error in Quitting";
    }

    return "Successfully Quit!";
}

std::string SMTPClient::sendDot() {
    std::cout<<"\nTrying to send dot\n";

    std::string response = "";

    response = sendCommand("."); //SEND THE ACTUAL EMAIL CONTENT

    if (response.substr(0,3) != "250") {
        std::cout<<"\nERROR status after sending dot\n";
        return "Error with sending the actual data";
    }
    std::cout<<"\nOK status after sending dot\n";

    return "success";
}


