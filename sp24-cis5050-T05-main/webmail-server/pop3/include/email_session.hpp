#ifndef EMAIL_SESSION_HPP
#define EMAIL_SESSION_HPP

#include <vector>
#include <string>
#include <iostream>

// Define a structure to hold message details
struct MessageInfo {
    std::streampos offset;  // Offset where the message starts in the mbox data
    size_t size;            // Total size of the message
    size_t short_size;      // Size of the message minus the "From " line
};

class EmailSession {
public:
    std::string session_id;
    std::string currentUsername;
    std::string sender;
    std::vector<std::string> recipients;
    std::string emailData;
    // std::string mboxData;  // Holds the entire mbox content if loaded into memory
    std::vector<MessageInfo> messageInfos; // Stores offset and size of each message
    std::vector<bool> deletedMessages;
    bool helo = false;
    bool mail_from = false;
    bool rcpt_to = false;
    bool isAuthenticated = false;
    bool receivingData = false;

    EmailSession() = default;

    // Method to parse mboxData and populate messageInfos
    

    // Additional methods as needed for command processing, etc.
};
#endif // EMAIL_SESSION_HPP
