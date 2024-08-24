#ifndef KV_ADMIN_SERVICE_IMPL_HPP
#define KV_ADMIN_SERVICE_IMPL_HPP

#include "../grpc_proto/kv_admin_console.grpc.pb.h" //Relevant grpc header
#include <grpcpp/grpcpp.h>
#include <string>
#include <optional>

class AdminKVServiceImpl final : public admin::AdminKV::Service
{
public:
    AdminKVServiceImpl();
    grpc::Status GetAllKeyValuePairs(grpc::ServerContext *context, const admin::GetAllRequest *request, admin::GetAllResponse *response) override;

private:
};

#endif // KV_ADMIN_SERVICE_IMPL_HPP