// webmailgrpc_impl.cc
#include "../include/webmailgrpc_impl.hpp"
#include <grpcpp/grpcpp.h>

WebmailServiceImpl::WebmailServiceImpl(EmailServer& serv) : server(serv) {}

Status WebmailServiceImpl::SendCommand(ServerContext* context, const CommandRequest* request, CommandResponse* response) {
    std::string sessionId = request->session_id();
    std::string command = request->command();
    std::string commandType = command.substr(0, command.find(' '));


    if(!server.sessionExists(sessionId)) {
        std::string username = "xyz";
        std::string result;
        bool loginSuccess = server.processLogin(sessionId, username, result);

        response->set_response(result);
        response->set_success(loginSuccess);
    }

    std::string result;
    bool success = server.processCommand(sessionId, command, result);
    response->set_response(result);
    response->set_success(success);



    // if (commandType != "LOGIN" && !server.sessionExists(sessionId)) {
    //     response->set_response("No valid session ID provided or session does not exist.");
    //     response->set_success(false);
    //     return Status::OK;
    // }

    // std::string result;
    // if (commandType == "LOGIN") {
    //     std::string username = command.substr(command.find(' ') + 1);
    //     bool loginSuccess = server.processLogin(sessionId, username, result);
    //     response->set_response(result);
    //     response->set_success(loginSuccess);
    // } else {
    //     bool success = server.processCommand(sessionId, command, result);
    //     response->set_response(result);
    //     response->set_success(success);
    // }
    return Status::OK;
}
