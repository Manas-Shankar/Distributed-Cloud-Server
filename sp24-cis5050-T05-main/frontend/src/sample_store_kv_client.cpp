#include "../grpc_proto/kv_grpc_proto/kv_store.grpc.pb.h"
#include "../grpc_proto/kv_grpc_proto/backend_master_as_server.grpc.pb.h" //CHANGED


#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <grpc++/grpc++.h>
#include <grpcpp/grpcpp.h>

#include "../include/constants.h"
#include "../include/request.h"
#include "../include/response.h"
#include "../include/store.h"
#include "../include/utils.h"
#include "../include/sample_store_kv_client.h"

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

pair<string, string> kvClient::getFromKv(string r, string c){
  	GetRequest req;

      req.set_row(r);
      req.set_column(c);

      GetResponse res;

         ClientContext context;

         Status status = stub_->Get(&context, req, &res);

         cout << "size of response from GET " << res.value().size() << endl;

         if(status.ok()){
             return make_pair(res.value(), "success !");
         } else {
             cout << status.error_code() << ": " << status.error_message() << endl;
             return make_pair("", status.error_message());
         }
}

string kvClient::deleteFromKv(string r, string c){
  	DeleteRequest req;

      req.set_row(r);
      req.set_column(c);

      DeleteResponse res;

         ClientContext context;

         Status status = stub_->Delete(&context, req, &res);

         if(status.ok()){
             return "success !";
         } else {
             cout << status.error_code() << ": " << status.error_message() << endl;
             return status.error_message();
         }
}

bool kvClient::putToKv(string r, string c, string value) {
    	PutRequest req;

    	req.set_row(r);
    	req.set_column(c);
    	req.set_value(value);

        PutResponse res;

        ClientContext context;

        Status status = stub_->Put(&context, req, &res);

        if(status.ok()){
            return res.success();
        } else {
            cout << status.error_code() << ": " << status.error_message() << std::endl;
            return 0;
        }
}

string kvClient::getNodeAddress(string key) {
    GetNodeAddressRequest req;
    GetNodeAddressResponse res;

    req.set_key(key);

    ClientContext context;

    Status status = backendStub_->GetNodeAddress(&context, req, &res);

    if (status.ok()) {
        return res.address();
    } else {
        cout << "error message:" << status.error_code() << ": " << status.error_message() << endl;
        return status.error_message();
    }
}
