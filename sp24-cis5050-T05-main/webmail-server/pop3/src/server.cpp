#include "../include/server.hpp"
#include "../include/kv_client.hpp"
#include <iostream>
#include <string>
#include <unistd.h>
#include <algorithm>
#include <regex>
#include <openssl/md5.h>

//Function to get the hashing of a string, used for UIDL
void computeDigest(char *data, int dataLengthBytes, unsigned char *digestBuffer)
{
  /* The digest will be written to digestBuffer, which must be at least MD5_DIGEST_LENGTH bytes long */

  MD5_CTX c;
  MD5_Init(&c);
  MD5_Update(&c, data, dataLengthBytes);
  MD5_Final(digestBuffer, &c);
}

//Wrapper function over computeDigest
std::string computeDigestString(char *data, int dataLengthBytes, unsigned char *digestBuffer) {
    computeDigest(data, dataLengthBytes, digestBuffer);
    std::stringstream hexStream;
    for(int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        hexStream << std::hex << std::setw(2) << std::setfill('0') << (int)digestBuffer[i];
    }
    return hexStream.str();
}

std::string dropFirstLine(const std::string& message) {
    std::istringstream stream(message);
    std::string line;
    std::string result;

    // Get the first line and discard it
    std::getline(stream, line);

    // Read the rest of the data
    while (std::getline(stream, line)) {
        result += line + "\r\n"; // Append line and return carriage
    }

    return result;
}

//Function to get current date and time
std::string getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void appendEmailToMbox(std:: string &emailData, std:: string &sender, std::vector<std::string> &recipients) {
    std::cout<<"\nsender: "<<sender;
    // std::cout<<"\nreceipients: "<<recipients;
    std::cout<<"\ndata: "<<emailData;
}


/***********************************************************************
*COMMAND HANDLING FUNCTIONS
************************************************************************/
#include "server.hpp"
#include <regex>
#include <iostream>
#include <sstream>

// Handle user authentication command
std::string EmailServer::handleUSERCommand(EmailSession& session, const std::string& username) {
    std::cout<<"\nhandleUSERCommand trigggered\n";
    if (!username.empty()) {
        session.currentUsername = username;
        return "+OK User name accepted, password required";
    } else {
        return "-ERR Invalid username format";
    }
}

// Handle password authentication command
std::string EmailServer::handlePASSCommand(EmailSession& session, const std::string& password) {
    std::cout<<"\nhandlePASSCommand triggered\n";
    if (!session.currentUsername.empty() && password == "cis505") {
        session.isAuthenticated = true;
        initializeSession(session, session.currentUsername);
        return "+OK Password accepted";
        
    } else {
        return "-ERR Invalid password or username not set";
    }
    
}

std::string EmailServer::handleRSET(EmailSession& session) {
    // Clear deletion marks and other stateful aspects of the session
    std::cout<<"\n handleRSET triggered\n";
    session.deletedMessages.clear();
    session.emailData.clear();
    session.recipients.clear();
    // Optionally reset other fields if necessary
    session.mail_from = false;
    session.rcpt_to = false;
    session.receivingData = false;

    return "+OK";
}


// Handle STAT command - statistics about the mailbox
std::string EmailServer::handleSTATCommand(EmailSession& session) {
    std::cout<<"\n handleSTATCommand triggered\n";
    std::ostringstream response;
    response << "+OK " << session.messageInfos.size() << " messages";
    return response.str();
}

// Handles the LIST command without specific message number
std::string EmailServer::handleLISTNoArg(EmailSession& session) {
    std::cout<<"\n handleLISTNoArg triggered\n";

    std::stringstream response;
    response << "+OK\r\n";
    std::cout << "number of messages: "<<session.messageInfos.size()<<"\n";
    for (size_t i = 0; i < session.messageInfos.size(); i++) {
        if (!(session.deletedMessages.size()>i && !session.deletedMessages[i])) {
            // totalSize += session.messageInfos[i].short_size;
            response << i + 1 << " " << session.messageInfos[i].short_size << "\r\n";
        }
    }
    response << ".";
    return response.str();
}

std::string EmailServer::handleQUIT(EmailSession& session) {
    std::cout<<"\n handleQUIT triggered\n";
    // Perform any necessary cleanup or finalization tasks
    // This might include updating session states, saving data, or releasing resources

    // Since this is the end of the session, you might want to perform session cleanup
    //TODO:delete messages
    deleteMessages(session);
    resetSession(session); // Optional: reset session details for reuse or to clear sensitive information
    sessionManager.endSession(session.session_id);
    // Response to the client indicating that the service is closing the connection
    return "+OK Goodbye"; // Standard POP3 response for QUIT command
}


// Handles the LIST command with specific message number
std::string EmailServer::handleLIST(EmailSession& session, const std::string& command) {
    std::cout<<"\n handleLIST triggered\n";
    int msgIndex = std::stoi(command) -1; // Extract message index and adjust for 0-based indexing
    if (msgIndex < 0 || msgIndex >= session.messageInfos.size()) {
        return "-ERR no such message";
    }
    if(session.deletedMessages.size()>msgIndex && session.deletedMessages[msgIndex]) {
        return "-ERR no such message";
    }

    return "+OK " + std::to_string(msgIndex + 1) + " " + std::to_string(session.messageInfos[msgIndex].short_size);
}

// Handles the RETR command to retrieve a specific message
std::string EmailServer::handleRETRCommand(EmailSession& session, const std::string& command) {
    std::cout<<"\n handleRETRCommand triggered\n";
    // int msgIndex = std::stoi(command.substr(5)) - 1; // Extract message index and adjust for 0-based indexing
    int msgIndex = std::stoi(command) -1; // Extract message index and adjust for 0-based indexing

    std::cout<<"\nNo of messages = "<<session.messageInfos.size();
    if (msgIndex < 0 || msgIndex >= session.messageInfos.size() ) {
        return "-ERR no such message";
    }
    if( session.deletedMessages.size()>msgIndex && session.deletedMessages[msgIndex]) {
        return "-ERR no such message";
    }

    std::string messageContent = readMessage(session, msgIndex);

    std::cout<<messageContent<<" received\n";
    std::string processedContent = dropFirstLine(messageContent); // Process to drop the first line
    std::string response = "+OK message follows\r\n" + processedContent + ".\r\n";
    return response;
}


// Handles the DELE command to mark a message for deletion
std::string EmailServer::handleDELECommand(EmailSession& session, const std::string& command) {
    std::cout<<"\n handleDELECommand triggered\n";
    int msgIndex = std::stoi(command) -1; // Extract message index and adjust for 0-based indexing
    std::cout<<"\ndelete index="<<msgIndex<<"\n";
    if (msgIndex < 0 || msgIndex >= session.messageInfos.size()) {
        return "-ERR no such message";
    }
    if(session.deletedMessages.size()<=msgIndex) {
        session.deletedMessages.resize(msgIndex+1);
    }
    session.deletedMessages[msgIndex] = true; // Mark the message as deleted
    return "+OK message " + std::to_string(msgIndex + 1) + " marked for deletion";
}


// Handles the UIDL command with specific message number
std::string EmailServer::handleUIDLCommand(EmailSession& session, const std::string& command) {
    std::cout<<"\n handleUIDLCommand triggered\n";
    int msgIndex = std::stoi(command) -1; // Extract message index and adjust for 0-based indexing
    if (msgIndex < 0 || msgIndex >= session.messageInfos.size()) {
        return "-ERR no such message";
    }

    if (msgIndex < session.deletedMessages.size() && session.deletedMessages[msgIndex]) {
        return "-ERR message marked for deletion";
    }

    unsigned char digestBuffer[MD5_DIGEST_LENGTH];
    std::string messageContent = readMessage(session, msgIndex);
    std::string digest = computeDigestString(const_cast<char*>(messageContent.data()), messageContent.size(), digestBuffer);
    return "+OK " + std::to_string(msgIndex + 1) + " " + digest;
}

// Handles the UIDL command without specific message number
std::string EmailServer::handleUIDLNoArg(EmailSession& session) {
    std::cout<<"\n handleUIDLNoArg triggered\n";
    std::stringstream response;
    response << "+OK\r\n";
    unsigned char digestBuffer[MD5_DIGEST_LENGTH];
    
    for (size_t i = 0; i < session.messageInfos.size(); i++) {
        if (!(session.deletedMessages.size()>i && !session.deletedMessages[i])) {
            std::string messageContent = readMessage(session, i);
            std::string digest = computeDigestString(const_cast<char*>(messageContent.data()), messageContent.size(), digestBuffer);
            response << i + 1 << " " << digest << "\r\n";
        }
    }
    response << ".";
    return response.str();
}


// Function to read a message from the session by its index

/***********************************************************************
*END OF COMMAND HANDLING FUNCTIONS
************************************************************************/
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
    response = handlePOP3Commands(*session, command);
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
    session.currentUsername.clear();
    session.sender.clear();
    session.recipients.clear();
    session.emailData.clear();


    session.messageInfos.clear();
    session.deletedMessages.clear();

    session.helo = false;
    session.mail_from = false;
    session.rcpt_to = false;
    session.receivingData = false;
    session.isAuthenticated = false;
}


// Function to trim leading and trailing spaces
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return "";  // String is all spaces
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}


std::string EmailServer::handlePOP3Commands(EmailSession& session, const std::string& command) {
    std::string trimmedInput = trim(command);
    size_t spaceIndex = trimmedInput.find(' ');
    std::string commandType, args;
    if (spaceIndex != std::string::npos) {
        commandType = trimmedInput.substr(0, spaceIndex);
        args = trimmedInput.substr(spaceIndex + 1);
    } else {
        commandType = trimmedInput;
        args = "";  // No arguments
    }

    std::cout<<command << std::endl;

    if (commandType == "USER") {
        return handleUSERCommand(session, args);
    } else if (commandType == "PASS") {
        return handlePASSCommand(session, args);
    } else if (commandType == "STAT") {
        return handleSTATCommand(session);
    } else if (commandType == "LIST") {
        if (args.empty()) {
            return handleLISTNoArg(session);
        } else {
            return handleLIST(session, args);
        }
    } else if (commandType == "RETR") {
        return handleRETRCommand(session, args);
    } else if (commandType == "DELE") {
        return handleDELECommand(session, args);
    } else if (commandType == "UIDL") {
        if (args.empty()) {
            return handleUIDLNoArg(session);
        } else {
            return handleUIDLCommand(session, args);
        }
    } else if (commandType == "RSET") {
        return handleRSET(session);
    } else if (commandType == "NOOP") {
        return "+OK"; // Assuming you have a NOOP handling method or it just returns OK
    } else if (commandType == "QUIT") {
        // Assuming you have a method to handle QUIT
        return handleQUIT(session);
    } else {
        return "-ERR Unknown command";
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

void EmailServer::sendToKV(const std::string& emailData, const std::string& sender, const std::vector<std::string>& recipients) {
    std::string row = "some_row_identifier";  // Define how to identify rows
    std::string column = "some_column_identifier";  // Define how to identify columns

    KVClient kvClient(grpc::CreateChannel("127.0.0.1:5050", grpc::InsecureChannelCredentials()));
    bool success = kvClient.put(row, column, emailData);

    if (!success) {
        std::cerr << "Failed to store email data in KV store." << std::endl;
    }
}

// EmailServer::readMessage: Retrieve a message by its index from the session
std::string EmailServer::readMessage(EmailSession& session, int index) {
    // std::cout<<"Inside readmessage\n";
    if (index < 0 || index >= session.messageInfos.size()) {
        return "";  // If index is out of bounds
    }
    const auto& info = session.messageInfos[index];
    std::cout<<"\n info="<<info.offset<<"\n";

    // Assuming 'emailData' is a long string containing all emails concatenated
    if (static_cast<std::streamoff>(info.offset) + info.size > session.emailData.length()) {
        return "";  // Ensure we don't exceed the bounds of the email data
    }

    // Extract the message based on the stored offset and size
    return session.emailData.substr(info.offset, info.size);
}

void EmailServer::initializeSession(EmailSession& session, const std::string& username) {
    std::cout<<"\nEntered initializeSession\n";
    // Retrieve email data from KV store
    KVClient kvClient(grpc::CreateChannel("127.0.0.1:5050", grpc::InsecureChannelCredentials()));
    std::string emailData = kvClient.get(username, "mbox");

    // Check if data retrieval was successful
    if (emailData.empty()) {
        std::cerr << "Failed to retrieve email data for user: " << username << std::endl;
        return;
    } else {
        std::cout<<"\nRetrieved some data for user: "<< username << std::endl;
    }

    // Load the data into the session
    session.emailData = emailData;

    // Parse the email data to populate message information
    readAndParseMessages(session);

    // std::cout<<"\nAfter Initializing I'm getting "<<
}

void EmailServer::readAndParseMessages(EmailSession& session) {
    std::istringstream mboxStream(session.emailData); // Use a stringstream to simulate file reading
    std::string line;
    std::streampos messageStart = 0;
    size_t messageSize = 0;
    size_t short_messageSize = 0;

    while (std::getline(mboxStream, line)) {
        // std::cout<<"\n"<<line<<"\n";
        if (line.rfind("From ", 0) == 0) {
            if (messageSize > 0) { // Previous message end
                session.messageInfos.push_back({messageStart, messageSize, short_messageSize});
                messageSize = 0;
                short_messageSize = 0;
            }
            messageStart = mboxStream.tellg();
            messageStart -= line.size() + 1; // Adjust for the line just read
            messageSize += line.size() + 1; // Update message size
            // std::cout<<"\nmessage start: "<<messageStart;
        } else {
            messageSize += line.size() + 1; // Update message size
            short_messageSize += line.size() + 1; // Adjust for non-header lines
        }
    }

    // Don't forget the last message
    if (messageSize > 0) {
        session.messageInfos.push_back({messageStart, messageSize, short_messageSize});
    }
}

void EmailServer::deleteMessages(EmailSession& session) {
    std::cout<<"\nFinally deleting messages\n";
    std::string row = session.currentUsername; // Define the row
    std::string column = "mbox"; // Define the column

    // Create an instance of KVClient
    KVClient kvClient(grpc::CreateChannel("127.0.0.1:5050", grpc::InsecureChannelCredentials()));


    if(session.deletedMessages.size() == 0) {
        return;
    }
    // Concatenate non-deleted messages into a single string
    std::stringstream updatedEmailData;
    for (size_t i = 0; i < session.messageInfos.size(); ++i) {
        if (i>=session.deletedMessages.size() || !session.deletedMessages[i]) {
            std::string messageContent = readMessage(session, i);
            updatedEmailData << messageContent;
        }
    }

    // First delete the old data
    if (!kvClient.deletes(row, column)) {
        std::cerr << "Failed to delete existing email data in KV store." << std::endl;
        return;
    }

    // Then put the updated data
    if (!kvClient.put(row, column, updatedEmailData.str())) {
        std::cerr << "Failed to update email data in KV store." << std::endl;
    }
}