#include "../grpc_proto/kv_store.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include "../include/controller.hpp"
#include <string>
#include <optional>
#include "../include/tablet_manager.hpp"

KV_Controller::KV_Controller()
{
}

KV_Controller::~KV_Controller()
{
}

bool KV_Controller::Put(const std::string &row, const std::string &column, const std::string &value)
{

    // Get right tablet:
    Tablet *tablet = Tablet_Manager::get_instance().get_tablet(row);
    // if tablet exists, store data in tablet
    if (tablet)
    {
        Tablet_Manager::get_instance().add_to_metatablet(row, tablet->get_tablet_id());
        // store data in tablet
        return tablet->Put(row, column, value);
    }
    return false;
}

std::optional<std::string> KV_Controller::Get(const std::string &row, const std::string &column)
{
    // TODO: Implement get logic
    Tablet *tablet = Tablet_Manager::get_instance().get_tablet(row);
    if (tablet)
    {
        return tablet->Get(row, column);
    }
    return "Data not found";
}

bool KV_Controller::Cput(const std::string &row, const std::string &column, const std::string &v1, const std::string &v2)
{
    // TODO: Implement cput logic
    Tablet *tablet = Tablet_Manager::get_instance().get_tablet(row);
    if (tablet)
    {
        return tablet->Cput(row, column, v1, v2);
    }
    return false;
}

bool KV_Controller::Delete(const std::string &row, const std::string &column)
{
    // TODO: Implement delete logic
    // 1. TODO: REMOVE DATA from memory (in memtable)
    Tablet *tablet = Tablet_Manager::get_instance().get_tablet(row);
    if (tablet)
    {
        return tablet->Delete(row, column);
    }
    return false;
}