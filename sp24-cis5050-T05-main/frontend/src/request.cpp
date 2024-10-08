#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sstream>
#include <vector>
#include<iostream>

#include "../include/constants.h"
#include "../include/utils.h"
#include "../include/request.h"

using namespace std;


/*read and parse one request*/
Request::Request(int fd) {
  string line = read_line(fd);
  int content_length = -1;

  // sanity check
  if (line.empty()) {
    valid = false;
    debug(1, "Initial line is empty\n");
    return;
  }

  // initial line
  
  string initial_line = line;
  // cout << "line::   " << line << endl;
  vector<string> initial_line_tokens = split(initial_line, ' ');
  if (initial_line_tokens.size() != 3) {
    debug(1, "Initial line token numbers != 3\n");
    valid = false;
    return;
  }

  // method, path, http_version
  this->method = initial_line_tokens.at(0);
  this->path = initial_line_tokens.at(1); // the path contains query string
  this->http_version = initial_line_tokens.at(2);
  debug(1, "[Method]: ");
  debug(1, (this->method).c_str());
  debug(1, "\r\n[Path]: ");
  debug(1, (this->path).c_str());
  debug(1, "\r\n[Http version]: ");
  debug(1, (this->http_version).c_str());
  debug(1, "\r\n");

  while (!line.empty()) {
    debug(1, line.c_str());
    debug(1, "\r\n");

    // cookies
    if (line.length() >= 8 && line.substr(0, 8) == COOKIE) {
      vector<string> cookie_tokens = split(line.substr(8).c_str(), ';');
      for (vector<string>::iterator it = cookie_tokens.begin();
           it != cookie_tokens.end(); ++it) {
        vector<string> cookie_pair = split((*it).c_str(), '=');
        if (cookie_pair.size() == 2) {
          (this->cookies)[cookie_pair.at(0)] = cookie_pair.at(1);
          debug(1, "[Cookie]: ");
          debug(1, cookie_pair.at(0).c_str());
          debug(1, "=");
          debug(1, cookie_pair.at(1).c_str());
          debug(1, "\r\n");
        }
      }
    }

    // content-length
    if (line.length() >= 16 && line.substr(0, 16) == CONTENT_LEN) {
      this->content_length = atoi(line.substr(16).c_str());
    }

    // read next line
    line = read_line(fd);
  }

  // POST message body
  if (this->method == "POST" && this->content_length > 0) {
    char* buf = (char*) malloc(sizeof(char) * (this->content_length + 1));
    do_read(fd, buf, this->content_length);
    buf[this->content_length] = '\0';
    for (int i = 0; i < this->content_length; i++) {
      this->body += buf[i];
    }

    cout << "end of body" << endl;
    free(buf);
  }

  valid = true;
}