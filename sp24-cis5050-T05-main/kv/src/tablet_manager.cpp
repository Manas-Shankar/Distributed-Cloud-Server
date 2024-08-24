#include <unordered_map>
#include "../include/tablet.hpp"
#include "../include/tablet_manager.hpp"
#include <iostream>
#include <filesystem>
#include <sstream>

Tablet_Manager::Tablet_Manager() : max_tablet_id_(0), in_memory_tablet_id_(-1), metadata_file_stream_(nullptr)
{
}

Tablet_Manager::~Tablet_Manager()
{
    if (!metadata_file_stream_)
    {
        metadata_file_stream_->close();
    }
}

void Tablet_Manager::initialize(int group_number, int server_number)
{
    group_number_ = group_number;
    server_number_ = server_number;
    instantiate_tablets();
}

Tablet *Tablet_Manager::get_tablet(const std::string &key)
{
    // return first tablet if only one tablet exists
    if (key_tablet_id_map_.size() == 1)
    {
        std::cout << "Only one tablet exists. Returning tablet 1" << std::endl;
        return tablet_list_.begin()->second.get();
    }
    // find the first element bigger than current key
    auto it = key_tablet_id_map_.upper_bound(key);
    // iterate backwards to find the last element smaller than current key
    --it;
    // get tablet id from iterator
    const int &tablet_id = it->second;
    // update_in_memory_tablet(tablet_id);
    std::cout << "Row Key " << key << " can be found in " << "Tablet ID: " << tablet_id << " with range " << it->first << std::endl;
    return tablet_list_[tablet_id].get();
}

void Tablet_Manager::add_to_metatablet(const std::string &row_key, const int &tablet_id)
{
    meta_tablet_[row_key] = tablet_id;
}

void Tablet_Manager::instantiate_tablets()
{
    // create the folder path for the tablets
    std::string folder_path = "data/g" + std::to_string(group_number_) + "_" + "r" + std::to_string(server_number_);
    std::string dir_path = folder_path + "/tablets/";
    // setup for extracting metadata
    std::string path = folder_path + "/metadata.txt";
    std::filesystem::path metadata_file_path = path;
    // Open the metadata file
    std::ifstream metadata_file(metadata_file_path);
    for (const auto &file : std::filesystem::directory_iterator(dir_path))
    {
        if (file.is_regular_file())
        {
            int tablet_id = get_tablet_id_from_file(file.path().filename().string());
            // update max_tablet_id_ if necessary
            max_tablet_id_ = std::max(max_tablet_id_, tablet_id);
            tablet_list_.emplace(tablet_id, std::make_unique<Tablet>(file.path(), folder_path, tablet_id));
            if (!tablet_list_[tablet_id])
            {
                perror("Error adding tablet to the Tablet Manager");
            }
            // load in the tablet range from metadata file and store it in key tablet id map
            key_tablet_id_map_[get_range_from_metadata_file(tablet_id, metadata_file)] = tablet_id;
            std::cout << "Created tablet #" << tablet_id << "from path " << file.path().string() << std::endl;
        }
    }
}

std::string Tablet_Manager::get_range_from_metadata_file(int tablet_id, std::ifstream &file)
{
    if (!file.is_open())
    {
        std::cerr << "Failed to open the metadata file" << std::endl;
        return ""; // or throw an exception
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        int id;
        char colon;
        std::string value;

        // Read the tablet id and the colon
        if (!(iss >> id >> colon))
        {
            std::cerr << "Parsing error: could not read tablet id and colon." << std::endl;
            continue;
        }

        // Check if the current line's tablet id matches the requested tablet id
        if (id == tablet_id)
        {
            // Extract the starting range for the tablet
            std::getline(iss, value);
            return value;
        }
    }

    std::cerr << "Tablet id " << tablet_id << " not found in the metadata file." << std::endl;
    return "";
}

void Tablet_Manager::storing_range_metadata_to_file(const std::string &row_key, const int &tablet_id)
{
    // TODO: Store to meta_data tablet file
    std::cout << "Writing to Metatablet" << std::endl;
    // Open the log file stream
    std::string path = "data/g" + std::to_string(group_number_) + "_" + "r" + std::to_string(server_number_) + "/metadata.txt";
    std::filesystem::path metadata_file_path = path;
    if (!metadata_file_stream_)
    {
        metadata_file_stream_ = std::make_unique<std::fstream>(metadata_file_path, std::ios::in | std::ios::out | std::ios::app);
        if (!metadata_file_stream_->is_open())
        {
            std::cerr << "Failed to open metadata file: " << metadata_file_path << std::endl;
            return;
        }
    }
    // check if log file exists:
    if (!std::filesystem::exists(metadata_file_path))
    {
        std::cout << "Metadata file at " << metadata_file_path << " doesn't exist" << std::endl;
    }
    // now write operation to log file
    std::cout << "Writing to Metadata file:" << row_key << ": " << tablet_id << std::endl;
    *metadata_file_stream_ << tablet_id << ":" << row_key << "\n";
    metadata_file_stream_->flush();
}

int Tablet_Manager::get_tablet_id_from_file(const std::string &file_path)
{
    int pos = file_path.find('_');
    if (pos == std::string::npos)
    {
        std::cerr << "Tablet doesn't follow naming convention tablet_<id> so tablet id can't be parsed" << std::endl;
    }
    int tablet_id = stoi(file_path.substr(pos + 1));
    return tablet_id;
}

void Tablet_Manager::update_in_memory_tablet(const int tablet_id)
{
    std::cout << "Updating Memory in tablet" << std::endl;
    if (tablet_id == in_memory_tablet_id_)
    {
        std::cout << "data already in memory" << std::endl;
        return;
    }
    // flush previous in memory tablet onto disk (if it is in memory already)
    if (in_memory_tablet_id_ != -1)
    {
        // lock the memtable so nobody else can write to it whilst we flush it to disk and then clear it from memory
        tablet_list_[in_memory_tablet_id_].get()->flush_and_clear_memtable();
    }

    // load new tablet into memory if not in memory yet
    if (!tablet_list_[tablet_id].get()->is_in_memory())
    {
        tablet_list_[tablet_id].get()->load_into_memory();
    }
    set_in_memory_tablet_id(tablet_id);
}

void Tablet_Manager::set_in_memory_tablet_id(const int tablet_id)
{
    in_memory_tablet_id_ = tablet_id;
}

void Tablet_Manager::partition_tablet(Tablet &tablet, std::string middle_key)
{
    std::cout << "Partitioning tablet at middle key: " << middle_key << std::endl;
    // create new tablet and file
    Tablet &new_tablet = create_new_tablet(middle_key);
    // write from old memtablet into new one
    new_tablet.copy_from_old_tablet(tablet, middle_key);
    // delete second half from first tablet
    tablet.remove_partitioned_data(middle_key);
}

// copy from old memtabl to new memtable disk during partitioning

Tablet &Tablet_Manager::create_new_tablet(const std::string &starting_range)
{
    // lock max max_tablet_id_mutex_ first to avoid race conditions
    std::unique_lock<std::mutex> max_tablet_id_lock(max_tablet_id_mutex_);
    // pick tablet id and increment max_tablet_id_
    int new_tablet_id = ++max_tablet_id_;
    // create the folder path for the new tablet
    std::string folder_path = "data/g" + std::to_string(group_number_) + "_" + "r" + std::to_string(server_number_);
    // create file path for tablet_id
    std::filesystem::path file_path = folder_path + "/tablets/tablet_" + std::to_string(new_tablet_id) + ".bytes";
    std::cout << "Creating new tablet: " << file_path << std::endl;
    // create and store new tablet
    tablet_list_.emplace(new_tablet_id, std::make_unique<Tablet>(file_path, folder_path, new_tablet_id));
    key_tablet_id_map_[starting_range] = new_tablet_id;
    // TODO: Store starting range in metadata file
    storing_range_metadata_to_file(starting_range, new_tablet_id);
    return *tablet_list_[new_tablet_id];
}

void Tablet_Manager::start_checkpointing(int64_t checkpoint_version_number_)
{
    // get the tablet that is currently in memory
    get_tablet(std::to_string(in_memory_tablet_id_));
    Tablet &tablet = *tablet_list_[in_memory_tablet_id_];
    // start checkpointing
    tablet.start_checkpointing(checkpoint_version_number_);
}

int64_t Tablet_Manager::get_checkpoint_version_number()
{
    int64_t checkpoint_version_number;
    std::string folder_path = "data/g" + std::to_string(group_number_) + "_" + "r" + std::to_string(server_number_) + "/tablets/";
    std::cout << "folder path: " << folder_path << std::endl;
    // read the latest checkpoint version number from the first filename in folder_path
    if (std::filesystem::is_directory(folder_path))
    {
        for (const auto &entry : std::filesystem::directory_iterator(folder_path))
        {
            std::string filename = entry.path().filename().string();
            int pos = filename.find_last_of('_');
            checkpoint_version_number = stoi(filename.substr(pos + 1));
            break;
        }
    }
    else
    {
        std::cerr << "Error: Directory does not exist" << std::endl;
    }
    return checkpoint_version_number;
}

std::vector<int64_t> Tablet_Manager::get_log_line_numbers()
{
    std::vector<int64_t> log_line_numbers;
    std::string folder_path = "data/g" + std::to_string(group_number_) + "_" + "r" + std::to_string(server_number_) + "/log_files/";
    // read the number of lines in each log file from the filenames in folder_path
    if (std::filesystem::is_directory(folder_path))
    {
        for (const auto &entry : std::filesystem::directory_iterator(folder_path))
        {
            std::ifstream file(entry.path());
            int64_t line_count = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
            log_line_numbers.push_back(line_count);
        }
    }
    else
    {
        std::cerr << "Error: Directory does not exist" << std::endl;
    }
    return log_line_numbers;
}

std::map<std::string, std::string> Tablet_Manager::get_logs(std::vector<int64_t> &log_line_numbers)
{
    std::cout << "Getting logs for log line numbers" << std::endl;
    std::map<std::string, std::string> logs;
    std::string folder_path = "data/g" + std::to_string(group_number_) + "_" + "r" + std::to_string(server_number_) + "/log_files/";
    int log_file_num = 0;
    std::cout << "log line numbers size: " << log_line_numbers.size() << std::endl;
    // read the logs from the filenames in folder_path
    if (std::filesystem::is_directory(folder_path))
    {
        for (const auto &entry : std::filesystem::directory_iterator(folder_path))
        {
            std::ifstream file(entry.path());
            // iterate forward by log_line_numbers[log_file] lines
            int lines_to_skip = log_line_numbers.at(log_file_num);
            std::cout << "Skipping " << lines_to_skip << " lines" << std::endl;
            for (int i = 0; i < lines_to_skip; i++)
            {
                if (file.ignore(std::numeric_limits<std::streamsize>::max(), '\n').eof())
                {
                    std::cerr << "Error: Not enough lines in file " << entry.path() << std::endl;
                    break;
                }
            }
            // after skipping the lines, read the log file into a string and push it into our log file vector
            std::string log;
            if (!file.eof())
            {
                log.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                logs[entry.path().filename().string()] = log;
                log_file_num++;
            }
            else
            {
                std::cerr << "Error: End of file reached" << std::endl;
            }
        }
    }
    else
    {
        std::cerr << "Error: Directory does not exist" << std::endl;
    }
    return logs;
}

Tablet *Tablet_Manager::get_tablet_by_id(int tablet_id)
{
    if (tablet_list_.find(tablet_id) == tablet_list_.end())
    {
        std::cerr << "Tablet with id " << tablet_id << " not found" << std::endl;
        return nullptr;
    }
    return tablet_list_[tablet_id].get();
}

void Tablet_Manager::delete_all_outdated_tablet_files()
{
    std::string folder_path = "data/g" + std::to_string(group_number_) + "_" + "r" + std::to_string(server_number_) + "/tablets/";
    for (const auto &entry : std::filesystem::directory_iterator(folder_path))
    {
        std::filesystem::remove(entry.path());
    }
}

std::string Tablet_Manager::get_server_path() const
{
    return std::string("data/g") + std::to_string(group_number_) + "_" + "r" + std::to_string(server_number_);
}

std::vector<Tablet *> Tablet_Manager::get_all_tablets()
{
    std::vector<Tablet *> tablets;
    for (const auto &tablet : tablet_list_)
    {
        tablets.push_back(tablet.second.get());
    }
    return tablets;
}

void Tablet_Manager::add_tablet_from_checkpoint_file(const std::string &file_path, const std::string &starting_range)
{
    // lock max max_tablet_id_mutex_ first to avoid race conditions
    std::unique_lock<std::mutex> max_tablet_id_lock(max_tablet_id_mutex_);
    // increment max_tablet_id_
    max_tablet_id_++;
    std::cout << "Adding tablet from checkpoint file: " << file_path << std::endl;
    // get the tablet id from the file path
    int tablet_id = get_tablet_id_from_file(file_path);
    // create the folder path for the tablets
    std::string folder_path = "data/g" + std::to_string(group_number_) + "_" + "r" + std::to_string(server_number_);
    // create the tablet and store it
    tablet_list_.emplace(tablet_id, std::make_unique<Tablet>(file_path, folder_path, tablet_id));

    key_tablet_id_map_[starting_range] = tablet_id;
    // Store starting range in metadata file
    storing_range_metadata_to_file(starting_range, tablet_id);
}
