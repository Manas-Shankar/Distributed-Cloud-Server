#ifndef EMAIL_SESSION_HPP
#define EMAIL_SESSION_HPP

#include <string>
#include <vector>

class EmailSession {
public:
    struct EmailAddress {
        std::string localPart;
        std::string domainPart;

        EmailAddress(std::string local, std::string domain)
            : localPart(std::move(local)), domainPart(std::move(domain)) {}
    };

    std::string sender;
    std::vector<EmailAddress> recipients;
    std::string emailData;
    bool helo = false;
    bool mail_from = false;
    bool rcpt_to = false;
    bool receivingData = false;

    EmailSession() = default;

    // Example function to add a recipient
    void addRecipient(const std::string& localPart, const std::string& domainPart) {
        recipients.emplace_back(localPart, domainPart);
    }
};

#endif // EMAIL_SESSION_HPP
