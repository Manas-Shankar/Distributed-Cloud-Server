// #include <winsock2.h>
#include<arpa/inet.h>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include <pthread.h>
#include <grpcpp/grpcpp.h>
#include <functional>

#include "../include/constants.h"
#include "../include/request.h"
#include "../include/response.h"
#include "../include/store.h"
#include "../include/utils.h"

//Email service handlers
#include "../include/pop3_commands.h"
#include "../include/smtp_commands.h"

//admin console
#include "../include/adminconsole.h"

using namespace std;

// username
string user_name;
string curr_user;
map <string,string> uidl;
string curEmail;
string curUIDL;

Response::Response(Request req) {

  this->http_version = req.http_version;
  (this->headers)[CONNECTION] = "close";

  cout << "LATEST REQUEST " << req.path << endl;

  //admin console
  if (req.path == ADMIN_URI) {
    cout << "ADMIN " << req.path << endl;
    admin_console(req);
    return;

  // register
  } else if (req.path == REGISTER_URI) {
    login(req);
  }

  if (req.path == REGISTER_URI) {
    reg(req);
  }

  // login
  else if (req.path == LOGIN_URI) {
    login(req);
  }

    // user not login
  else if (!is_already_login(req.cookies, user_name)) {
    login(req);
  }

  /*
   * FOLDER URI PARSING
   *
   * */

  // upload
    else if (req.path == UPLOAD_URI) {
      if (req.method == "GET") {
        upload(req);
      } else if (req.method == "POST") {
        handle_upload(req);
      }
    }

    // download file
    else if (req.path.length() >= 10 && req.path.substr(0, 10) == "/download?") {
      download_file(req);
    }

    // download from subfolder
    else if (req.path.length() >= 10 && req.path.substr(0, 10) == "/download/") {
      download_subfolder(req);
    }

    // download from root
    else if (req.path.length() >= 9 && req.path.substr(0, 9) == DOWNLOAD_URI) {
      download(req);
    }

    // create new folder
    else if (req.path == NEW_FOLDER_URI) {
      create_new_folder(req);
    }

    // rename file
    else if (req.path == RENAME_FILE_URI) {
      rename_file(req);
    }

    // delete file
    else if (req.path == DELETE_URI) {
      delete_file(req);
    }

    // move file
    else if (req.path == MOVE_FILE_URI) {
      move_file(req);
    }



  /*
   * EMAIL URI PARSING
   *
   */

  // inbox
      else if (req.path == INBOX_URI) {
        inbox(req);
   }

   // view email
  else if (req.path.length() >= 10 &&
           req.path.substr(0, 10) == VIEW_EMAIL_URI) {
    view_email(req);
  }

  // send email
    else if (req.path == SEND_EMAIL_URI) {
      if (req.method == "GET") {
        send_email(req);
      } else if (req.method == "POST") {

        cout << "SEND EMAIL POST " << endl;

        handle_send_email(req);
      }

    }  


    // forward email
    else if (req.path.length() >= 13 && req.path.substr(0, 13) == FORWARD_EMAIL_URI) {
      
       forward_email(req);
    } 

    else if (req.path.length() >= 22 && req.path.substr(0, 22) == FORWARD_EMAIL_SUCCESS_URI) {
      forward_email_success(req);
    }
    

    // reply email
    else if (req.path.length() >= 13 && req.path.substr(0, 13) == REPLY_EMAIL_URI) {
      
       reply_email(req);
    } 

    else if (req.path.length() >= 20 && req.path.substr(0, 20) == REPLY_EMAIL_SUCCESS_URI) {
      reply_email_success(req);
    }
    
  

    // delete email
    else if (req.path.length() >= 12 && req.path.substr(0, 12) == DELETE_EMAIL_URI) {
      delete_email(req);
    }

    // logout
    else if (req.path == LOGOUT_URI) {
     delete_session(user_name);
      login(req);

    //admin console
    } else {

    login(req);
  }
}

void Response::reply(int fd) {
  string rep;
  rep += http_version + " " + status + "\r\n";

  for (map<string, string>::iterator it = headers.begin(); it != headers.end();
       ++it) {
    rep += it->first + it->second + "\r\n";
  }
  rep += "\r\n";
  // rep += this->body;

  char crep[rep.length() + 1];
  strcpy(crep, rep.c_str());

  // send header
  debug(1, "[%d] S: %s", fd, crep);
  do_write(fd, crep, strlen(crep));

  // send body
  for (int i = 0; i < (this->body).length(); i++) {
    do_write(fd, &(this->body).at(i), 1);
  }
}

void Response::reg(Request req) {
  this->status = OK;
  (this->headers)[CONTENT_TYPE] = "text/html";

  // GET
  if (req.method.compare("GET") == 0) {
    this->body = get_file_content_as_string("html/register.html");
    (this->headers)[CONTENT_LEN] = to_string((this->body).length());
  }

  // POST
  else if (req.method.compare("POST") == 0) {
    vector<string> params = split(req.body.c_str(), '&');
    string username = split(params.at(0), '=').at(1);
    string password = split(params.at(1), '=').at(1);

    curr_user = username;

     if (check_user_exists(username)) {
       this->body = get_file_content_as_string("html/user-already-exist.html");
       (this->headers)[CONTENT_LEN] = to_string((this->body).length());
     } else { // new user
    add_user(username, password);
    this->body = get_file_content_as_string("html/new-user.html");
    (this->headers)[CONTENT_LEN] = to_string((this->body).length());
     }
  }
}

/* login */
void Response::login(Request req) {

  string username;
  bool already_login = is_already_login(req.cookies, username);
  // bool already_login = false;

  cout << "Setting headers " << endl;
  this->status = OK;
  (this->headers)[CONTENT_TYPE] = "text/html";

  // GET 
  if (req.method.compare("GET") == 0 && !already_login) {

    this->body = get_file_content_as_string("html/login.html");
    (this->headers)[CONTENT_LEN] = to_string((this->body).length());

  }

  // POST
  else if (req.method.compare("POST") == 0) {
    vector<string> params = split(req.body.c_str(), '&');
    username = split(params.at(0), '=').at(1);
    string password = split(params.at(1), '=').at(1);

     if (is_login_valid(username, password)) {
      add_session(username);
       already_login = true;
     } else {
       this->body = get_file_content_as_string("html/login-failed.html");
       (this->headers)[CONTENT_LEN] = to_string((this->body).length());
     }
  }

   if (already_login) {
     this->body = get_file_content_as_string("html/user-home.html");
     replace_all(this->body, "$username", username);
     (this->headers)[CONTENT_LEN] = to_string((this->body).length());
     (this->headers)[SET_COOKIE] = "sessionid=" + username;
     curr_user = username;
     std::cout << "curr user:" << curr_user << endl;
   }

}


/* session checking */
bool Response::is_already_login(map<string, string> cookies, string &username) {
  if (cookies.count("sessionid") == 1) {
    if (is_session_valid(cookies["sessionid"])) {
      username = cookies["sessionid"];
      return true;
    }
  }
  return false;
}

/*
 *
 * FILE RELATED RESPONSES
 *
 */

/* file upload */
void Response::upload(Request req) {
  this->status = OK;
  (this->headers)[CONTENT_TYPE] = "text/html";
  this->body = get_file_content_as_string("html/upload.html");
  (this->headers)[CONTENT_LEN] = to_string((this->body).length());
}

bool isFile(const string& name) {
    // Check if the name has at least 2 characters (for the extension)
    if (name.size() < 2) {
        return false;
    }

    // Find the last occurrence of "."
    size_t dotPos = name.find_last_of('.');

    // Check if "." exists and is followed by at least 4 characters (for the extension)
    return (dotPos != string::npos) && (name.size() - dotPos > 3);
}

void saveToFile(const string& fileContent, const string& filePath) {
    ofstream fileStream(filePath, ios::binary);
    if (!fileStream.is_open()) {
        cerr << "Failed to open file for writing: " << filePath << endl;
        return;
    }

    std::cout << "filecontent size for video file:" << fileContent.size() << endl;

    const int bufferSize = 8192; // 8 KB buffer size
    for (size_t i = 0; i < fileContent.size(); i += static_cast<size_t>(bufferSize)) {
        fileStream.write(fileContent.c_str() + i, std::min(static_cast<size_t>(bufferSize), fileContent.size() - i));
    }

    fileStream.close();

    if (!fileStream.good()) {
        std::cerr << "Error occurred while writing file: " << filePath << std::endl;
        return;
    }
}

/* handle file upload */
void Response::handle_upload(Request req) {
  std::cout << "inside handle upload" << endl;
  this->status = OK;
  (this->headers)[CONTENT_TYPE] = "text/html";
  string filename(extract_file_name(req.body));
  string file_content(extract_file_content(req.body, req.content_length));

  std::cout << "extracted file content size:" << file_content.size() << endl;
  // store_file(dir, filename, file_content);

  // send to KV store
  std::cout << "::::::::: curr_user :::::::::::" << curr_user << endl;
  hash<string> hasher;
  size_t fileHash = hasher(filename);

  std::cout << ":::::::::::File hash:::::::::::::" << fileHash << endl;

  pair<string, string> response = getFilesAndFolders(curr_user);
  string filesAndFolders = response.first;
  string errorMessage = response.second;
  string notFoundMessage = "Key not found or Get";
	bool notFound = errorMessage.find(notFoundMessage) != string::npos;

  if(notFound)
  {
    unordered_map<string, size_t> FileFolderHashes;
    FileFolderHashes[filename] = fileHash;

    stringstream ss;
    for (const auto& pair : FileFolderHashes) {
        ss << pair.first << ":" << pair.second << ",";
    }

    string serializedHashes = ss.str();
    std::cout << "::::::::::Serialized Hash Values::::::::::" << serializedHashes << endl;
    storeFilesFoldersRoot(curr_user, serializedHashes);
  }
  else
  {
    unordered_map<string, size_t> FileFolderHashes;

    // Create a string stream to parse the serialized string
    stringstream ss(filesAndFolders);
    string pair;

    while (getline(ss, pair, ',')) {
        stringstream pairStream(pair);
        string oldFileFolderName;
        size_t oldHashValue;

        // Extract folder name and hash value from the pair
        getline(pairStream, oldFileFolderName, ':');
        pairStream >> oldHashValue;

        // Insert folder name and hash value into the map
        FileFolderHashes[oldFileFolderName] = oldHashValue;
    }

    for (const auto& pair : FileFolderHashes) {
      string name = pair.first;
        if(isFile(name))
          std::cout << "File: " << pair.first << ", Hash: " << pair.second << endl;
        else 
          std::cout << "Folder: " << pair.first << ", Hash: " << pair.second << endl;
    }

    FileFolderHashes[filename] = fileHash;

    // serialize everything again
    stringstream ssN;
    for (const auto& pair : FileFolderHashes) {
        ssN << pair.first << ":" << pair.second << ",";
    }

    string serializedHashes = ssN.str();
    std::cout << "::::::::::Serialized Hash Values::::::::::" << serializedHashes << endl;

    storeFilesFoldersRoot(curr_user, serializedHashes);
  }

  string fileHashID = to_string(fileHash);
  uploadFile(curr_user, fileHashID, file_content);

  this->body = get_file_content_as_string("html/upload.html");
  (this->headers)[CONTENT_LEN] = to_string((this->body).length());
}

/* download file */
void Response::download_file(Request req) {
  // cout << "Inside download file call handler " << endl;
  string file_name_and_hash = req.path.substr(10);
  // cout <<  "file to be downloaded: " << file_name_and_hash << endl;

  size_t slashPos = file_name_and_hash.find('/');
  string fileName = file_name_and_hash.substr(0, slashPos); // Start from position 9 to skip "download?"
  std::cout << "File Name: " << fileName << endl;

  std::string hashCode = file_name_and_hash.substr(slashPos + 1);
  std::cout << "Hash Code: " << hashCode << endl;

  string fileContent = getFileFromID(curr_user, hashCode);
  this->status = OK;
  if(fileContent.size() > 0)
  {
    saveToFile(fileContent, fileName);
    this->body = get_file_content_as_string("html/download_file_success.html");
    replace_all(this->body, "$filename", fileName);
    (this->headers)[CONTENT_LEN] = to_string((this->body).length());
  }
  else
  {
    this->body = get_file_content_as_string("html/download_file_failed.html");
    replace_all(this->body, "$filename", fileName);
    (this->headers)[CONTENT_LEN] = to_string((this->body).length());
  }
}


/* download all uploaded files and subfolders within subfolder*/
void Response::download_subfolder(Request req) {
  this->status = OK;
  (this->headers)[CONTENT_TYPE] = "text/html";

  string folder_hash_and_name = req.path.substr(10);
  size_t slashPos = folder_hash_and_name.find('/');
  string folderHash = folder_hash_and_name.substr(0, slashPos); // Start from position 9 to skip "download?"
  std::cout << "Folder Hash: " << folderHash << endl;

  string folderName = folder_hash_and_name.substr(slashPos + 1);
  std::cout << "Folder name: " << folderName << endl;

  // get file/folder hashes from KV store for this subfolder using its hash
  pair<string, string> response = getFilesAndFoldersFromSubfolder(curr_user, folderHash);
  string filesAndFolders = response.first;
  string errorMessage = response.second;
  string notFoundMessage = "Key not found or Get operation";
	bool notFound = errorMessage.find(notFoundMessage) != string::npos;

  if(notFound)
  {
    this->body = get_file_content_as_string("html/download_subfolder.html");
    replace_all(this->body, "$allDownloadFiles", "No Files/Folders have been created yet within this directory !");
    (this->headers)[CONTENT_LEN] = to_string((this->body).length());
  }
  else
  {
    vector<string> files(list_all_files(filesAndFolders));
    stringstream ss_file;
    stringstream ss_folder;

      for (const auto& file : files) {
          size_t colonPos = file.find(':');
          if (colonPos != std::string::npos) {
              string name = file.substr(0, colonPos);
              string hash = file.substr(colonPos + 1);
              if (isFile(name)) {
                  ss_file << "<a class=\"list-group-item\" href=\"/download?" << name << "/" << hash << "\">" << name << "</a>";
                } else {
                  ss_folder <<  "<a class=\"list-group-item\" href=\"/download/" << hash << "/" << name << "\">" << name << "</a>";
                }
          }
      }

      this->body = get_file_content_as_string("html/download.html");
      string all_download_files = ss_file.str();
      string all_folders = ss_folder.str();
      replace_all(this->body, "$allDownloadFiles", all_download_files);
      replace_all(this->body, "$allFolders", all_folders);
      (this->headers)[CONTENT_LEN] = to_string((this->body).length());
  }
}


/* download all uploaded files and folders at root */
void Response::download(Request req) {
  this->status = OK;
  (this->headers)[CONTENT_TYPE] = "text/html";
  string dir(curr_user);
  // string curr_folder(req.path.substr(9));

  // get file/folder hashes from KV store
  pair<string, string> response = getFilesAndFolders(curr_user);
  string filesAndFolders = response.first;
  string errorMessage = response.second;
  string notFoundMessage = "Key not found or Get";
	bool notFound = errorMessage.find(notFoundMessage) != string::npos;

  // vector<string> lines = send_to_backend(message, user_name);
  if(notFound)
  {
    this->body = get_file_content_as_string("html/download-subfolder.html");
    replace_all(this->body, "$allDownloadFiles", "No Files/Folders have been created yet !");
    (this->headers)[CONTENT_LEN] = to_string((this->body).length());
  }
  else
  {
    vector<string> files(list_all_files(filesAndFolders));
    stringstream ss_file;
    stringstream ss_folder;

    
      for (const auto& file : files) {
          size_t colonPos = file.find(':');
          if (colonPos != std::string::npos) {
              string name = file.substr(0, colonPos);
              string hash = file.substr(colonPos + 1);
              if (isFile(name)) {
                  ss_file << "<a class=\"list-group-item\" href=\"/download?" << name << "/" << hash << "\">" << name << "</a>";
                } else {
                  ss_folder <<  "<a class=\"list-group-item\" href=\"/download/" << hash << "/" << name << "\">" << name << "</a>";
                }
          }
      }

      this->body = get_file_content_as_string("html/download.html");
      string all_download_files = ss_file.str();
      string all_folders = ss_folder.str();
      replace_all(this->body, "$allDownloadFiles", all_download_files);
      replace_all(this->body, "$allFolders", all_folders);
      (this->headers)[CONTENT_LEN] = to_string((this->body).length());
  }

}


/* create new folder */
void Response::create_new_folder(Request req) {
  this->status = OK;
  (this->headers)[CONTENT_TYPE] = "text/html";
  string foldername = req.body.substr(req.body.find('=') + 1);
  string dir(curr_user);
  std::cout << "::::::::: curr_user :::::::::::" << curr_user << endl;
  hash<string> hasher;
  size_t folderHash = hasher(foldername);

  std::cout << ":::::::::::hash:::::::::::::" << folderHash << endl;

  pair<string, string> response = getFilesAndFolders(curr_user);
  string filesAndFolders = response.first;
  string errorMessage = response.second;
  string notFoundMessage = "Key not found or Get";
	bool notFound = errorMessage.find(notFoundMessage) != string::npos;

  if(notFound)
  {
    unordered_map<string, size_t> folderHashes;
    folderHashes[foldername] = folderHash;

    stringstream ss;
    for (const auto& pair : folderHashes) {
        ss << pair.first << ":" << pair.second << ",";
    }

    string serializedHashes = ss.str();
    std::cout << "::::::::::Serialized Hash Values::::::::::" << serializedHashes << endl;
    storeFilesFoldersRoot(curr_user, serializedHashes);
  }
  else
  {
    unordered_map<string, size_t> folderHashes;

    // Create a string stream to parse the serialized string
    stringstream ss(filesAndFolders);
    string pair;

    while (getline(ss, pair, ',')) {
        stringstream pairStream(pair);
        string oldFolderName;
        size_t oldHashValue;

        // Extract folder name and hash value from the pair
        getline(pairStream, oldFolderName, ':');
        pairStream >> oldHashValue;

        // Insert folder name and hash value into the map
        folderHashes[oldFolderName] = oldHashValue;
    }

    for (const auto& pair : folderHashes) {
        string name = pair.first;
        if(isFile(name))
          std::cout << "File: " << pair.first << ", Hash: " << pair.second << endl;
        else 
          std::cout << "Folder: " << pair.first << ", Hash: " << pair.second << endl;
    }

    folderHashes[foldername] = folderHash;
    // serialize everything again
    stringstream ssN;
    for (const auto& pair : folderHashes) {
        ssN << pair.first << ":" << pair.second << ",";
    }

    string serializedHashes = ssN.str();
    std::cout << "::::::::::Serialized Hash Values::::::::::" << serializedHashes << endl;

    storeFilesFoldersRoot(curr_user, serializedHashes);
  }

  this->body =
      get_file_content_as_string("html/new-folder-created.html");
  replace_all(this->body, "$foldername", foldername);
  (this->headers)[CONTENT_LEN] = to_string((this->body).length());
}


/* move file */
void Response::move_file(Request req) {
  this->status = OK;
  (this->headers)[CONTENT_TYPE] = "text/html";
  vector<string> tokens = split(req.body.c_str(), '&');
  string fileFoldername = tokens.at(0).substr(tokens.at(0).find('=') + 1);
  string oldfolder = tokens.at(1).substr(tokens.at(1).find('=') + 1);
  string newfolder = tokens.at(2).substr(tokens.at(2).find('=') + 1);

  std::cout << "file name:" << fileFoldername << endl;
  std::cout << "src name:" << oldfolder << endl;
  std::cout << "dest name:" << newfolder << endl;

  // string dir(curr_user);
  if(fileFoldername.length() == 0 || newfolder.length() == 0)
  {
    this->body = get_file_content_as_string("html/move_failed.html");
    (this->headers)[CONTENT_LEN] = to_string((this->body).length());
    return;
  }
  // handle case for folder move 
  else
  {
    // old folder is empty, meaning move is from root
    if(oldfolder.length() == 0)
    {
      // search for all 3 to obtain their hashes
      size_t fileFolderHash = 0;
      size_t sourceHash = 1; // 1 to indicate that source is root
      size_t destHash = 0;

      vector<string> searchFolders;
      searchFolders.push_back(curr_user);
      while(!searchFolders.empty())
      {
        cout << " ::::::::: new iteration for file/folder search::::::::" << endl;
        pair<string, string> response;
        string currFolder = searchFolders.front();

        if(searchFolders.size() > 0)
          searchFolders.erase(searchFolders.begin());
        
        if(currFolder == curr_user)
          response = getFilesAndFolders(currFolder);
        else
          response = getFilesAndFoldersFromSubfolder(curr_user, currFolder);
        
        string filesAndFolders = response.first;
        string errorMessage = response.second;
        string notFoundMessage = "Key not found or Get";
	      bool notFound = errorMessage.find(notFoundMessage) != string::npos;

        // current folder is empty, continue to next folder
        if(notFound)
          continue;
        else {
          
          // go through all the files and folders in the current folder looking for a match
          unordered_map<string, size_t> folderHashes;
          stringstream ss(filesAndFolders);
          string pair;

          // map all files and folders to a map
          while (getline(ss, pair, ',')) {
            stringstream pairStream(pair);
            string oldFolderName;
            size_t oldHashValue;

              // Extract folder name and hash value from the pair
            getline(pairStream, oldFolderName, ':');
            pairStream >> oldHashValue;

              // Insert folder name and hash value into the map
            folderHashes[oldFolderName] = oldHashValue;
          }

          bool foundFile = false;
          // for each pair of file/folder name and its hash, try to find a match
          for (const auto& pair : folderHashes) {
            string name = pair.first;
            if(isFile(name))
            {
              std::cout << "Looking at File: " << pair.first << ", Hash: " << pair.second << endl;
              if(pair.first == fileFoldername)
              {
                // found the hash of the file to be moved !
                foundFile = true;
                fileFolderHash = pair.second;
                break;
              }
              else
                continue;  // continue to search in other entries
            }
            else
            {  // this is a folder
              std::cout << "Looking at Folder: " << pair.first << ", Hash: " << pair.second << endl;
              if(pair.first == fileFoldername)
              {
                //found the hash of the folder to be moved !
                foundFile = true;
                fileFolderHash = pair.second;
                break;
              }
              else
              {
                // the requested file/folder could be within this folder, so we add it's hash to the vector for future examination
                 searchFolders.push_back(to_string(pair.second));
              }
            }
          }

          // if the file was found, then we exit out
          if(foundFile)
            break;
        }
      }

      // file was not found anywhere
      if(fileFolderHash == 0)
      {
          this->body = get_file_content_as_string("html/move_not_possible.html");
          (this->headers)[CONTENT_LEN] = to_string((this->body).length());
          return;
      }
      else
        std::cout << "found file " << fileFoldername << " with hash " << fileFolderHash << endl; 

      // now, we find the destination folder's hash
      searchFolders.clear();
      searchFolders.push_back(curr_user); // start searching in root
      while(!searchFolders.empty())
      {
        cout << " ::::::::: new iteration for destination folder search::::::::" << endl;
        pair<string, string> response;
        string currFolder = searchFolders.front();

        if(searchFolders.size() > 0)
          searchFolders.erase(searchFolders.begin());
        
        if(currFolder == curr_user)
          response = getFilesAndFolders(currFolder);
        else
          response = getFilesAndFoldersFromSubfolder(curr_user, currFolder);
        
        string filesAndFolders = response.first;
        string errorMessage = response.second;
        string notFoundMessage = "Key not found or Get";
	      bool notFound = errorMessage.find(notFoundMessage) != string::npos;

        // current folder is empty, continue to next folder
        if(notFound)
          continue;
        else {
          
          // go through all the files and folders in the current folder looking for a match
          unordered_map<string, size_t> folderHashes;
          stringstream ss(filesAndFolders);
          string pair;

          // map all files and folders to a map
          while (getline(ss, pair, ',')) {
            stringstream pairStream(pair);
            string oldFolderName;
            size_t oldHashValue;

              // Extract folder name and hash value from the pair
            getline(pairStream, oldFolderName, ':');
            pairStream >> oldHashValue;

              // Insert folder name and hash value into the map
            folderHashes[oldFolderName] = oldHashValue;
          }

          bool foundDest = false;
          // for each pair of file/folder name and its hash, try to find a match
          for (const auto& pair : folderHashes) {
            string name = pair.first;
            if(isFile(name))
            {
                continue;  // continue to search in other entries, since we are looking for a folder
            }
            else
            {  // this is a folder
              std::cout << "Looking at Folder: " << pair.first << ", Hash: " << pair.second << endl;
              if(pair.first == newfolder)
              {
                //found the hash of the folder to be moved !
                foundDest = true;
                destHash = pair.second;
                break;
              }
              else
              {
                // the requested file/folder could be within this folder, so we add it's hash to the vector for future examination
                 searchFolders.push_back(to_string(pair.second));
              }
            }
          }

          // if the dest folder was found, then we exit out
          if(foundDest)
            break;
        }
      }

      // folder was not found anywhere
      if(destHash == 0)
      {
          this->body = get_file_content_as_string("html/move_not_possible.html");
          (this->headers)[CONTENT_LEN] = to_string((this->body).length());
      }
      else
      {
        std::cout << "found folder " << newfolder << " with hash " << destHash << endl;

        pair<string, string> response;
        response = getFilesAndFolders(curr_user);
        
        string filesAndFolders = response.first;
        string errorMessage = response.second;
        string notFoundMessage = "Key not found or Get";
	      bool notFound = errorMessage.find(notFoundMessage) != string::npos;

        if(notFound)
        {
          this->body = get_file_content_as_string("html/download-subfolder.html");
          replace_all(this->body, "$allDownloadFiles", "No Files/Folders exist, so move cannot occur");
          (this->headers)[CONTENT_LEN] = to_string((this->body).length());
          return;
        }
        else
        {
          unordered_map<string, size_t> folderHashes;
          // Create a string stream to parse the serialized string
          stringstream ss(filesAndFolders);
          string pair;
      
          while (getline(ss, pair, ',')) {
              stringstream pairStream(pair);
              string oldFolderName;
              size_t oldHashValue;
      
              // Extract folder name and hash value from the pair
              getline(pairStream, oldFolderName, ':');
              pairStream >> oldHashValue;

              if(oldFolderName == fileFoldername)   // skip adding the moved file to the map of the current directory
                continue;
              else
                folderHashes[oldFolderName] = oldHashValue;
          }
      
          for (const auto& pair : folderHashes) {
              string name = pair.first;
              if(isFile(name))
                std::cout << "File: " << pair.first << ", Hash: " << pair.second << endl;
              else 
                std::cout << "Folder: " << pair.first << ", Hash: " << pair.second << endl;
          }

          stringstream ssN;
          for (const auto& pair : folderHashes) {
              ssN << pair.first << ":" << pair.second << ",";
          }

          string serializedHashes = ssN.str();
          std::cout << "::::::New Serialized Hash Values::::" << serializedHashes << endl;
          storeFilesFoldersRoot(curr_user, serializedHashes);

          response = getFilesAndFoldersFromSubfolder(curr_user, to_string(destHash));
          string filesAndFolders = response.first;
          string errorMessage = response.second;
          string notFoundMessage = "Key not found or Get";
	        bool notFound = errorMessage.find(notFoundMessage) != string::npos;

          if(notFound)
          {
            unordered_map<string, size_t> folderHashes;
            folderHashes[fileFoldername] = fileFolderHash;

            stringstream ss;
            for (const auto& pair : folderHashes) {
                ss << pair.first << ":" << pair.second << ",";
            }

            string serializedHashes = ss.str();
            std::cout << "::::::::::Serialized Hash Values for new dest folder::::::::::" << serializedHashes << endl;
            storeFilesFolders(curr_user, to_string(destHash), serializedHashes);
          }
          else
          {
              unordered_map<string, size_t> folderHashes;
              // Create a string stream to parse the serialized string
              stringstream ss(filesAndFolders);
              string pair;

              while (getline(ss, pair, ',')) {
                  stringstream pairStream(pair);
                  string oldFolderName;
                  size_t oldHashValue;

                  // Extract folder name and hash value from the pair
                  getline(pairStream, oldFolderName, ':');
                  pairStream >> oldHashValue;

                  // Insert folder name and hash value into the map
                  folderHashes[oldFolderName] = oldHashValue;
              }

              for (const auto& pair : folderHashes) {
                  string name = pair.first;
                  if(isFile(name))
                    std::cout << "File in dest folder: " << pair.first << ", Hash: " << pair.second << endl;
                  else 
                    std::cout << "Folder in dest folder: " << pair.first << ", Hash: " << pair.second << endl;
              }

              folderHashes[fileFoldername] = fileFolderHash;
              // serialize everything again
              stringstream ssN;
              for (const auto& pair : folderHashes) {
                  ssN << pair.first << ":" << pair.second << ",";
              }

              string serializedHashes = ssN.str();
              std::cout << "::::::::::New Serialized Hash Values for dest folder::::::::::" << serializedHashes << endl;

              storeFilesFolders(curr_user, to_string(destHash), serializedHashes);
          }
        }

        this->body = get_file_content_as_string("html/move-success.html");
        replace_all(this->body, "$filename", fileFoldername);
        replace_all(this->body, "$newfolder", newfolder);
        (this->headers)[CONTENT_LEN] = to_string((this->body).length());
      }
    }
    else
    {
      // search for all 3 to obtain their hashes
      size_t fileFolderHash = 0;
      size_t sourceHash = 0; // 1 to indicate that source is root
      size_t destHash = 0;

      vector<string> searchFolders;
      searchFolders.push_back(curr_user);
      while(!searchFolders.empty())
      {
        cout << " ::::::::: new iteration for file/folder search::::::::" << endl;
        pair<string, string> response;
        string currFolder = searchFolders.front();

        if(searchFolders.size() > 0)
          searchFolders.erase(searchFolders.begin());
        
        if(currFolder == curr_user)
          response = getFilesAndFolders(currFolder);
        else
          response = getFilesAndFoldersFromSubfolder(curr_user, currFolder);
        
        string filesAndFolders = response.first;
        string errorMessage = response.second;
        string notFoundMessage = "Key not found or Get";
	      bool notFound = errorMessage.find(notFoundMessage) != string::npos;

        // current folder is empty, continue to next folder
        if(notFound)
          continue;
        else {
          
          // go through all the files and folders in the current folder looking for a match
          unordered_map<string, size_t> folderHashes;
          stringstream ss(filesAndFolders);
          string pair;

          // map all files and folders to a map
          while (getline(ss, pair, ',')) {
            stringstream pairStream(pair);
            string oldFolderName;
            size_t oldHashValue;

              // Extract folder name and hash value from the pair
            getline(pairStream, oldFolderName, ':');
            pairStream >> oldHashValue;

              // Insert folder name and hash value into the map
            folderHashes[oldFolderName] = oldHashValue;
          }

          bool foundFile = false;
          // for each pair of file/folder name and its hash, try to find a match
          for (const auto& pair : folderHashes) {
            string name = pair.first;
            if(isFile(name))
            {
              std::cout << "Looking at File: " << pair.first << ", Hash: " << pair.second << endl;
              if(pair.first == fileFoldername)
              {
                // found the hash of the file to be moved !
                foundFile = true;
                fileFolderHash = pair.second;
                if(currFolder == curr_user)
                  sourceHash = 1;
                else 
                {
                  sourceHash = std::stoull(currFolder);
                  std::cout << "found source hash : " << sourceHash << endl;
                }
                break;
              }
              else
                continue;  // continue to search in other entries
            }
            else
            {  // this is a folder
              std::cout << "Looking at Folder: " << pair.first << ", Hash: " << pair.second << endl;
              if(pair.first == fileFoldername)
              {
                //found the hash of the folder to be moved !
                foundFile = true;
                fileFolderHash = pair.second;
                if(currFolder == curr_user)
                  sourceHash = 1;
                else 
                {
                  sourceHash = std::stoull(currFolder);
                  std::cout << "found source hash : " << sourceHash << endl;
                }
                break;
              }
              else
              {
                // the requested file/folder could be within this folder, so we add it's hash to the vector for future examination
                 searchFolders.push_back(to_string(pair.second));
              }
            }
          }

          // if the file was found, then we exit out
          if(foundFile)
            break;
        }
      }

      // file was not found anywhere
      if(fileFolderHash == 0)
      {
          this->body = get_file_content_as_string("html/move_not_possible.html");
          (this->headers)[CONTENT_LEN] = to_string((this->body).length());
          return;
      }
      else
        std::cout << "found file " << fileFoldername << " with hash " << fileFolderHash << endl; 

      // now, we find the destination folder's hash
      searchFolders.clear();
      searchFolders.push_back(curr_user); // start searching in root
      while(!searchFolders.empty())
      {
        cout << " ::::::::: new iteration for destination folder search::::::::" << endl;
        pair<string, string> response;
        string currFolder = searchFolders.front();

        if(searchFolders.size() > 0)
          searchFolders.erase(searchFolders.begin());
        
        if(currFolder == curr_user)
          response = getFilesAndFolders(currFolder);
        else
          response = getFilesAndFoldersFromSubfolder(curr_user, currFolder);
        
        string filesAndFolders = response.first;
        string errorMessage = response.second;
        string notFoundMessage = "Key not found or Get";
	      bool notFound = errorMessage.find(notFoundMessage) != string::npos;

        // current folder is empty, continue to next folder
        if(notFound)
          continue;
        else {
          
          // go through all the files and folders in the current folder looking for a match
          unordered_map<string, size_t> folderHashes;
          stringstream ss(filesAndFolders);
          string pair;

          // map all files and folders to a map
          while (getline(ss, pair, ',')) {
            stringstream pairStream(pair);
            string oldFolderName;
            size_t oldHashValue;

              // Extract folder name and hash value from the pair
            getline(pairStream, oldFolderName, ':');
            pairStream >> oldHashValue;

              // Insert folder name and hash value into the map
            folderHashes[oldFolderName] = oldHashValue;
          }

          bool foundDest = false;
          // for each pair of file/folder name and its hash, try to find a match
          for (const auto& pair : folderHashes) {
            string name = pair.first;
            if(isFile(name))
            {
                continue;  // continue to search in other entries, since we are looking for a folder
            }
            else
            {  // this is a folder
              std::cout << "Looking at Folder: " << pair.first << ", Hash: " << pair.second << endl;
              if(pair.first == newfolder)
              {
                //found the hash of the folder to be moved !
                foundDest = true;
                destHash = pair.second;
                break;
              }
              else
              {
                // the requested file/folder could be within this folder, so we add it's hash to the vector for future examination
                 searchFolders.push_back(to_string(pair.second));
              }
            }
          }

          // if the dest folder was found, then we exit out
          if(foundDest)
            break;
        }
      }

      // folder was not found anywhere
      if(destHash == 0)
      {
          this->body = get_file_content_as_string("html/move_not_possible.html");
          (this->headers)[CONTENT_LEN] = to_string((this->body).length());
      }
      else
      {
        std::cout << "found folder " << newfolder << " with hash " << destHash << endl;

        pair<string, string> response;
        if(sourceHash == 1) // found at root
          response = getFilesAndFolders(curr_user);
        else
          response = getFilesAndFoldersFromSubfolder(curr_user, to_string(sourceHash));
        
        string filesAndFolders = response.first;
        string errorMessage = response.second;
        string notFoundMessage = "Key not found or Get";
	      bool notFound = errorMessage.find(notFoundMessage) != string::npos;

        if(notFound)
        {
          this->body = get_file_content_as_string("html/download-subfolder.html");
          replace_all(this->body, "$allDownloadFiles", "No Files/Folders exist, so move cannot occur");
          (this->headers)[CONTENT_LEN] = to_string((this->body).length());
          return;
        }
        else
        {
          unordered_map<string, size_t> folderHashes;
          // Create a string stream to parse the serialized string
          stringstream ss(filesAndFolders);
          string pair;
      
          while (getline(ss, pair, ',')) {
              stringstream pairStream(pair);
              string oldFolderName;
              size_t oldHashValue;
      
              // Extract folder name and hash value from the pair
              getline(pairStream, oldFolderName, ':');
              pairStream >> oldHashValue;

              if(oldFolderName == fileFoldername)   // skip adding the moved file to the map of the current directory
                continue;
              else
                folderHashes[oldFolderName] = oldHashValue;
          }
      
          for (const auto& pair : folderHashes) {
              string name = pair.first;
              if(isFile(name))
                std::cout << "File within source folder: " << pair.first << ", Hash: " << pair.second << endl;
              else 
                std::cout << "Folder within source folder: " << pair.first << ", Hash: " << pair.second << endl;
          }

          stringstream ssN;
          for (const auto& pair : folderHashes) {
              ssN << pair.first << ":" << pair.second << ",";
          }

          string serializedHashes = ssN.str();
          std::cout << "::::::New Serialized Hash Values::::" << serializedHashes << endl;

          if(sourceHash == 1)
            storeFilesFoldersRoot(curr_user, serializedHashes);
          else 
            storeFilesFolders(curr_user, to_string(sourceHash), serializedHashes);

          response = getFilesAndFoldersFromSubfolder(curr_user, to_string(destHash));
          string filesAndFolders = response.first;
          string errorMessage = response.second;
          string notFoundMessage = "Key not found or Get";
	        bool notFound = errorMessage.find(notFoundMessage) != string::npos;

          if(notFound)
          {
            unordered_map<string, size_t> folderHashes;
            folderHashes[fileFoldername] = fileFolderHash;

            stringstream ss;
            for (const auto& pair : folderHashes) {
                ss << pair.first << ":" << pair.second << ",";
            }

            string serializedHashes = ss.str();
            std::cout << "::::::::::Serialized Hash Values for new dest folder::::::::::" << serializedHashes << endl;
            storeFilesFolders(curr_user, to_string(destHash), serializedHashes);
          }
          else
          {
              unordered_map<string, size_t> folderHashes;
              // Create a string stream to parse the serialized string
              stringstream ss(filesAndFolders);
              string pair;

              while (getline(ss, pair, ',')) {
                  stringstream pairStream(pair);
                  string oldFolderName;
                  size_t oldHashValue;

                  // Extract folder name and hash value from the pair
                  getline(pairStream, oldFolderName, ':');
                  pairStream >> oldHashValue;

                  // Insert folder name and hash value into the map
                  folderHashes[oldFolderName] = oldHashValue;
              }

              for (const auto& pair : folderHashes) {
                  string name = pair.first;
                  if(isFile(name))
                    std::cout << "File in dest folder: " << pair.first << ", Hash: " << pair.second << endl;
                  else 
                    std::cout << "Folder in dest folder: " << pair.first << ", Hash: " << pair.second << endl;
              }

              folderHashes[fileFoldername] = fileFolderHash;
              // serialize everything again
              stringstream ssN;
              for (const auto& pair : folderHashes) {
                  ssN << pair.first << ":" << pair.second << ",";
              }

              string serializedHashes = ssN.str();
              std::cout << "::::::::::New Serialized Hash Values for dest folder::::::::::" << serializedHashes << endl;

              storeFilesFolders(curr_user, to_string(destHash), serializedHashes);
          }
        }

        this->body = get_file_content_as_string("html/move-success.html");
        replace_all(this->body, "$filename", fileFoldername);
        replace_all(this->body, "$newfolder", newfolder);
        (this->headers)[CONTENT_LEN] = to_string((this->body).length());
      }
    }
  }
}




/* rename file */
void Response::rename_file(Request req) {
  this->status = OK;
  (this->headers)[CONTENT_TYPE] = "text/html";
  vector<string> tokens = split(req.body.c_str(), '&');
  // string foldername = tokens.at(0).substr(tokens.at(0).find('=') + 1);
  string oldname = tokens.at(0).substr(tokens.at(0).find('=') + 1);
  string newname = tokens.at(1).substr(tokens.at(1).find('=') + 1);

  if(oldname.length() == 0 || newname.length() == 0)
  {
    this->body = get_file_content_as_string("html/file-rename-fail.html");
    (this->headers)[CONTENT_LEN] = to_string((this->body).length());
    return;
  }
  else
  {
    cout << "oldname: " << oldname << "newname: " << newname << endl; 
    size_t sourceHash = 0; // use 1 to indicate root
    
      vector<string> searchFolders;
      searchFolders.push_back(curr_user);
      while(!searchFolders.empty())
      {
        cout << " ::::::::: new iteration for file/folder rename search::::::::" << endl;
        pair<string, string> response;
        string currFolder = searchFolders.front();

        if(searchFolders.size() > 0)
          searchFolders.erase(searchFolders.begin());
        
        if(currFolder == curr_user)
          response = getFilesAndFolders(currFolder);
        else
          response = getFilesAndFoldersFromSubfolder(curr_user, currFolder);
        
        string filesAndFolders = response.first;
        string errorMessage = response.second;
        string notFoundMessage = "Key not found or Get";
	      bool notFound = errorMessage.find(notFoundMessage) != string::npos;

        // current folder is empty, continue to next folder
        if(notFound)
          continue;
        else {
          // go through all the files and folders in the current folder looking for a match
          unordered_map<string, size_t> folderHashes;
          stringstream ss(filesAndFolders);
          string pair;

          // map all files and folders to a map
          while (getline(ss, pair, ',')) {
            stringstream pairStream(pair);
            string oldFolderName;
            size_t oldHashValue;

              // Extract folder name and hash value from the pair
            getline(pairStream, oldFolderName, ':');
            pairStream >> oldHashValue;

            // Insert folder name and hash value into the map
            folderHashes[oldFolderName] = oldHashValue;
          }

          bool foundFile = false;
          // for each pair of file/folder name and its hash, try to find a match
          for (const auto& pair : folderHashes) {
            string name = pair.first;
            if(isFile(name))
            {
              std::cout << "Looking at File: " << pair.first << ", Hash: " << pair.second << endl;
              if(pair.first == oldname)
              {
                // found the hash of the file to be moved !
                foundFile = true;
                if(currFolder == curr_user)
                  sourceHash = 1;
                else
                  sourceHash = std::stoull(currFolder);
                break;
              }
              else
                continue;  // continue to search in other entries
            }
            else
            {  // this is a folder
              std::cout << "Looking at Folder: " << pair.first << ", Hash: " << pair.second << endl;
              if(pair.first == oldname)
              {
                //found the hash of the folder to be moved !
                foundFile = true;
                if(currFolder == curr_user)
                  sourceHash = 1;
                else
                  sourceHash = std::stoull(currFolder);
                break;
              }
              else
              {
                // the requested file/folder could be within this folder, so we add it's hash to the vector for future examination
                 searchFolders.push_back(to_string(pair.second));
              }
            }
          }

          // if the file was found, then we exit out
          if(foundFile)
            break;
        }
      }

      // file was not found anywhere
      if(sourceHash == 0)
      {
          this->body = get_file_content_as_string("html/file-rename-fail.html");
          (this->headers)[CONTENT_LEN] = to_string((this->body).length());
          return;
      }
      else
      {
        std::cout << "found file " << oldname << endl; 

        pair<string, string> response;
        if(sourceHash == 1) // found at root
          response = getFilesAndFolders(curr_user);
        else
          response = getFilesAndFoldersFromSubfolder(curr_user, to_string(sourceHash));
        
        string filesAndFolders = response.first;
        string errorMessage = response.second;
        string notFoundMessage = "Key not found or Get";
	      bool notFound = errorMessage.find(notFoundMessage) != string::npos;

        if(notFound)
        {
          this->body = get_file_content_as_string("html/download-subfolder.html");
          replace_all(this->body, "$allDownloadFiles", "No Files/Folders exist, so renaming cannot occur");
          (this->headers)[CONTENT_LEN] = to_string((this->body).length());
          return;
        }
        else
        {
          unordered_map<string, size_t> folderHashes;
          // Create a string stream to parse the serialized string
          stringstream ss(filesAndFolders);
          string pair;
      
          while (getline(ss, pair, ',')) {
              stringstream pairStream(pair);
              string oldFolderName;
              size_t oldHashValue;
      
              // Extract folder name and hash value from the pair
              getline(pairStream, oldFolderName, ':');
              pairStream >> oldHashValue;

              if(oldFolderName == oldname)   // modify addition of the renamed file to the map of the current directory
                folderHashes[newname] = oldHashValue;
              else
                folderHashes[oldFolderName] = oldHashValue;
          }

          stringstream ssN;
          for (const auto& pair : folderHashes) {
              ssN << pair.first << ":" << pair.second << ",";
          }

          string serializedHashes = ssN.str();
          std::cout << "::::::New Serialized Hash Values After rename::::" << serializedHashes << endl;

          if(sourceHash == 1)
            storeFilesFoldersRoot(curr_user, serializedHashes);
          else 
            storeFilesFolders(curr_user, to_string(sourceHash), serializedHashes);
        }

        this->body = get_file_content_as_string("html/file-rename-success.html");
        replace_all(this->body, "$oldname", oldname);
        replace_all(this->body, "$newname", newname);
        (this->headers)[CONTENT_LEN] = to_string((this->body).length());
      }
  }
}


/* delete file */
void Response::delete_file(Request req) {
  this->status = OK;
  (this->headers)[CONTENT_TYPE] = "text/html";
  vector<string> tokens = split(req.body.c_str(), '&');
  string nameToDelete = tokens.at(0).substr(tokens.at(0).find('=') + 1);
  if (nameToDelete.length() == 0) {
    this->body = get_file_content_as_string("html/file-delete-fail.html");
    (this->headers)[CONTENT_LEN] = to_string((this->body).length());
  }
  else
  {
      cout << "entity name to be deleted: " << nameToDelete << endl; 
      size_t sourceHash = 0; // use 1 to indicate root
    
      vector<string> searchFolders;
      searchFolders.push_back(curr_user);
      while(!searchFolders.empty())
      {
        cout << " ::::::::: new iteration for file/folder delete search::::::::" << endl;
        pair<string, string> response;
        string currFolder = searchFolders.front();

        if(searchFolders.size() > 0)
          searchFolders.erase(searchFolders.begin());
        
        if(currFolder == curr_user)
          response = getFilesAndFolders(currFolder);
        else
          response = getFilesAndFoldersFromSubfolder(curr_user, currFolder);
        
        string filesAndFolders = response.first;
        string errorMessage = response.second;
        string notFoundMessage = "Key not found or Get";
	      bool notFound = errorMessage.find(notFoundMessage) != string::npos;

        // current folder is empty, continue to next folder
        if(notFound)
          continue;
        else {
          // go through all the files and folders in the current folder looking for a match
          unordered_map<string, size_t> folderHashes;
          stringstream ss(filesAndFolders);
          string pair;

          // map all files and folders to a map
          while (getline(ss, pair, ',')) {
            stringstream pairStream(pair);
            string oldFolderName;
            size_t oldHashValue;

              // Extract folder name and hash value from the pair
            getline(pairStream, oldFolderName, ':');
            pairStream >> oldHashValue;

            // Insert folder name and hash value into the map
            folderHashes[oldFolderName] = oldHashValue;
          }

          bool foundFile = false;
          // for each pair of file/folder name and its hash, try to find a match
          for (const auto& pair : folderHashes) {
            string name = pair.first;
            if(isFile(name))
            {
              std::cout << "Looking at File: " << pair.first << ", Hash: " << pair.second << endl;
              if(pair.first == nameToDelete)
              {
                // found the hash of the file to be moved !
                foundFile = true;
                if(currFolder == curr_user)
                  sourceHash = 1;
                else
                  sourceHash = std::stoull(currFolder);
                break;
              }
              else
                continue;  // continue to search in other entries
            }
            else
            {  // this is a folder
              std::cout << "Looking at Folder: " << pair.first << ", Hash: " << pair.second << endl;
              if(pair.first == nameToDelete)
              {
                //found the hash of the folder to be moved !
                foundFile = true;
                if(currFolder == curr_user)
                  sourceHash = 1;
                else
                  sourceHash = std::stoull(currFolder);
                break;
              }
              else
              {
                // the requested file/folder could be within this folder, so we add it's hash to the vector for future examination
                 searchFolders.push_back(to_string(pair.second));
              }
            }
          }

          // if the file was found, then we exit out
          if(foundFile)
            break;
        }
      }

      // file was not found anywhere
      if(sourceHash == 0)
      {
          this->body = get_file_content_as_string("html/file-delete-fail.html");
          (this->headers)[CONTENT_LEN] = to_string((this->body).length());
          return;
      }
      else
      {
        std::cout << "found file " << nameToDelete << endl; 

        pair<string, string> response;
        if(sourceHash == 1) // found at root
          response = getFilesAndFolders(curr_user);
        else
          response = getFilesAndFoldersFromSubfolder(curr_user, to_string(sourceHash));
        
        string filesAndFolders = response.first;
        string errorMessage = response.second;
        string notFoundMessage = "Key not found or Get";
	      bool notFound = errorMessage.find(notFoundMessage) != string::npos;

        if(notFound)
        {
          this->body = get_file_content_as_string("html/download-subfolder.html");
          replace_all(this->body, "$allDownloadFiles", "No Files/Folders exist, so deletion cannot occur");
          (this->headers)[CONTENT_LEN] = to_string((this->body).length());
          return;
        }
        else
        {
          size_t deleted_entity_hash = 0;
          unordered_map<string, size_t> folderHashes;
          // Create a string stream to parse the serialized string
          stringstream ss(filesAndFolders);
          string pair;
      
          while (getline(ss, pair, ',')) {
              stringstream pairStream(pair);
              string oldFolderName;
              size_t oldHashValue;
      
              // Extract folder name and hash value from the pair
              getline(pairStream, oldFolderName, ':');
              pairStream >> oldHashValue;

              if(oldFolderName == nameToDelete)   // modify addition of the renamed file to the map of the current directory
              {
                deleted_entity_hash = oldHashValue;
                continue;
              }
              else
                folderHashes[oldFolderName] = oldHashValue;
          }

          stringstream ssN;
          for (const auto& pair : folderHashes) {
              ssN << pair.first << ":" << pair.second << ",";
          }

          string serializedHashes = ssN.str();
          std::cout << "::::::New Serialized Hash Values After delete::::" << serializedHashes << endl;

          if(sourceHash == 1)
            storeFilesFoldersRoot(curr_user, serializedHashes);
          else 
            storeFilesFolders(curr_user, to_string(sourceHash), serializedHashes);
          
          // do delete with deleted_entity_hash
          string response = deleteFilesAndFolders(curr_user, to_string(deleted_entity_hash));
          string message = response;
          string FailedMessage = "Delete operation failed";
	        bool failed = message.find(FailedMessage) != string::npos;
          // current folder is empty, continue to next folder
          if(failed)
          {
            this->body = get_file_content_as_string("html/file-delete-fail.html");
            (this->headers)[CONTENT_LEN] = to_string((this->body).length());
            return;
          }
          else
          {
            this->body = get_file_content_as_string("html/file-delete-success.html");
            replace_all(this->body, "$filename", nameToDelete);
            (this->headers)[CONTENT_LEN] = to_string((this->body).length());
          }
        }
      }
  }
}


/*
 *
 * EMAIL RELATED RESPONSES
 *
 */

void Response::send_email(Request req) {
  this->status = OK;
  (this->headers)[CONTENT_TYPE] = "text/html";
  this->body = get_file_content_as_string("html/send-email.html");
  (this->headers)[CONTENT_LEN] = to_string((this->body).length());
}

/* handle send email */
void Response::handle_send_email(Request req) {

  vector<string> params = split(url_decode(req.body).c_str(), '&');

  cout << "Request Body" << req.body << endl;
  cout << "PARAMS" << params.size() << endl;

  string sent_to = split(params.at(0), '=').at(1);
  string title = split(params.at(1), '=').at(1);
  string content = split(params.at(2), '=').at(1);
  string curr_time = get_current_time();

  // decoding
  // replace_all(sent_to, "%40", "@");
  replace_all(title, "+", " ");
  replace_all(content, "+", " ");

  string message;
  message += "From: <" + user_name + "@localhost>\r\n";
  message += "To: <" + sent_to + ">\r\n";
  message += "Date: " + curr_time + "\r\n";
  message += "Subject: " + title + "\r\n";
  message += content + "\r\n";

  this->status = OK;
  (this->headers)[CONTENT_TYPE] = "text/html";
  this->body = get_file_content_as_string("html/send-email-success.html");
  (this->headers)[CONTENT_LEN] = to_string((this->body).length());

  // if (content != "") {

  //EMAILLOGIN :
  std::string server_address("localhost:5020");
  auto channel = grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
  SMTPClient smtp(channel);
  smtp.connect(user_name);
  smtp.senderDetails(user_name); // This supports external emails right?
  smtp.receiverDetails(sent_to);
  smtp.sendData(message);

  cout << "\nData sent, now going to send dot\n" <<endl;
  smtp.sendDot();
  cout << "\nDot sent\n" <<endl;
  smtp.quit(); //stop the connection
  //EMAILLOGIN END

}

/* inbox */
void Response::inbox(Request req) {

    cout << "parsing done! " << req.body.c_str() << endl;

    std::string server_address_pop("127.0.0.1:5000"); //POP3 
    auto channel_pop3 = grpc::CreateChannel(server_address_pop, grpc::InsecureChannelCredentials());
    POP3Client pop3(channel_pop3);
    curEmail = curr_user.substr(0,curr_user.size());
    cout << pop3.userAndPass(curEmail,"cis505") << endl;
    string numMessages = pop3.stat();

  //EMAILLOGIN END
  this->status = OK;
  (this->headers)[CONTENT_TYPE] = "text/html";
  this->body = get_file_content_as_string("html/inbox.html");
  (this->headers)[CONTENT_LEN] = to_string((this->body).length());

  //EMAILLOGIN

  cout << "Num Messages"  << numMessages << endl;

  vector<vector<string>> emails;
  
  //retrive all the emails
  for (int i = 0; i < stoi(numMessages); i++) {


    string maillist = pop3.retr(to_string(i + 1)); //retrieve all the emails
    cout << "email retrieved "<< maillist << endl;

    //store number, from, title and time
    vector<string> singleEmail;
    singleEmail.push_back(to_string(i + 1));

    //from address
    std::vector<std::string> details = parseEmailDetails(maillist);

    for (int j = 0; j < details.size();j++) {
      singleEmail.push_back(details.at(j));
    }

    emails.push_back(singleEmail);
  }

  //Convert into format for the webpage
  string htmlTable;

  for (int i = 0; i < emails.size();i++) {
      cout << "Email Number " << emails.at(i).at(0) << endl;
      cout << "From " << emails.at(i).at(1) << endl;
      cout << "Title " << emails.at(i).at(2) << endl;
      cout << "Time " << emails.at(i).at(3) << endl;

      htmlTable += "<tr>";
      htmlTable += "<form method='POST' action='/viewemail'>"; // Specify the server endpoint
      htmlTable += "<td>" + emails.at(i).at(0) + "</td>"; // Column # (email ID shown in a cell, consider hiding if not wanted visually)
      htmlTable += "<td>" + emails.at(i).at(1) + "</td>"; // Column From
      htmlTable += "<td>" + emails.at(i).at(2) + "</td>"; // Column Title
      htmlTable += "<td>" + emails.at(i).at(3) + "</td>"; // Column Time
      htmlTable += "<td><input type='hidden' name='emailId' value='" + emails.at(i).at(0) + "'></td>"; // Hidden input to store the email ID
      htmlTable += "<td><button type='submit' class='btn btn-primary'>View Email</button></td>"; // Submit button to send the form
      htmlTable += "</form>";
      htmlTable += "</tr>";

    }

  //Retrive all UIDLs
  for (int i = 0; i < emails.size();i++) {
      uidl[to_string(i)] = pop3.uidl(to_string(i));
  }

  pop3.quit(); //stop the connection

  //EMAILLOGIN END
  replace_all(this->body, "$maillist",htmlTable);
  (this->headers)[CONTENT_LEN] = to_string((this->body).length());

}


/* view email */
void Response::view_email(Request req) { 

  string currentEmailNumber = split(req.body, '=').at(1);
  cout << "currentEmailNumber " << currentEmailNumber << endl;

  //EMAILLOGIN
  std::string server_address("127.0.0.1:5000"); //WEBMAILSERVER PORT
  auto channel = grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
  POP3Client pop3(channel);

  //login to pop3
  curEmail = curr_user.substr(0,curr_user.size());
  cout << pop3.userAndPass(curEmail,"cis505") << endl;

  string maillist = pop3.retr(currentEmailNumber); //Check how we are receiving only a particular email
  cout << "mail retrieved to view"<< maillist << endl;

  //retrive the content 
  vector<string> singleEmail;
  singleEmail.push_back(currentEmailNumber); 

  //from address
  std::vector<std::string> details = parseEmailDetails(maillist);

  for (int j = 0; j < details.size();j++) {
    singleEmail.push_back(details.at(j));    
  }

  string content = extractContentAfterSubject(maillist);

  pop3.quit();

  //EMAILLOGIN END
  this->status = OK;
  (this->headers)[CONTENT_TYPE] = "text/html";
  this->body = get_file_content_as_string("html/view-email.html");

  //Check Parsing
  replace_all(this->body, "$emailNumber", singleEmail.at(0));
  replace_all(this->body, "$from", singleEmail.at(1));
  replace_all(this->body, "$title", singleEmail.at(2));
  replace_all(this->body, "$date", singleEmail.at(3));
  replace_all(this->body, "$content", content);


  // add the email number in the body
  string buttons = "";

  buttons += "<form method='GET' action='/replytoemail'>"; // Specify the server endpoint
  buttons += "<input type='hidden' name='emailId' value='" + currentEmailNumber + "'>"; // Hidden input to store the email ID
  buttons += "<button type='submit' class='btn btn-primary'>Reply </button>"; // Submit button to send the form
  buttons += "</form>";

  buttons += "<form method='GET' action='/forwardemail'>"; // Specify the server endpoint
  buttons += "<input type='hidden' name='emailId' value='" + currentEmailNumber + "'>"; // Hidden input to store the email ID
  buttons += "<button type='submit' class='btn btn-primary'> Forward </button>"; // Submit button to send the form
  buttons += "</form>";

  buttons += "<form method='GET' action='/deleteemail'>"; // Specify the server endpoint
  buttons += "<input type='hidden' name='emailId' value='" + currentEmailNumber + "'>"; // Hidden input to store the email ID
  buttons += "<button type='submit' class='btn btn-primary'>Delete </button>"; // Submit button to send the form
  buttons += "</form>";
              

  replace_all(this->body, "$buttons", buttons);

  (this->headers)[CONTENT_LEN] = to_string((this->body).length());

}


/* forward email */
void Response::forward_email(Request req) {

  //get the emailID to be forwarded 
  string mailNumber = split(req.path, '=').at(1);
  string emailID = "<input type=\"hidden\" name=\"emailID\" value=\""+ mailNumber +">";

  cout << "Forward Email number " << emailID << endl;

  this->status = OK;
  (this->headers)[CONTENT_TYPE] = "text/html";
  this->body = get_file_content_as_string("html/forward-email.html");

  replace_all(this->body, "$emailID", emailID);

  (this->headers)[CONTENT_LEN] = to_string((this->body).length());

}

void Response::forward_email_success(Request req) {

  cout << "Body " << req.body << endl;

  string curr_time = get_current_time();
  string emailToBeForwarded = getValue(req.body,"emailID=","%");

  size_t startPos = req.body.find("sentto=") + 7;
  string sent_to = req.body.substr(startPos);

  replace_all(sent_to, "%40", "@");

  //EMAILLOGIN
  std::string server_address_pop3("127.0.0.1:5000"); //WEBMAILSERVER PORT
  auto channel_pop3 = grpc::CreateChannel(server_address_pop3, grpc::InsecureChannelCredentials());
  POP3Client pop3(channel_pop3);
  curEmail = curr_user.substr(0,curr_user.size());
  pop3.userAndPass(curEmail,"cis505");

  string numMessages = pop3.list();
  string maillist = pop3.retr(emailToBeForwarded); //Retrieve the email
  pop3.quit();

  //parse the email
  std::vector<std::string> details = parseEmailDetails(maillist);
  
  vector<string> singleEmail;
  singleEmail.push_back(emailToBeForwarded); 

  for (int j = 0; j < details.size();j++) {
    singleEmail.push_back(details.at(j));    
  }

  string content = extractContentAfterSubject(maillist);

  string message;
  message += "From: <" + user_name + "@localhost>\r\n";
  message += "To: <" + sent_to + ">\r\n";
  message += "Date: " + curr_time + "\r\n";
  message += "Subject: FWD:" + singleEmail.at(2) + "\r\n";
  message += content + "\r\n";

  cout << "Email Forwarded "<< message << endl;
  cout << "Receipient "<< sent_to << endl;

  std::string server_address_smtp("localhost:5020");
  auto channel_smtp = grpc::CreateChannel(server_address_smtp, grpc::InsecureChannelCredentials());
  SMTPClient smtp(channel_smtp);
  smtp.connect(user_name);
  smtp.senderDetails(user_name); 
  smtp.receiverDetails(sent_to);
  smtp.sendData(message);
  smtp.sendDot();
  smtp.quit(); //stop the connection


  this->status = OK;
  (this->headers)[CONTENT_TYPE] = "text/html";
  this->body = get_file_content_as_string("html/forward-email-success.html");
  (this->headers)[CONTENT_LEN] = to_string((this->body).length());
  //EMAILLOGIN END

}


void Response::reply_email(Request req) {

  //get the emailID to be forwarded 
  string mailNumber = split(req.path, '=').at(1);
  string emailID = "<input type=\"hidden\" name=\"emailID\" value=\""+ mailNumber +">";

  cout << "Reply Email number " << emailID << endl;
  replace_all(this->body, "$emailID", emailID);
  
  this->status = OK;
  (this->headers)[CONTENT_TYPE] = "text/html";
  this->body = get_file_content_as_string("html/reply-email.html");
  (this->headers)[CONTENT_LEN] = to_string((this->body).length());

}


/* reply email */
void Response::reply_email_success(Request req) {

  cout << "Reply Body " << req.body << endl;
  vector<string> params = split(url_decode(req.body).c_str(), '&');

  cout << "PARAMS" << params.size() << endl;

  // string sent_to = split(params.at(0), '=').at(1);
  // string title = split(params.at(0), '=').at(1);
  // string content = split(params.at(1), '=').at(1);
  string title = split(params.at(0), '=').at(1);
  string content = split(params.at(1), '=').at(1);
  string curr_time = get_current_time();

  //EMAILLOGIN
  std::string server_address_pop3("127.0.0.1:5000"); //WEBMAILSERVER PORT
  auto channel_pop3 = grpc::CreateChannel(server_address_pop3, grpc::InsecureChannelCredentials());
  POP3Client pop3(channel_pop3);
  curEmail = curr_user.substr(0,curr_user.size());
  pop3.userAndPass(curEmail,"cis505");

  string numMessages = pop3.list();
  // string maillist = pop3.retr(emailToBeForwarded); //Retrieve the email
  string maillist = pop3.retr("1"); //Retrieve the email
  pop3.quit();

  //parse the email
  std::vector<std::string> details = parseEmailDetails(maillist);
  
  vector<string> singleEmail;
  // singleEmail.push_back(emailToBeForwarded); 
  singleEmail.push_back("1"); 

  for (int j = 0; j < details.size();j++) {
    singleEmail.push_back(details.at(j));    
  }

  string sent_to = details.at(0).substr(0,details.at(0).length() - 1);

  string message;
  message += "From: <" + user_name + "@localhost>\r\n";
  message += "To: <" + sent_to + ">\r\n";
  message += "Date: " + curr_time + "\r\n";
  message += "Subject: REPLY:" + singleEmail.at(2) + "\r\n";
  message += content + "\r\n";

  cout << "Email Forwarded "<< message << endl;
  cout << "Receipient "<< sent_to << endl;

  std::string server_address_smtp("localhost:5020");
  auto channel_smtp = grpc::CreateChannel(server_address_smtp, grpc::InsecureChannelCredentials());
  SMTPClient smtp(channel_smtp);
  smtp.connect(user_name);
  smtp.senderDetails(user_name); 
  smtp.receiverDetails(sent_to);
  smtp.sendData(message);
  smtp.sendDot();
  smtp.quit(); //stop the connection

  this->status = OK;
  (this->headers)[CONTENT_TYPE] = "text/html";
  this->body = get_file_content_as_string("html/reply-email-success.html");
  (this->headers)[CONTENT_LEN] = to_string((this->body).length());
  //EMAILLOGIN END

}

void Response::delete_email(Request req) {

  //EMAILLOGIN
  std::string server_address("localhost:5000");
  auto channel = grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
  POP3Client pop3(channel);
  string emailID = split(req.path, '=').at(1);
  curEmail = curr_user.substr(0,curr_user.size());
  cout << pop3.userAndPass(curEmail,"cis505") << endl;
  cout << "Email to delte " << emailID << endl;

  //login to pop3
  string deleteMsg = pop3.deleteMail(emailID);
  pop3.quit();

  //EMAILLOGIN END
  
  this->status = OK;
  (this->headers)[CONTENT_TYPE] = "text/html";
  this->body = get_file_content_as_string("html/email-deleted.html");
  (this->headers)[CONTENT_LEN] = to_string((this->body).length());

}


/*
Admin Console
*/

void Response::admin_console(Request req) {

  cout << "Admin console "<< endl;
 
  //For GET Requests and POST requests - We always need the data!

  //Admin Console
  AdminConsole console;
  cout << "admin console created " << endl;

  //maps of the nodes
  map<string,string> responseNodes = console.startNodes();
  map<string,string> responseKVStore = console.startKVStore();
  map<string,string> nodesAndGroups = console.nodesAndGroups();

  //convert into strings for html
  string nodesResponse = "";
  string kvResponse = "";

  
    for (auto const& [key, value] : responseNodes) {
      
      cout << "Node " << key << "Status " << value << "Group " << nodesAndGroups[key]; 
        
      nodesResponse += "<tr>\n<td>";
      nodesResponse += key;
      nodesResponse += "</td>\n<td>";
      nodesResponse += nodesAndGroups[key];
      nodesResponse += "</td>\n<td>";
      nodesResponse += value;
      nodesResponse += "</td>\n<td>";

      // Add a form for the Shutdown button
      nodesResponse += "<form action='/admin-console' method='POST' style='display: inline;'>";
      nodesResponse += "<input type='hidden' name='nodeId' value='" + key + "'>"; // Changed the name to 'nodeId'
      nodesResponse += "<input type='hidden' name='action' value='shutdown'>"; // Additional field for specifying the action
      nodesResponse += "<button type='submit' class='btn btn-danger'>Shutdown</button>";
      nodesResponse += "</form>\n";

      // Add a form for the Restart button
      nodesResponse += "<form action='/admin-console' method='POST' style='display: inline;'>";
      nodesResponse += "<input type='hidden' name='nodeID' value='" + key + "'>"; // Changed the name to 'nodeId'
      nodesResponse += "<input type='hidden' name='action' value='restart'>"; // Additional field for specifying the action
      nodesResponse += "<button type='submit' class='btn btn-danger'>Restart</button>";
      nodesResponse += "</form>\n";

      nodesResponse += "<button class='btn btn-secondary' onclick='location.reload()'>Refresh</button>";

      nodesResponse += "</td>\n</tr>\n";

    }

      for (auto const& [key, value] : responseKVStore) {
        
        kvResponse += "<tr>\n<td>";
        kvResponse += "<td>";
        kvResponse += key;
        kvResponse += "<td>\n";
        kvResponse += "<td>";
        kvResponse += value;
        kvResponse += "<td>\n";
        kvResponse += "</tr>\n";

    }


  //set up the admin console webpage
  this->status = OK;
  (this->headers)[CONTENT_TYPE] = "text/html";
  this->body = get_file_content_as_string("html/admin-console.html");

  cout << "page rendered " << endl;

   replace_all(this->body, "$nodes", nodesResponse); //KV
   replace_all(this->body, "$kvstore", kvResponse); //KV

   cout << "values replaced " << endl;

  //For POST requests, we additionally need to send the status of the node
  if (req.method == "POST") {

    cout << "POST METHOD" << endl;

    // parse the commands
    vector<string> params = split(url_decode(req.body).c_str(), '&');
    string nodeId = split(params.at(0), '=').at(1);
    string action  = split(params.at(1), '=').at(1);

    cout << nodeId << "NodeID" << endl;
    cout << action << "action" << endl;

    console.nodeOperations(action,nodeId);
  }
  (this->headers)[CONTENT_LEN] = to_string((this->body).length());
}


