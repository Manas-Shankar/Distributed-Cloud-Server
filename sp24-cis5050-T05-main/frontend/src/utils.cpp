#include <ctime>
#include <dirent.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdarg.h>
#include <stdio.h>
#include <streambuf>
#include <string>
#include <unistd.h>
#include <vector>
#include <cstring>

#include "../include/utils.h"

using namespace std;

/* wrapper function for fprintf, which takes in variable arguments and prints if
 * debug is enabled*/
void debug(int vflag, const char *format, ...) {
  if (!vflag)
    return;
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
}

/* read len from fd to buffer*/
int do_read(int fd, char *buf, int len) {
  int rcvd = 0;
  while (rcvd < len) {
    int n = read(fd, &buf[rcvd], len - rcvd);
    if (n <= 0) {
      return rcvd;
    }
    rcvd += n;
  }
  return rcvd;
}

/* write buffer with len into fd*/
int do_write(int fd, char *buf, int len) {
  int sent = 0;
  while (sent < len) {
    int n = write(fd, &buf[sent], len - sent);
    if (n < 0) {
      return 0;
    }
    sent += n;
  }
  return 1;
}

/* read a line from a fd, till \r\n , \n or end of file*/
string read_line(int fd) {
  string line;
  char c;

read:
  do {
    if (do_read(fd, &c, sizeof(c)) <= 0) {
      return line;
    }
    line += c;
  } while (c != '\r' && c != '\n');

  if (c == '\r') {
    if (do_read(fd, &c, sizeof(c)) <= 0) {
      return line;
    }
    if (c == '\n') { //'\r\n' end of the message
      line += c;
    } else { //'\r' not followed with '\n', read again
      goto read;
    }
  } else if (c == '\n') { // only ends with '\n'
    line = line.substr(0, line.length() - 1);
    line += '\r';
    line += '\n';
  }
  line = line.substr(0, line.length() - 2);
  return line;
}

/* read a line from a fd, till \r\n or end of file*/
string read_rep_line(int fd) {
  string line;
  char c;

read:
  do {
    if (do_read(fd, &c, sizeof(c)) <= 0) {
      return line;
    }
    line += c;
  } while (c != '\r');

  if (do_read(fd, &c, sizeof(c)) <= 0) {
    return line;
  }
  if (c == '\n') { //'\r\n' end of the message
    line += c;
  } else { //'\r' not followed with '\n', read again
    goto read;
  }

  line = line.substr(0, line.length() - 2);
  return line;
}

/* split a string by delimiter */
vector<string> split(const string &s, char delim) {
  vector<string> elems;
  stringstream ss;
  ss.str(s);
  string item;
  while (getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

/* extract uploaded file content from request body */
string extract_file_content(string req_body, int content_length) {
  cout << "content length:" << content_length << endl;

  // cout << req_body << endl;
  req_body = req_body.substr(req_body.find("\r\n\r\n") + 4);
  // cout << "parsed body of file:" << req_body;
  string sub = req_body.substr(0, req_body.find("------WebKit") - 2);
  // cout << req_body.substr(req_body.size()-50, content_length);
  return sub;
  // return req_body.substr(0, content_length);
}

/* extract uploaded file name from request body */
string extract_file_name(string req_body) {
  req_body = req_body.substr(req_body.find("filename=\"") + 10);
  return req_body.substr(0, req_body.find("\""));
}

/* create and store uploaded files */
void store_file(string dir, string filename, string file_content) {
  debug(1, (dir + filename).c_str());
  ofstream outfile(dir + filename);
  outfile << file_content;
  outfile.close();
}

/* list all files under a directory */
vector<string> list_all_files(string dir) {
  vector<string> filesAndFolders;
  stringstream ss(dir);
    string item;
    while (std::getline(ss, item, ',')) {
        filesAndFolders.push_back(item);
    }

    return filesAndFolders;
}

/* check if a given file exists */
bool is_file_exist(const char *filename) {
  ifstream infile(filename);
  return infile.good();
}

/* get file content as string from file name */
string get_file_content_as_string(const char *filename) {
  ifstream t(filename);
  string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
  return str;
}

/* replace all substring in a string */
void replace_all(string &str, const string &from, const string &to) {
  if (from.empty()) {
    return;
  }

  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }
}

/* get file size */
int file_size(const char *filename) {
  ifstream in(filename, ifstream::ate | ifstream::binary);
  return in.tellg();
}

/* get current time */
string get_current_time() {
  time_t t = time(nullptr);
  ostringstream curr_time;
  curr_time << put_time(localtime(&t), "%c %Z");
  return curr_time.str();
}

/* url decode */
string url_decode(string &str) {
  string ret;
  char ch;
  int i, ii;
  for (i = 0; i < str.length(); i++) {
    if (int(str[i]) == 37) {
      sscanf(str.substr(i + 1, 2).c_str(), "%x", &ii);
      ch = static_cast<char>(ii);
      ret += ch;
      i = i + 2;
    } else {
      ret += str[i];
    }
  }
  return (ret);
}

/* extract the substring after +OK */
string extractSubstring(std::string& str) {
  
    // Find the position of the delimiter string
    size_t delimiterPos = str.find("+OK message follows\r\n");
    
    if (delimiterPos != std::string::npos) {
        // Extract the substring starting from the position after the delimiter
        std::string extractedContent = str.substr(delimiterPos + strlen("+OK message follows\r\n"));
        
        // return the extracted content
        return extractedContent;
    } else {
        return "Message not received";
    }
}

/* parse the email received */
std::vector<std::string> parseEmailDetails(std::string& emailMessage) {
    std::vector<std::string> details(3); // Vector to hold "From", "Subject", and "Date"
    size_t startPos, endPos;

    // Extract "From" field
    startPos = emailMessage.find("From:");
    if (startPos != std::string::npos) {
        startPos += 7; // Move past "From: "
        endPos = emailMessage.find("\r\n", startPos) - 1;
        details[0] = emailMessage.substr(startPos, endPos - startPos); // Store "From"
    }

    // Extract "Subject" field
    startPos = emailMessage.find("Subject:");
    if (startPos != std::string::npos) {
        startPos += 9; // Move past "Subject: "
        endPos = emailMessage.find("\r\n", startPos);
        details[1] = emailMessage.substr(startPos, endPos - startPos); // Store "Subject"
    }

    // Extract "Date" field
    startPos = emailMessage.find("Date:");
    if (startPos != std::string::npos) {
        startPos += 6; // Move past "Date: "
        endPos = emailMessage.find("\r\n", startPos);
        details[2] = emailMessage.substr(startPos, endPos - startPos); // Store "Date"
    }

    return details;
}

/* parse to extract the actual email content */
std::string extractContentAfterSubject(std::string& message) {
    // Find the start of the subject line
    size_t subjectPos = message.find("Subject:");
    if (subjectPos == std::string::npos) {
        return "Subject not found.";  // Subject keyword not found
    }

    // Find the first occurrence of "\r\n" after "Subject:"
    size_t startOfContent = message.find("\r\n", subjectPos);
    if (startOfContent == std::string::npos) {
        return "Newline after subject not found.";  // Newline not found
    }

    startOfContent += 2;  // "\r\n" is two characters

    // Extract and return the substring from this point to the end of the string
    return message.substr(startOfContent);
}

/* to retrive the email to be deleted/forwarded/replied to */
std::string getValue(std::string& text,std::string startDelimiter,std::string endDelimiter) {
    size_t startPos = text.find(startDelimiter);
    if (startPos == std::string::npos) return "";
    startPos += startDelimiter.length();
    size_t endPos = text.find(endDelimiter, startPos);
    if (endPos == std::string::npos) return "";
    return text.substr(startPos, endPos - startPos);
}
