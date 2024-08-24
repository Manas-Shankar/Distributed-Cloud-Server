#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include <mutex>
#include <string>
#include <atomic>

#include "session_manager.hpp"  // This includes the declaration of SessionManager
#include "email_session.hpp"  // This includes the declaration of EmailSession

class EmailServer {
private:
    int port;
    bool verbose;
    std::string mailboxDir;
    // std::atomic<bool> running;
    // std::vector<int> activeConnections;  // Assuming this is used for connection tracking
    // std::mutex connectionsMutex;
    SessionManager sessionManager;

public:
    // Constructor
    EmailServer(int port, bool verbose, const std::string& mailboxDir);

    // Process a command received from a client
    bool processCommand(const std::string& sessionId, const std::string& command, std::string& response);

    // Reset the session to a clean state
    void resetSession(EmailSession& session);

    // Cleanup resources and handle server shutdown
    // void cleanup();

    // Signal handler for graceful shutdown
    static void handleSigInt(int sig);

    bool sessionExists(const std::string& sessionId) const {
        return sessionManager.sessionExists(sessionId);
    }

    bool processLogin(const std::string& sessionId, const std::string& username, std::string& result);
    // Method to handle the actual storage of email data into a mailbox
    // void appendEmailToMbox(const std::string& emailData, const std::string& sender, const std::vector<std::string>& recipients);

    void sendToKV(const std::string& emailData, const std::string& sender, const std::vector<std::string>& recipients);

   // Handle POP3 commands
    std::string handlePOP3Commands(EmailSession& session, const std::string& command);

    // Command handling methods for POP3
    std::string handleUSERCommand(EmailSession& session, const std::string& username);
    std::string handlePASSCommand(EmailSession& session, const std::string& password);
    std::string handleSTATCommand(EmailSession& session);
    std::string handleLISTNoArg(EmailSession& session);
    std::string handleLIST(EmailSession& session, const std::string& command);
    std::string handleRETRCommand(EmailSession& session, const std::string& command);
    std::string handleDELECommand(EmailSession& session, const std::string& command);
    std::string handleUIDLCommand(EmailSession& session, const std::string& command);
    std::string handleUIDLNoArg(EmailSession& session);
    std::string handleRSET(EmailSession& session);
    std::string handleQUIT(EmailSession& session);

    std::string readMessage(EmailSession& session, int index);
    void readAndParseMessages(EmailSession& session);
    void initializeSession(EmailSession& session, const std::string& username);
    void deleteMessages(EmailSession& session);



};

#endif // SERVER_HPP
