
#include "../include/tablet.hpp"
#include <filesystem>
#include <fstream>
#include <cstdint>
#include "../include/tablet_manager.hpp"
#include <string>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <shared_mutex>
#include <vector>

Tablet::Tablet(const std::filesystem::path &file_path, const std::string &folder_path, const int &tablet_id) : in_memory_(false), size_(0), file_path_(file_path), log_file_stream_(nullptr),
                                                                                                               tablet_id_(tablet_id), checkpoint_interval_seconds_(1800), tablet_max_capacity_(200000000),
                                                                                                               folder_path_(folder_path)
{
    // init mutexes
    pthread_mutex_init(&sstable_mutex_, NULL);
    // start_checkpointing();
}

Tablet::~Tablet()
{
    // set checkpointing to false
    // stop_checkpointing();
    // flush to disk
    flush_memtable_to_disk();
    // TODO: Close all filestreams
    if (log_file_stream_)
        log_file_stream_->close();
}

bool Tablet::Put(const std::string &row, const std::string &column, const std::string &value)
{
    std::cout << "Tablet put" << std::endl;
    // check if node is already in memory and load it if not
    if (!in_memory_)
    {
        // update which node is in memory by flushing previous one and loading current one
        Tablet_Manager::get_instance().update_in_memory_tablet(tablet_id_);
    }
    // 1. TODO: Logging: Write put to Log file
    std::string operation{"PUT"};
    std::cout << "gonna write to log and store in memtable now" << std::endl;
    write_to_log(operation, row, column, value, "");
    // 2. TODO: STORE DATA in memory (in tablet)
    store_in_memtable(row, column, "", value);
    return true;
}

std::optional<std::string> Tablet::Get(const std::string &row, const std::string &column)
{
    // check if node is already in memory and load it if not
    if (!in_memory_)
    {
        // update which node is in memory by flushing previous one and loading current one
        Tablet_Manager::get_instance().update_in_memory_tablet(tablet_id_);
    }
    // retrieve data from in memory table
    if (memtable_.find(row) != memtable_.end())
    {
        if (memtable_[row].columns.find(column) != memtable_[row].columns.end())
        {
            return memtable_[row].columns[column];
        }
        std::cerr << "Column Key" << column << " not found" << std::endl;
        return std::nullopt;
    }
    std::cerr << "Row Key " << row << " not found" << std::endl;
    return std::nullopt;
}

bool Tablet::Cput(const std::string &row, const std::string &column, const std::string &v1, const std::string &v2)
{
    // check if node is already in memory and load it if not
    if (!in_memory_)
    {
        // update which node is in memory by flushing previous one and loading current one
        Tablet_Manager::get_instance().update_in_memory_tablet(tablet_id_);
    }
    // 1. TODO: Logging: Write Cput to Log file
    std::string operation{"CPUT"};
    std::cout << "gonna write to log and store in memtable now" << std::endl;
    write_to_log(operation, row, column, v1, v2);
    // 2. TODO: STORE DATA in memory (in tablet)
    if (memtable_.find(row) != memtable_.end() && memtable_[row].columns.find(column) != memtable_[row].columns.end() && memtable_[row].columns[column] == v1)
    {
        store_in_memtable(row, column, v1, v2);
        return true;
    }
    return false;
}

bool Tablet::Delete(const std::string &row, const std::string &column)
{
    // check if node is already in memory and load it if not
    if (!in_memory_)
    {
        // update which node is in memory by flushing previous one and loading current one
        Tablet_Manager::get_instance().update_in_memory_tablet(tablet_id_);
    }
    // Log operation to log file
    std::string operation{"DELETE"};
    write_to_log(operation, row, column, "", "");
    return delete_from_memtable(row, column);
}

void Tablet::write_to_log(const std::string &operation, const std::string &row, const std::string &column, const std::string &value1, const std::string &value2)
{
    std::cout << "Writing to log" << std::endl;
    // Open the log file stream
    std::string log_folder_path = folder_path_ + "/log_files";
    std::filesystem::path log_file_path = std::filesystem::path(log_folder_path) / ("wal_log_" + std::to_string(tablet_id_) + std::string(".txt"));

    if (!log_file_stream_)
    {
        log_file_stream_ = std::make_unique<std::ofstream>(log_file_path, std::ios::app);
        if (!log_file_stream_->is_open())
        {
            std::cerr << "Failed to open log file: " << log_file_path << std::endl;
            return;
        }
    }
    // check if log file exists:
    if (!std::filesystem::exists(log_file_path))
    {
        std::cout << "Log file at " << log_file_path << " doesn't exist" << std::endl;
    }
    // now write operation to log file
    std::cout << "Writing to log file: " << operation << ", " << row << ", " << column << std::endl;
    *log_file_stream_ << operation << ", " << row << ", " << column;
    if (operation == "PUT" || operation == "CPUT")
    {
        std::cout << "Writing to log file: " << std::endl;
        *log_file_stream_ << ", " << value1;
        if (operation == "CPUT")
        {
            std::cout << "Writing to log file stream" << std::endl;
            *log_file_stream_ << ", " << value2;
        }
    }
    *log_file_stream_ << std::endl;
    log_file_stream_->flush();
}

// helper function to trim string
void Tablet::trim(std::string &str)
{
    str.erase(0, str.find_first_not_of(" \n\r\t"));
    str.erase(str.find_last_not_of(" \n\r\t") + 1);
}

void Tablet::recover_from_logs()
{
    // Open the log file stream
    std::string log_folder_path = folder_path_ + "/log_files";
    std::filesystem::path log_file_path = std::filesystem::path(log_folder_path) / ("wal_log_" + std::to_string(tablet_id_) + std::string(".txt"));

    std::cout << "Attempting to recover from logs at: " << log_file_path << std::endl;
    // if the file doesn't exist just return without doing anything
    if (!std::filesystem::exists(log_file_path))
    {
        std::cout << "No Logs available for " << std::to_string(tablet_id_) << std::endl;
        return;
    }

    // open the log file stream
    std::ifstream log_file_stream;
    log_file_stream.open(log_file_path, std::ifstream::in);

    if (!log_file_stream.is_open())
    {
        std::cerr << "Failed to open log file: " << log_file_path << std::endl;
        return;
    }

    // now loop through each logged action and perform the action on the memtable
    std::string line;

    while (std::getline(log_file_stream, line))
    {
        std::istringstream iss(line);
        apply_logs_to_memtable(iss);
    }
    // store recovered memtable to disk
    // flush_memtable_to_disk();
    // delete logs after having recovered from them
    // delete_logs();
}

void Tablet::apply_logs_to_memtable(std::istringstream &log_line)
{
    std::string operation, row, column, value1, value2;

    // Get operation, row, and column and trim them from whitespaces
    std::getline(log_line, operation, ',');
    std::getline(log_line, row, ',');
    std::getline(log_line, column, ',');
    trim(operation);
    trim(row);
    trim(column);
    std::cout << "operation: " << operation << ", row: " << row << ", column: " << column << std::endl;
    if (operation == "PUT")
    {
        std::getline(log_line, value1);
        trim(value1);
        // std::cout << "value1: " << value1 << std::endl;
        // lock row before updating it
        store_in_memtable(row, column, "", value1);
    }
    else if (operation == "CPUT")
    {
        std::getline(log_line, value1, ',');
        std::getline(log_line, value2);
        trim(value1);
        // std::cout << "value1: " << value1 << ", value2: " << value2 << std::endl;
        // lock before reading and changing it
        store_in_memtable(row, column, value1, value2);
    }
    else if (operation == "DELETE")
    {
        delete_from_memtable(row, column);
    }
}

void Tablet::delete_logs()
{
    // create path of log file we want to delete:
    std::string log_path = folder_path_ + std::string("/log_files/wal_log_") + std::to_string(tablet_id_) + std::string(".txt");

    // delete logs from file from folder or throw error if not possible:
    std::ofstream file(log_path, std::ios::trunc);
    if (file)
    {
        file.close();
        std::cout << "Log file " << log_path << " cleared" << std::endl;
    }
    else
    {
        std::cerr << "Error: Couldn't clear log file since path wasnt found: " << log_path << std::endl;
    }
    /*try
    {
        if (std::filesystem::remove(log_path))
        {
            std::cout << "Log file " << log_path << " deleted" << std::endl;
        }
        else
        {
            std::cout << "Log file " << log_path << " wasn't found" << std::endl;
        }
    }
    catch (std::filesystem::filesystem_error &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }*/
}

void Tablet::store_in_memtable(const std::string &row, const std::string &column, const std::string &oldvalue, const std::string &value)
{
    std::cout << "Storing data in memtable" << std::endl;
    // lock the current row
    std::unique_lock<std::shared_mutex> lock(memtable_[row].row_mutex);

    // if old value exists and is not the same as what is there we don't store it
    if (oldvalue != "" && memtable_[row].columns[column] != oldvalue)
    {
        std::cerr << "Old value doesn't match the value in the memtable" << std::endl;
        return;
    }

    long int size_change = 0;
    // if the column doesn't exist add the space for the column key and the size encodings for column key and value
    if (memtable_[row].columns.find(column) == memtable_[row].columns.end())
    {
        size_change += (sizeof(uint32_t) * 2) + column.length();
        size_change += value.length();
    }
    else
    {
        // if we are just updating the value add the difference between the old and new value
        size_change += value.length() - memtable_[row].columns[column].length();
    }

    // if row key not in memtable yet add it to the ordered_keys:
    if (ordered_keys_.find(row) == ordered_keys_.end())
        ordered_keys_.insert(row);
    // store value at row and column given
    memtable_[row].columns[column] = value;
    // update the row size and tablet size
    update_row_size(memtable_[row], size_change);
    // unlocking unique lock for current row
    lock.unlock();

    std::cout << "size of tablet: " << size_ << std::endl;
    // check if partition is required
    if (size_ > tablet_max_capacity_)
    {
        // first flush the memtable
        std::string middle_key = flush_memtable_to_disk();
        // then partition it into two from the Tablet Manager
        Tablet_Manager::get_instance().partition_tablet(*this, middle_key);
    }
}

bool Tablet::delete_from_memtable(const std::string &row, const std::string &column)
{
    // use shared lock so we don't delete one row during flushing
    // std::shared_lock<std::shared_mutex> memtable_lock(memtable_mutex_);
    // Delete from Memtable
    if (memtable_.find(row) != memtable_.end())
    {
        // lock row before checking if column exists and deleting it from row
        std::unique_lock<std::shared_mutex> row_lock(memtable_[row].row_mutex);
        if (memtable_[row].columns.find(column) != memtable_[row].columns.end())
        {
            long int size_change = (column.length() + (2 * sizeof(uint32_t)) + memtable_[row].columns[column].length()) * -1;
            memtable_[row].columns.erase(column);
            update_row_size(memtable_[row], size_change);
            return true;
        }
        std::cerr << "Column Key" << column << " not found" << std::endl;
        return false;
    }
    return false;
}

void Tablet::load_into_memory()
{
    std::cout << "Loading tablet into Memory" << std::endl;
    // lock memtable mutex until we have fully restored the memtable including the recovery from the logs
    std::unique_lock<std::shared_mutex> memtable_lock(memtable_mutex_);
    // lock mutex for SStable
    pthread_mutex_lock(&sstable_mutex_);
    std::cout << "Acquired sstable mutex lock" << std::endl;
    std::ifstream file(file_path_, std::ios::binary);
    if (!file)
    {
        std::cerr << "Cannot open tablet file!" << std::endl;
        pthread_mutex_unlock(&sstable_mutex_);
        return;
    }

    size_t file_position = 0;
    // reset tablet size to 0 so we can recount it:
    size_ = 0;
    std::cout << "Starting the load process" << std::endl;
    while (file.peek() != EOF)
    {
        size_t row_size = 0;
        // reading in the row key
        uint32_t row_key_len;
        row_size += sizeof(row_key_len);
        // TODO: Update size whenever reading in data
        file.read(reinterpret_cast<char *>(&row_key_len), sizeof(row_key_len));
        std::vector<char> row_key_chars(row_key_len);
        file.read(row_key_chars.data(), row_key_len);
        std::string row_key(row_key_chars.begin(), row_key_chars.end());
        row_size += row_key.length();

        // reading in the number of columns in the row:
        uint32_t num_cols;
        row_size += sizeof(row_key_len);
        file.read(reinterpret_cast<char *>(&num_cols), sizeof(num_cols));

        std::unordered_map<std::string, std::string> columns_map;
        // read in all the column: value pairs:
        for (uint32_t i = 0; i < num_cols; ++i)
        {
            // read in the column key
            uint32_t col_key_len;
            row_size += sizeof(col_key_len);
            file.read(reinterpret_cast<char *>(&col_key_len), sizeof(col_key_len));
            std::vector<char> col_key_chars(col_key_len);
            file.read(col_key_chars.data(), col_key_len);
            std::string col_key(col_key_chars.begin(), col_key_chars.end());
            row_size += col_key.length();

            // read the value at row:col:
            uint32_t value_len;
            row_size += sizeof(value_len);
            file.read(reinterpret_cast<char *>(&value_len), sizeof(value_len));
            std::vector<char> value_chars(value_len);
            file.read(value_chars.data(), value_len);
            std::string value(value_chars.begin(), value_chars.end());
            row_size += value.length();
            // std::cout << "Loading from disk: " << col_key << ": " << value << std::endl;
            // store value in our memtable:
            columns_map.emplace(col_key, value);
        }
        // construct a Row_data struct to emplace into memtable
        Row_Data row_data(columns_map);
        // update the bytes size with the size of the entire row in disk (including size encodings)
        row_data.bytes_size = row_size;
        // update Tablet size
        size_ += row_size;
        // update the starting position of the row with the file position from last iteration
        row_data.position = file_position;
        // update file positition to get start position for next Row_DATA
        file_position += row_size;
        // store row data in memtable
        memtable_.emplace(row_key, row_data);
        // store key in ordered_keys
        ordered_keys_.insert(row_key);
    }
    // set in_memory_ attribute to true
    in_memory_ = true;

    // unlock SSTable
    pthread_mutex_unlock(&sstable_mutex_);
    std::cout << "UnLocked SSTable Mutex lock" << std::endl;
    // also update with logs if there are any logs available
    // TODO: Fix potential race conditions where sstable mutex gets unlocked and then acquired by another thread (also potential race conditions on memtable)
    recover_from_logs();
}

std::string Tablet::flush_memtable_to_disk()
{
    std::cout << "Flushing to disk" << std::endl;
    // TODO: Lock Memtable and Disk during flushing
    pthread_mutex_lock(&sstable_mutex_);
    std::cout << "Locked SSTable" << std::endl;
    std::ofstream file(file_path_, std::ios::binary | std::ios::trunc);
    if (!file)
    {
        std::cerr << "Cannot open tablet file for writing!" << std::endl;
        pthread_mutex_unlock(&sstable_mutex_);
        exit(EXIT_FAILURE);
    }

    size_t file_position = 0;
    std::string middle_key;
    bool middle_found = false;
    std::cout << "Ordered keys size: " << ordered_keys_.size() << std::endl;
    for (const auto &row_key : ordered_keys_)
    {
        size_t row_size = 0;
        Row_Data &row_data = memtable_[row_key];
        // Writing the row key
        uint32_t row_key_len = static_cast<uint32_t>(row_key.size());
        file.write(reinterpret_cast<const char *>(&row_key_len), sizeof(row_key_len));
        file.write(row_key.data(), row_key.size());
        row_size += sizeof(row_key_len) + row_key.length();

        // Writing the number of columns
        uint32_t num_cols = static_cast<uint32_t>(row_data.columns.size());
        file.write(reinterpret_cast<const char *>(&num_cols), sizeof(num_cols));
        row_size += sizeof(num_cols);

        for (const auto &[col_key, value] : row_data.columns)
        {
            // Writing the column key
            // std::cout << "Writing to disk: " << col_key << ": " << value << std::endl;
            uint32_t col_key_len = static_cast<uint32_t>(col_key.size());
            file.write(reinterpret_cast<const char *>(&col_key_len), sizeof(col_key_len));
            file.write(col_key.data(), col_key.size());
            row_size += sizeof(col_key_len) + col_key.length();

            // Writing the value
            uint32_t value_len = static_cast<uint32_t>(value.size());
            file.write(reinterpret_cast<const char *>(&value_len), sizeof(value_len));
            file.write(value.data(), value.size());
            row_size += sizeof(value_len) + value.length();
        }
        // update the starting position of the row with the file position from last iteration
        row_data.position = file_position;
        // update file positition to get start position for next Row_DATA
        file_position += row_size;
        // check if we have reached crossed the middle of the file and if yes store the position to return later
        // std::cout << "row position: " << row_data.position << std::endl;
        if (row_data.position >= (tablet_max_capacity_ / 2) && !middle_found)
        {
            std::cout << "Middle key found: " << row_key << std::endl;
            middle_found = true;
            middle_key = row_key;
        }
    }

    file.close(); // Ensure the file is closed after writing
    if (!file.good())
    {
        std::cerr << "Error occurred at writing time!" << std::endl;
    }
    pthread_mutex_unlock(&sstable_mutex_);
    std::cout << "Unlocked SSTable" << std::endl;
    return middle_key;
}

bool Tablet::is_in_memory()
{
    return in_memory_;
}

// New checkpointing implementation: Based on centralized checkpointing and initiated by the Checkpointing controller
void Tablet::start_checkpointing(int64_t checkpoint_version_number)
{
    // flush memtable to disk
    flush_and_clear_memtable();
    // delete logs since all changes have been flushed to memory
    delete_logs();

    // change name of tablet file with new checkpoint version number
    int pos = file_path_.string().find_last_of("_") + 1;
    std::string file_name = file_path_.string().substr(0, pos);
    std::string checkpointed_file_path = file_name + std::to_string(checkpoint_version_number);
    if (rename(file_path_.c_str(), checkpointed_file_path.c_str()) != 0)
    {
        std::cerr << "Error renaming file" << std::endl;
        exit(EXIT_FAILURE);
    }
    file_path_ = checkpointed_file_path;
}

// Old local checkpointing implementation
/*
void Tablet::start_checkpointing()
{
    // TODO: Implement checkpointing on command (not timout based)
    checkpoint_active_ = true;
    // start checkpointing in separate thread
    pthread_create(&checkpointing_thread_, nullptr, &Tablet::checkpointing_thread, this);
    pthread_detach(checkpointing_thread_);
}

void *Tablet::checkpointing_thread(void *arg)
{
    Tablet *tablet = static_cast<Tablet *>(arg);
    tablet->checkpointing_loop();
    return NULL;
}

void Tablet::checkpointing_loop()
{
    while (checkpoint_active_)
    {
        sleep(checkpoint_interval_seconds_);
        std::cout << "Checkpointing data to disk" << std::endl;
        flush_memtable_to_disk();
    }
}

void Tablet::stop_checkpointing()
{

    if (checkpoint_active_ && checkpointing_thread_)
    {
        checkpoint_active_ = false;
        pthread_join(checkpointing_thread_, nullptr);
    }
}*/

int Tablet::get_tablet_id()
{
    return tablet_id_;
}

void Tablet::flush_and_clear_memtable()
{
    // lock memtable so nobody can change it while it's being
    std::unique_lock<std::shared_mutex> memtable_lock(memtable_mutex_);
    std::cout << "Flushing and clearing memtable of id: " << tablet_id_ << std::endl;
    // first flush memtable to disk to make sure we have a copy
    flush_memtable_to_disk();
    // then clear it from memory
    remove_from_in_memory();
}

void Tablet::remove_from_in_memory()
{
    memtable_.clear();
    in_memory_ = false;
    Tablet_Manager::get_instance().set_in_memory_tablet_id(-1);
}

void Tablet::update_row_size(Row_Data &row_data, long int size_change)
{
    // first update row size
    row_data.bytes_size += size_change;
    // then update overall tablet size
    size_ += size_change;
}

void Tablet::copy_from_old_tablet(Tablet &old_tablet, std::string middle_key)
{
    std::cout << "Copying from old tablet" << std::endl;
    // find the middle key in the old tablet
    auto key_it = old_tablet.ordered_keys_.find(middle_key);
    pthread_mutex_lock(&sstable_mutex_);
    std::cout << "Locked SSTable" << std::endl;
    std::ofstream file(file_path_, std::ios::binary | std::ios::trunc);
    if (!file)
    {
        std::cerr << "Cannot open tablet file for writing!" << std::endl;
        pthread_mutex_unlock(&sstable_mutex_);
        return;
    }

    size_t file_position = 0;
    // copy from middle key to end of old tablet to new tablet
    for (auto it = key_it; it != old_tablet.ordered_keys_.end(); it++)
    {
        size_t row_size = 0;
        Row_Data &row_data = old_tablet.memtable_[*it];
        // Writing the row key
        uint32_t row_key_len = static_cast<uint32_t>(it->size());
        file.write(reinterpret_cast<const char *>(&row_key_len), sizeof(row_key_len));
        file.write(it->data(), it->size());
        row_size += sizeof(row_key_len) + it->length();

        // Writing the number of columns
        uint32_t num_cols = static_cast<uint32_t>(row_data.columns.size());
        file.write(reinterpret_cast<const char *>(&num_cols), sizeof(num_cols));
        row_size += sizeof(num_cols);

        for (const auto &[col_key, value] : row_data.columns)
        {
            // Writing the column key
            // std::cout << "Writing to disk: " << col_key << ": " << value << std::endl;
            uint32_t col_key_len = static_cast<uint32_t>(col_key.size());
            file.write(reinterpret_cast<const char *>(&col_key_len), sizeof(col_key_len));
            file.write(col_key.data(), col_key.size());
            row_size += sizeof(col_key_len) + col_key.length();

            // Writing the value
            uint32_t value_len = static_cast<uint32_t>(value.size());
            file.write(reinterpret_cast<const char *>(&value_len), sizeof(value_len));
            file.write(value.data(), value.size());
            row_size += sizeof(value_len) + value.length();
        }
        // update the starting position of the row with the file position from last iteration
        row_data.position = file_position;
        // update file positition and tablet size to get start position for next Row_DATA
        file_position += row_size;
        size_ += row_size;
    }

    file.close(); // Ensure the file is closed after writing
    if (!file.good())
    {
        std::cerr << "Error occurred at writing time!" << std::endl;
    }
    pthread_mutex_unlock(&sstable_mutex_);
    std::cout << "Unlocked SSTable" << std::endl;
    std::cout << "Finished copying from old tablet. Size of new tablet: " << size_ << std::endl;
}

void Tablet::remove_partitioned_data(const std::string &middle_key)
{
    std::cout << "Removing partitioned data" << std::endl;
    // find the middle key in the old tablet
    auto key_it = ordered_keys_.find(middle_key);
    // remove all data from middle key to end of tablet from memtable
    for (auto it = key_it; it != ordered_keys_.end(); it++)
    {
        memtable_.erase(*it);
    }
    // remove all keys from middle key to end of tablet
    ordered_keys_.erase(key_it, ordered_keys_.end());
    // update size of tablet
    size_ = 0;
    for (const auto &row_key : ordered_keys_)
    {
        size_ += memtable_[row_key].bytes_size;
    }
    std::cout << "Size of old tablet after partitioning: " << size_ << std::endl;
    // flush the memtable to disk
    flush_memtable_to_disk();
}

std::string Tablet::get_file_path()
{
    return file_path_;
}

void Tablet::update_file_path(std::string file_path)
{
    file_path_ = file_path;
}