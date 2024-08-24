// // NodeStatusManager.hpp

// #ifndef NODE_STATUS_MANAGER_HPP
// #define NODE_STATUS_MANAGER_HPP

// #include <string>
// #include <unordered_map>
// #include <mutex>

// class INodeStatusManager {
// public:
//     virtual ~INodeStatusManager() = default;
//     // Define common virtual methods that both managers will implement.
//     virtual void SetPrimary(std::string &address) = 0;
//     virtual void SetNodeStatus(const std::string& nodeAddress, const std::string& status) = 0;
//     virtual std::string GetNodeStatus(const std::string& nodeAddress);
//     virtual std::unordered_map<std::string, std::string> GetAllStatuses() = 0;
//     virtual void SetPrimary(std::string &address) = 0;
//     virtual std::string GetPrimary() = 0;
//     virtual bool isIn(const std::string& nodeAddress) = 0;
//     virtual void setUpMap(std::unordered_map<std::string, std::string> &map1) = 0;
//     virtual void showAllNodes() = 0;
// };


// class NodeStatusManager1 : public INodeStatusManager {
// public:
//     static NodeStatusManager1& GetInstance() {
//         static NodeStatusManager1 instance;
//         return instance;
//     }

//     NodeStatusManager1(const NodeStatusManager1&) = delete;
//     NodeStatusManager1& operator=(const NodeStatusManager1&) = delete;

//     // Methods to interact with node statuses
//     void SetNodeStatus(const std::string& nodeAddress, const std::string& status);
//     std::string GetNodeStatus(const std::string& nodeAddress);
//     std::unordered_map<std::string, std::string> GetAllStatuses();

//     void SetPrimary(std::string &address) override {
//         primary_address_ = address;
//     }

//     std::string GetPrimary() {
//         return primary_address_;
//     }

//     bool isIn(const std::string& nodeAddress) override;

//     void setUpMap(std::unordered_map<std::string, std::string> &map1) {
//         daemonMapToServer_ = map1;
//     }

//     std::string getServerFromDaemon(std::string &addr) override;

//     void showAllNodes() override;

// private:
//     NodeStatusManager1() {}  // Private constructor

//     std::unordered_map<std::string, std::string> nodeStatuses;
//     std::mutex mutex_;
//     std::unordered_map<std::string, int> rangeToId;
//     std::unordered_map<std::string, std::string> rangeIdToNode;

//     std::string primary_address_;
//     std::unordered_map<std::string, std::string> daemonMapToServer_;
// };

// class NodeStatusManager2 : public INodeStatusManager {
// public:
//     static NodeStatusManager2& GetInstance() {
//         static NodeStatusManager2 instance;
//         return instance;
//     }

//     NodeStatusManager2(const NodeStatusManager2&) = delete;
//     NodeStatusManager2& operator=(const NodeStatusManager2&) = delete;

//     // Methods to interact with node statuses
//     void SetNodeStatus override(const std::string& nodeAddress, const std::string& status);
//     std::string GetNodeStatus override(const std::string& nodeAddress);
//     std::unordered_map<std::string, std::string> GetAllStatuses override();

//     void SetPrimary(std::string &address) {
//         primary_address_ = address;
//     }

//     std::string GetPrimary() {
//         return primary_address_;
//     }

//     bool isIn(const std::string& nodeAddress) override;

//     void setUpMap(std::unordered_map<std::string, std::string> &map1) {
//         daemonMapToServer_ = map1;
//     }

//     std::string getServerFromDaemon(std::string &addr) override;

//     void showAllNodes();

// private:
//     NodeStatusManager2() {}  // Private constructor

//     std::unordered_map<std::string, std::string> nodeStatuses;
//     std::mutex mutex_;
//     std::unordered_map<std::string, int> rangeToId;
//     std::unordered_map<std::string, std::string> rangeIdToNode;

//     std::string primary_address_;
//     std::unordered_map<std::string, std::string> daemonMapToServer_;
// };
// #endif // NODE_STATUS_MANAGER_HPP


#ifndef NODE_STATUS_MANAGERS_HPP
#define NODE_STATUS_MANAGERS_HPP

#include <string>
#include <unordered_map>
#include <mutex>

// Interface defining the common functionalities for node status managers
class INodeStatusManager {
public:
    virtual ~INodeStatusManager() = default;

    virtual void SetNodeStatus(const std::string& nodeAddress, const std::string& status) = 0;
    virtual std::string GetNodeStatus(const std::string& nodeAddress) = 0;
    virtual std::unordered_map<std::string, std::string> GetAllStatuses() = 0;
    virtual void SetPrimary(const std::string& address) = 0;
    virtual std::string GetPrimary() = 0;
    virtual bool isIn(const std::string& nodeAddress) = 0;
    virtual void setUpMap(std::unordered_map<std::string, std::string>& map) = 0;
    virtual void showAllNodes() = 0;
    virtual std::string getServerFromDaemon(std::string &addr) = 0;
    virtual std::string GetRandomActiveNode() = 0;
};

// Concrete implementation for NodeStatusManager1
class NodeStatusManager1 : public INodeStatusManager {
public:
    static NodeStatusManager1& GetInstance() {
        static NodeStatusManager1 instance;
        return instance;
    }

    NodeStatusManager1(const NodeStatusManager1&) = delete;
    NodeStatusManager1& operator=(const NodeStatusManager1&) = delete;

    void SetNodeStatus(const std::string& nodeAddress, const std::string& status) override;
    std::string GetNodeStatus(const std::string& nodeAddress) override;
    std::unordered_map<std::string, std::string> GetAllStatuses() override;
    void SetPrimary(const std::string& address) override;
    std::string GetPrimary() override;
    bool isIn(const std::string& nodeAddress) override;
    void setUpMap(std::unordered_map<std::string, std::string>& map) override;
    void showAllNodes() override;
    std::string getServerFromDaemon(std::string &addr) override;
    std::string GetRandomActiveNode() override;


private:
    NodeStatusManager1() {}
    std::unordered_map<std::string, std::string> nodeStatuses;
    std::string primary_address_;
    std::mutex mutex_;
    std::unordered_map<std::string, std::string> daemonMapToServer_;
};

// Concrete implementation for NodeStatusManager2
class NodeStatusManager2 : public INodeStatusManager {
public:
    static NodeStatusManager2& GetInstance() {
        static NodeStatusManager2 instance;
        return instance;
    }

    NodeStatusManager2(const NodeStatusManager2&) = delete;
    NodeStatusManager2& operator=(const NodeStatusManager2&) = delete;

    void SetNodeStatus(const std::string& nodeAddress, const std::string& status) override;
    std::string GetNodeStatus(const std::string& nodeAddress) override;
    std::unordered_map<std::string, std::string> GetAllStatuses() override;
    void SetPrimary(const std::string& address) override;
    std::string GetPrimary() override;
    bool isIn(const std::string& nodeAddress) override;
    void setUpMap(std::unordered_map<std::string, std::string>& map) override;
    void showAllNodes() override;
    std::string getServerFromDaemon(std::string &addr) override;
    std::string GetRandomActiveNode() override;

private:
    NodeStatusManager2() {}
    std::unordered_map<std::string, std::string> nodeStatuses;
    std::string primary_address_;
    std::mutex mutex_;
    std::unordered_map<std::string, std::string> daemonMapToServer_;
};

#endif // NODE_STATUS_MANAGERS_HPP
