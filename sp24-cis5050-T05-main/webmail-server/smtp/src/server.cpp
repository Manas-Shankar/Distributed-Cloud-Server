#include "../include/server.hpp"
#include "../include/kv_client.hpp"
#include <iostream>
#include <string>
#include <unistd.h>
#include <algorithm>
#include <regex>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>


std::string getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
// void appendEmailToMbox(std:: string &emailData, std:: string &sender, std::vector<std::string> &recipients) {
//     std::cout<<"\nsender: "<<sender;
//     // std::cout<<"\nreceipients: "<<recipients;
//     std::cout<<"\ndata: "<<emailData;
// }

EmailServer::EmailServer(int port, bool verbose, const std::string& mailboxDir)
    : port(port), verbose(verbose), mailboxDir(mailboxDir) {}

bool EmailServer::processCommand(const std::string& sessionId, const std::string& command, std::string& response) {
    // Retrieve the session from the session manager
    EmailSession* session = sessionManager.getSession(sessionId);
    if (!session) {
        response = "Session not found or expired, please login again.";
        return false;
    }

    // Handle the SMTP command processing
    handleSMTPCommands(*session, command, response);
    return true; // Indicate successful processing (actual success depends on the response from handleSMTPCommands)
}

// void EmailServer::cleanup() {
//     std::lock_guard<std::mutex> lock(connectionsMutex);
//     for (int clientSock : activeConnections) {
//         close(clientSock);
//     }
//     activeConnections.clear();
// }

// void EmailServer::handleSigInt(int sig) {
//     running = false;
//     cleanup();
//     exit(0);
// }

void EmailServer::resetSession(EmailSession& session) {
    // Reset session state after email is sent or at any other appropriate time
    session.sender.clear();
    session.recipients.clear();
    session.emailData.clear();
    session.helo = false;
    session.mail_from = false;
    session.rcpt_to = false;
    session.receivingData = false;
}

void EmailServer::handleSMTPCommands(EmailSession& session, const std::string& command, std::string& response) {
    // Extract command type (e.g., "HELO", "MAIL FROM", etc.)
    size_t firstSpace = command.find(' ');
    std::string commandType = command.substr(0, firstSpace);
    std::string args = command.substr(firstSpace + 1);
    std::cout<<"\nString received:"<<command<<"end\n";
    if (commandType == "HELO") {
        std::cout<<"\nCommand received: "<<command;
        if (session.helo) { // Only allow HELO to be set once per session
            response = "503 Bad sequence of commands.";
        } else {
            session.helo = true;
            response = "250 Hello, pleased to meet you.";
        }
    } else if (command.rfind("MAIL FROM:", 0) == 0 && session.helo) {
        std::cout<<"\nCommand received: "<<command;
        if (session.mail_from) {
            response = "503 Sender already specified.";
        } else {
            std::regex emailRegex("<(.+?)>");
            std::smatch matches;
            if (std::regex_search(args, matches, emailRegex) && matches.size() > 1) {
                session.sender = matches[1];
                session.mail_from = true;
                response = "250 OK";
            } else {
                response = "501 Syntax error in parameters or arguments.";
            }
        }
    } else if (command.rfind("RCPT TO:", 0) == 0 && session.mail_from) {
        std::cout<<"\nCommand received: "<<command;
        std::regex pattern("<([^<>@]+)@([^<>@]+)>");
        // std::regex emailRegex("<(.+?)>");
        std::smatch matches;
        if (std::regex_search(args, matches, pattern) && matches.size() > 1) {
            session.addRecipient(matches[1], matches[2]);

            session.rcpt_to = true;
            response = "250 OK";
        } else {
            response = "501 Syntax error in parameters or arguments.";
        }
    } else if (commandType == "DATA" && session.rcpt_to) {
        std::cout<<"\nCommand received: "<<command;
        if (!session.receivingData) {
            session.receivingData = true;
            response = "354 Start mail input; end with <CRLF>.<CRLF>";
        }
    } else if (session.receivingData) {

        if (command == ".") {
            std::cout<<"\nDot received\n";
            // appendEmailToMbox(session.emailData, session.sender, session.recipients);
            std::cout<<"\nMail content before actually sending:"<<session.emailData<<"\n";
            sendToKV(session.emailData, session.sender, session.recipients);
            session.receivingData = false; // Stop receiving data
            resetSession(session); // Reset the session state
            response = "250 Message accepted for delivery.";
        } else {
            std::cout<<"\nReceiving data waiting for dot\n";
            session.emailData += command ; //TODO: check if \r\n is required.
            response = "250 Dot not received.";
        }
    } else if (commandType == "QUIT") {
        std::cout<<"\nCommand received: "<<command;
        response = "221 Bye";  // Provide an affirmative and polite QUIT response
        resetSession(session); // Clean up the session
        // Signal the end of this session in some way, e.g., by closing the connection or marking the session as finished
    } else {
        std::cout<<"\nCommand unrecognized\n";
        response = "500 Syntax error, command unrecognized";
    }
}

bool EmailServer::processLogin(const std::string& sessionId, const std::string& username, std::string& result) {
    // Logic to authenticate user and create session
    // if (authenticate(username)) {
    if (true) {
        sessionManager.createSession(sessionId);
        result = "Login successful";
        return true;
    }
    result = "Login failed";
    return false;
}

void EmailServer::sendToKV(const std::string& emailData, const std::string& sender, std::vector<EmailSession::EmailAddress>& recipients) {
    std::string mailHeader = "From <" +sender + " " + getCurrentDateTime() + "\r\n";
    std::string send_data = mailHeader+emailData;
    std::cout << "Inside send to KV" << send_data <<std::endl;
    for(int i=0; i<recipients.size(); i++) {
        std::string row = recipients[i].localPart;
        std::string column = "mbox";

    
        KVClient kvClient(grpc::CreateChannel("127.0.0.1:5050", grpc::InsecureChannelCredentials()));

        std::string got_data = kvClient.get(row, column);

        // Check if data retrieval was successful
        // if (got_data.empty()) {
        //     std::cerr << "Failed to retrieve email data for user: " << row << std::endl;
        //     return;
        // }

        std::string total_data = got_data+send_data;


        bool success = kvClient.put(row, column, total_data);

        if (!success) {
            std::cerr << "Failed to store email data in KV store." << std::endl;
        }

        std::cerr << "Send to KV!." << std::endl;
    }
    
    
}
