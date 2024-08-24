#ifndef STORE_H
#define STORE_H

#include <string>
#include <vector>

using namespace std;

vector<uint8_t> stringToBytes(const string& str);

string bytesToString(const vector<uint8_t>& bytes);

void add_user(string username, string password);

bool check_user_exists(string username);

bool is_login_valid(string username, string password);

void add_session(string id);

void delete_session(string id);

bool is_session_valid(string id);

pair<string,string> getFilesAndFolders(string row);

string deleteFilesAndFolders(string row, string hashID);

pair<string, string> getFilesAndFoldersFromSubfolder(string row, string col);

string getFileFromID(string username, string fileHashID);

void uploadFile(string username, string fileHash, string fileContent);

void storeFilesFolders(string username, string hashID, string serializedValues);

void storeFilesFoldersRoot(string username, string serializedValues);

#endif
