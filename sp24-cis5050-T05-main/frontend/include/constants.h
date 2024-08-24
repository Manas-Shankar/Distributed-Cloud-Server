#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <map>
#include <string>
#include <time.h>

const static char *CONTENT_TYPE = "Content-Type: ";
const static char *CONTENT_LEN = "Content-Length: ";
const static char *COOKIE = "Cookie: ";
const static char *SET_COOKIE = "Set-Cookie: ";
const static char *CONNECTION = "Connection: ";
const static char *OK = "200 OK";

// const static char *HOME_URI = "/";
const static char *REGISTER_URI = "/register";
const static char *LOGIN_URI = "/login";
const static char *LOGOUT_URI = "/logout";


const static char *UPLOAD_URI = "/upload";
const static char *DOWNLOAD_URI = "/download";
const static char *NEW_FOLDER_URI = "/newfolder";
const static char *RENAME_FILE_URI = "/renamefile";
const static char *DELETE_URI = "/delete";
const static char *MOVE_FILE_URI = "/movefile";

const static char *SEND_EMAIL_URI = "/sendemail";
const static char *INBOX_URI = "/inbox";
const static char *VIEW_EMAIL_URI = "/viewemail";
const static char *FORWARD_EMAIL_URI = "/forwardemail";
const static char *REPLY_EMAIL_URI = "/replytoemail";
const static char *DELETE_EMAIL_URI = "/deleteemail";

const static char *REPLY_EMAIL_SUCCESS_URI = "/reply-email-success";
const static char *FORWARD_EMAIL_SUCCESS_URI = "/forward-email-success";


const static char *ADMIN_URI = "/admin-console";

using namespace std;

// static map<string, string> users; // key: username; value:password
// store session id and its creation time, session id same as username
static map<string, time_t> sessions;


using namespace std;

#endif
