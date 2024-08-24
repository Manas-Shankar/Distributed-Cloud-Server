#include "../include/email_session.hpp"

void EmailSession::parseMboxData() {
    std::istringstream mboxStream(mboxData);
    std::string line;
    std::streampos messageStart = 0;
    size_t messageSize = 0;
    size_t short_messageSize = 0;
    bool firstMessage = true;

    while (std::getline(mboxStream, line)) {
        if (line.rfind("From ", 0) == 0) {
            if (!firstMessage) {
                messageInfos.push_back({messageStart, messageSize, short_messageSize});
                messageSize = 0;
                short_messageSize = 0;
            }
            firstMessage = false;
            messageStart = mboxStream.tellg();
            messageStart -= static_cast<std::streampos>(line.size() + 1);
        } else {
            short_messageSize += line.size() + 1; // +1 for the newline
        }
        messageSize += line.size() + 1;
    }

    // Don't forget to add the last message
    if (messageSize > 0) {
        messageInfos.push_back({messageStart, messageSize, short_messageSize});
    }
}

// Example method to access a specific message
std::string getMessage(size_t index) {
    if (index < messageInfos.size()) {
        const auto& info = messageInfos[index];
        if (info.offset + info.size > mboxData.size()) {
            return ""; // Out of bounds check
        }
        return mboxData.substr(info.offset, info.size);
    }
    return "";
}