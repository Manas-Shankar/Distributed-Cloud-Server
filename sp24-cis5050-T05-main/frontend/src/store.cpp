#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <cstring>
#include <grpc++/grpc++.h>
#include <grpcpp/grpcpp.h>

#include "../grpc_proto/kv_grpc_proto/kv_store.grpc.pb.h"
#include "../grpc_proto/kv_grpc_proto/backend_master_as_server.grpc.pb.h"
#include "../include/sample_store_kv_client.h"
#include "../include/constants.h"
#include "../include/store.h"
#include "../include/utils.h"
#include "../include/config.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using kvstore::KeyValue;
using kvstore::PutRequest;
using kvstore::PutResponse;
using kvstore::GetRequest;
using kvstore::GetResponse;
using kvstore::CPutRequest;
using kvstore::CPutResponse;
using kvstore::DeleteRequest;
using kvstore::DeleteResponse;

using backendmaster::BackendMasterService;
using backendmaster::NotifyRecoveryRequest;
using backendmaster::NotifyRecoveryResponse;
using backendmaster::PrimaryRequest;
using backendmaster::PrimaryNode;
using backendmaster::ListNodesRequest;
using backendmaster::NodesList;
using backendmaster::GetNodeAddressRequest;
using backendmaster::GetNodeAddressResponse;

using namespace std;

string getkvNodeAddress(string key)
{
	string BackendMasterAddress = "127.0.0.1:5056";
	cout << "inside getkvNodeAddress, address of backend master:" << BackendMasterAddress << endl;

	grpc::ChannelArguments channelArgs;
    channelArgs.SetMaxReceiveMessageSize(1024 * 1024 * 1024);
	channelArgs.SetMaxSendMessageSize(1024 * 1024 * 1024);

	std::shared_ptr<grpc::Channel> channel = grpc::CreateCustomChannel(BackendMasterAddress, grpc::InsecureChannelCredentials(), channelArgs);
	kvClient client(channel);

   string response;

   response = client.getNodeAddress(key);
   cout << "credentials sent: key:" << key << " Response Received: " << response << endl;
   return response;
}

void put_in_kv(string row, string col, string value)
{
	string node_address = "";
	while(node_address == "")
	{	
		node_address = getkvNodeAddress(row);
		cout << "node address returned from backend master:" << node_address << endl;
	}

	// string address = MASTER_IP + ":" + MASTER_PORT;
	// cout << "inside put_kv, address of grpc kvstore-server:" << address << endl;

	grpc::ChannelArguments channelArgs;
    channelArgs.SetMaxReceiveMessageSize(1024 * 1024 * 1024);
	channelArgs.SetMaxSendMessageSize(1024 * 1024 * 1024);

	std::shared_ptr<grpc::Channel> channel = grpc::CreateCustomChannel(node_address, grpc::InsecureChannelCredentials(), channelArgs);
	kvClient client(channel);

   bool response;

   response = client.putToKv(row, col, value);
   cout << "credentials sent: row:" << row << " col:" << col << " Response Received: " << response << endl;
}

pair<string, string> get_from_kv(string row, string col)
{
	string node_address = "";
	while(node_address == "")
	{	
		node_address = getkvNodeAddress(row);
		cout << "node address returned from backend master:" << node_address << endl;
	}	
	// string address = MASTER_IP + ":" + MASTER_PORT;
		// cout << "address of grpc kvstore-server:" << address << endl;

		grpc::ChannelArguments channelArgs;
    	channelArgs.SetMaxReceiveMessageSize(1024 * 1024 * 1024);
		channelArgs.SetMaxSendMessageSize(1024 * 1024 * 1024);

		std::shared_ptr<grpc::Channel> channel = grpc::CreateCustomChannel(node_address, grpc::InsecureChannelCredentials(), channelArgs);
		kvClient client(channel);

	pair<string, string> response = client.getFromKv(row, col);

	cout << "credentials sent to GET from kv: row: " << row << " col: " << col << endl;
	cout << "\nResponse message Received from GET call: " << response.second << endl;

	return response;
}

string delete_from_kv(string row, string col)
{
	string node_address = "";
	while(node_address == "")
	{	
		node_address = getkvNodeAddress(row);
		cout << "node address returned from backend master:" << node_address << endl;
	}

	// string address = MASTER_IP + ":" + MASTER_PORT;
	// 	cout << "address of grpc kvstore-server:" << address << endl;

		grpc::ChannelArguments channelArgs;
    	channelArgs.SetMaxReceiveMessageSize(1024 * 1024 * 1024);
		channelArgs.SetMaxSendMessageSize(1024 * 1024 * 1024);

		std::shared_ptr<grpc::Channel> channel = grpc::CreateCustomChannel(node_address, grpc::InsecureChannelCredentials(), channelArgs);
		kvClient client(channel);

	string response = client.deleteFromKv(row, col);

	cout << "credentials sent to DELETE from kv: row: " << row << " col: " << col << endl;
	cout << "\nResponse message Received from DELETE call: " << response << endl;

	return response;
}

string deleteFilesAndFolders(string row, string hashID)
{
	string response = delete_from_kv(row, hashID);
	return response;
}

pair<string, string> getFilesAndFolders(string row)
{
	pair<string, string> response = get_from_kv(row, "FilesAndFolders");
	return response;
}

pair<string, string> getFilesAndFoldersFromSubfolder(string user, string folderHash)
{
	pair<string, string> response = get_from_kv(user, folderHash);
	return response;
}

void uploadFile(string username, string fileHashID, string fileContent)
{
	cout << "\nuploaded file content size:" << fileContent.size() << "\n" << endl;
	cout << "\n going to upload file details, row:" << username << " col: " << fileHashID << endl;
	put_in_kv(username, fileHashID, fileContent);
}

string getFileFromID(string username, string fileHashID)
{
	pair<string, string> response = get_from_kv(username, fileHashID);
	string notFoundMessage = "Key not found or Get";

	string errorMessage = response.second;
	bool notFound = errorMessage.find(notFoundMessage) != string::npos;
	if(notFound)
	{
		return "";
	}
	else
	{
		cout << "file retrieved" << endl;
		return response.first;
	}
}

void storeFilesFoldersRoot(string username, string serializedValues) {
//  string message = "put " + username + ",pwd," + password + "\r\n";
	cout << "\nStoring File/Folder path, received details, row:" << username << " col: FilesAndFolders" << " value:" << serializedValues << endl;
	put_in_kv(username, "FilesAndFolders", serializedValues);
}

void storeFilesFolders(string username, string hashID, string serializedValues) {
//  string message = "put " + username + ",pwd," + password + "\r\n";
	cout << "\nreceived details, row:" << username << " col: " << hashID << " value:" << serializedValues << endl;
	put_in_kv(username, hashID, serializedValues);
} 

void add_user(string username, string password) {
//  string message = "put " + username + ",pwd," + password + "\r\n";
	cout << "\nreceived details, row:" << username << " col: password," << " value:" << password << endl;
	put_in_kv(username, "password", password);
}

bool check_user_exists(string username)
{
	cout << "checking if " << username << "exists" << endl;

	pair<string, string> response = get_from_kv(username, "password");
	string notFoundMessage = "Key not found or Get";

	string errorMessage = response.second;
	bool notFound = errorMessage.find(notFoundMessage) != string::npos;
	if(notFound)
	{
		return 0;
	}
	else
	{
		cout << "user already exists !" << endl;
		return 1;
	}
}


bool is_login_valid(string username, string password) {
	cout << "checking if " << username << " exists" << endl;

	pair<string, string> response = get_from_kv(username, "password");
	string notFoundMessage = "Key not found or Get";
	string errorMessage = response.second;

	bool notFound = errorMessage.find(notFoundMessage) != string::npos;
	if(notFound)
	{
		return 0;
	}
	else
	{
		cout << "user exists, checking if password equals " << password << endl;
		string pass = response.first;
		// cout << "decoded bytes password:" << passwordDecoded << endl;
		if(pass == password)
		{
			cout << "password matches !" << endl;
			return 1;
		}
		else
		{
			cout << "password doesn't match!" << endl;
			return 0;
		}

	}
}

void add_session(string id) { sessions[id] = time(NULL); }

void delete_session(string id){
  sessions.erase(id);
}

bool is_session_valid(string id) {
  return sessions.count(id) == 1 ? true : false;
}
