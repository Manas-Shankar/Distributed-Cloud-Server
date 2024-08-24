#ifndef TABLET_MANAGER_HPP
#define TABLET_MANAGER_HPP

#include <unordered_map>
#include <map>
#include "tablet.hpp"
#include <filesystem>
#include <fstream>

// Tablet manager manages the access to tablets and allows quick lookup of where to find which key.
// Implemented as a Singleton since we only want instance of the tablet manager.
class Tablet_Manager
{
public:
    // delete copy and assignment constructor to ensure we only have one instance of the tablet manager
    Tablet_Manager(const Tablet_Manager &) = delete;
    Tablet_Manager &operator=(const Tablet_Manager &) = delete;

    static Tablet_Manager &get_instance()
    {
        static Tablet_Manager instance;
        return instance;
    }

    void initialize(int group_number, int server_number);

    Tablet *get_tablet(const std::string &key);
    Tablet *get_tablet_by_id(int tablet_id);
    void update_in_memory_tablet(const int tablet_id);
    static int get_tablet_id_from_file(const std::string &file_path);
    void add_to_metatablet(const std::string &row_key, const int &tablet_id); // adds row key and tablet_id pair to metatable for tracking
    void set_in_memory_tablet_id(const int tablet_id);

    void partition_tablet(Tablet &tablet, std::string middle_key);

    // checkpointing operations
    void start_checkpointing(int64_t checkpoint_version_number_);
    int64_t get_checkpoint_version_number();
    std::vector<int64_t> get_log_line_numbers();
    std::map<std::string, std::string> get_logs(std::vector<int64_t> &log_line_numbers);
    void delete_all_outdated_tablet_files();
    std::vector<Tablet *> get_all_tablets();
    void add_tablet_from_checkpoint_file(const std::string &file_path, const std::string &starting_range);

    std::string get_server_path() const;
    std::string get_range_from_metadata_file(int tablet_id, std::ifstream &file);

private:
    Tablet_Manager();
    ~Tablet_Manager();
    void instantiate_tablets();
    Tablet &create_new_tablet(const std::string &starting_range); // TODO: For when we have to much data (data partitioning logic to be added later)

    // helper functions
    void storing_range_metadata_to_file(const std::string &row_key, const int &tablet_id); // storing metadata to a metadata file so we can

    std::unordered_map<std::string, int> meta_tablet_;             // stores which tablet each key is in (Key: Tablet) for quick lookup of the right table
    int max_tablet_id_;                                            // store current biggest tablet id so we can create the next biggest one
    std::mutex max_tablet_id_mutex_;                               // mutex to avoid race conditions when picking a new tablet id
    std::map<std::string, int> key_tablet_id_map_;                 // stores the starting key of the tablet range and maps it to the tablet_id
    std::unordered_map<int, std::unique_ptr<Tablet>> tablet_list_; // stores a map of all tablets by their tablet_id as the key
    int in_memory_tablet_id_;                                      // stores the tablet_id of the tablet that is currently in memory
    std::unique_ptr<std::fstream> metadata_file_stream_;           // stores the filestream to the metadata file (that stores which row can be found in which tablet)
    int group_number_;                                             // stores the group number of the server (used for locating the right disk folder)
    int server_number_;                                            // stores the server number of the server (used for locating the right disk folder)
};

#endif // TABLET_MANAGER_HPP