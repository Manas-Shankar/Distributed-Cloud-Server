// Create Tablet structure to store

#ifndef TABLET_HPP
#define TABLET_HPP

#include <string>
#include <optional>
#include <unordered_map>
#include <iostream>
#include <filesystem>
#include <atomic>
#include <shared_mutex>
#include <set>

struct Row_Data
{
    // std::unordered_map<std::string, std::string> columns;
    std::unordered_map<std::string, std::string> columns;
    mutable std::shared_mutex row_mutex;
    size_t bytes_size = 0; // stores size in bytes of all column keys and values in the row (excluding row key size)
    size_t position;       // stores the position of the row within the tablet

    Row_Data() = default;
    Row_Data(std::unordered_map<std::string, std::string> columns_input) : columns(std::move(columns_input)) {}

    // copy constructor
    Row_Data(const Row_Data &other) : columns(other.columns)
    {
    }

    // Move constructor
    Row_Data(Row_Data &&other) noexcept : columns(std::move(other.columns))
    {
    }
};

class Tablet
{
public:
    Tablet(const std::filesystem::path &file_path, const std::string &folder_path, const int &tablet_id);
    ~Tablet();

    // basic Database operations
    bool Put(const std::string &row, const std::string &column, const std::string &value);
    std::optional<std::string> Get(const std::string &row, const std::string &column);
    bool Cput(const std::string &row, const std::string &column, const std::string &v1, const std::string &v2);
    bool Delete(const std::string &row, const std::string &column);

    // basic helper functions
    bool is_in_memory();
    int get_tablet_id();
    void flush_and_clear_memtable(); // first flushes to disk and then clears memtable

    // Checkpointing operations
    void load_into_memory();
    std::string flush_memtable_to_disk();
    void start_checkpointing(int64_t checkpoint_version_number);
    // void stop_checkpointing();
    // static void *checkpointing_thread(void *arg);
    // void checkpointing_loop();
    void apply_logs_to_memtable(std::istringstream &log_line);

    // Partitioning operations
    void copy_from_old_tablet(Tablet &old_tablet, std::string middle_key);
    void remove_partitioned_data(const std::string &middle_key);

    // recovery operations
    std::string get_file_path();
    void update_file_path(std::string file_path);

    std::unordered_map<std::string, Row_Data> memtable_; // memtable where we store user data in memory
    std::set<std::string> ordered_keys_;                 // store row keys in order so we know what

private:
    // LOG Operations
    void write_to_log(const std::string &operation, const std::string &row, const std::string &column, const std::string &value1, const std::string &value2);
    void store_in_memtable(const std::string &row, const std::string &column, const std::string &oldvalue, const std::string &value);
    bool delete_from_memtable(const std::string &row, const std::string &column);
    void delete_logs();       // delete logs after checkpointing or after recovering from logs
    void recover_from_logs(); // recover from logs if there is a log file stored

    // Helper functions:
    void trim(std::string &str);
    // DANGER: only use after having flushed memtable to disk!!! (deletes memtable)
    void remove_from_in_memory();

    // Partitioning:
    void update_row_size(Row_Data &row_data, long int size_change);

    bool in_memory_;                                 // boolean to track if the tablet is currently in memory
    unsigned long size_;                             // size of tablet in BYTES
    std::filesystem::path file_path_;                // Store filepath of on disk tablet (SSTablet)
    std::unique_ptr<std::ofstream> log_file_stream_; // Pointer Log file to log operations
    std::string log_file_path_;                      // path storing where the log file is stored
    int tablet_id_;                                  // tablet id
    std::atomic<bool> checkpoint_active_;            // atomic variable to tell checkpointing function wether to continue running
    int checkpoint_interval_seconds_;                // checkpointing interval (in seconds) defining how often we checkpoint in memory to disk
    std::shared_mutex memtable_mutex_;               // Mutex to protect access to the memtable
    pthread_mutex_t sstable_mutex_;                  // Mutex to protect access to the SSTable for the current tablet
    pthread_t checkpointing_thread_;                 // thread running the checkpoint loop for periodic checkpointing
    int tablet_max_capacity_;                        // max capacity of tablet in bytes
    const std::string folder_path_;                  // stores the folder path of the tablet
};

#endif // TABLET_HPP