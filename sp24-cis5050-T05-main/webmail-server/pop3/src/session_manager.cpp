#include "../include/session_manager.hpp"
#include "../include/email_session.hpp"

void SessionManager::createSession(const std::string& sessionId) {
    std::unique_lock<std::shared_mutex> lock(mutex);
    sessions[sessionId] = EmailSession();
    sessions[sessionId].session_id = sessionId;
}

// Retrieve a session by its ID
EmailSession* SessionManager::getSession(const std::string& sessionId) {
    std::shared_lock<std::shared_mutex> lock(mutex);
    auto it = sessions.find(sessionId);
    if (it != sessions.end()) {
        return &it->second;
    }
    return nullptr;
}

// End a session
void SessionManager::endSession(const std::string& sessionId) {
    std::unique_lock<std::shared_mutex> lock(mutex);
    sessions.erase(sessionId);
}

bool SessionManager::sessionExists(const std::string& sessionId) const {
    std::shared_lock<std::shared_mutex> lock(mutex);
    return sessions.find(sessionId) != sessions.end();
}



// // session_manager.cpp
// #include "session_manager.hpp"

// void SessionManager::createSession(const std::string& sessionId) {
//     std::lock_guard<std::mutex> lock(mutex);
//     sessions[sessionId] = EmailSession();
// }

// EmailSession* SessionManager::getSession(const std::string& sessionId) {
//     std::lock_guard<std::mutex> lock(mutex);
//     auto it = sessions.find(sessionId);
//     if (it != sessions.end()) {
//         return &it->second;
//     }
//     return nullptr;
// }

// void SessionManager::endSession(const std::string& sessionId) {
//     std::lock_guard<std::mutex> lock(mutex);
//     sessions.erase(sessionId);
// }
