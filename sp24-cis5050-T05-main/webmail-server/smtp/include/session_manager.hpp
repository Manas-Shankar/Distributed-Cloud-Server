#ifndef SESSION_MANAGER_HPP
#define SESSION_MANAGER_HPP

#include <unordered_map>
#include <shared_mutex>
#include <string>
#include "email_session.hpp"  // Assume EmailSession is declared in this header

class SessionManager {
private:
    std::unordered_map<std::string, EmailSession> sessions;
    mutable std::shared_mutex mutex;

public:
    void createSession(const std::string& sessionId);
    EmailSession* getSession(const std::string& sessionId);
    void endSession(const std::string& sessionId);
    bool sessionExists(const std::string& sessionId) const;
};

#endif // SESSION_MANAGER_HPP
