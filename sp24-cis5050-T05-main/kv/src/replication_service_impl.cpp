#include "../include/replication_service_impl.hpp"

ReplicationServiceImpl::ReplicationServiceImpl(Replication_Coordinator &replication_coordinator, Checkpoint_Controller &checkpoint_controller) : replication_coordinator_(replication_coordinator), checkpoint_controller_(checkpoint_controller) {}

grpc::Status ReplicationServiceImpl::forwardTransaction(grpc::ServerContext *context, const replication::Transaction *request, replication::TransactionResponse *response)
{

    // Extract the transaction details from the request
    auto operation = request->operation();
    auto key = request->key();
    auto column = request->column();
    auto value = request->value();
    auto old_value = request->old_value();

    bool success;
    // Perform the replication according to the type of operation
    if (operation == replication::Operation::PUT)
    {
        // Perform the PUT operation
        std::cout << "Received PUT operation: " << key << " " << column << std::endl;
        success = controller_.Put(key, column, value);
    }
    else if (operation == replication::Operation::DELETE)
    {
        // Perform the DELETE operation
        std::cout << "Received DELETE operation: " << key << " " << column << std::endl;
        success = controller_.Delete(key, column);
    }
    else if (operation == replication::Operation::CPUT)
    {
        // Perform the CPUT operation
        std::cout << "Received CPUT operation: " << key << " " << column << std::endl;
        success = controller_.Cput(key, column, old_value, value);
    }
    else
    {
        // Invalid operation
        response->set_success(false);
        response->set_message("Invalid operation type.");
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Invalid operation type");
    }

    // If we are a primary node, forward the transaction to all subordinates otherwise return success
    if (replication_coordinator_.is_primary())
    {
        // Forward the transaction to all subordinates
        success = replication_coordinator_.forward_to_subordinates(key, column, old_value, value, operation);
        if (success)
        {
            checkpoint_controller_.increase_write_count();
        }
    }

    response->set_success(success);
    if (success)
    {
        response->set_message("Replication successful.");
        if (!replication_coordinator_.is_primary())
        {
            // increase the write count in the checkpoint controller
            checkpoint_controller_.increase_write_count();
        }
        return grpc::Status::OK;
    }
    else
    {
        response->set_message("Replication failed.");
        return grpc::Status(grpc::StatusCode::INTERNAL, "Replication operation failed");
    }
}
