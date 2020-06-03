#include "FileManager.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <chrono>


struct FileSearchException : public std::exception {
    [[nodiscard]] const char * what () const noexcept override {
        return "File doesn't exists";
    }
};

template<typename TP>
std::time_t FileManager::to_time_t(TP tp) {
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now() + system_clock::now());
    return system_clock::to_time_t(sctp);
}

std::pair<std::filesystem::path, std::filesystem::file_time_type> FileManager::GetFileInfo(const std::filesystem::path& file) {
    auto node = fileList.find(file);

    if (node != fileList.end()) {
        std::pair<std::filesystem::path, std::filesystem::file_time_type> finded;
        finded.first = node->first;
        finded.second = node->second;

        return finded;
    } else {
        throw FileSearchException();
    }
}

FileManager::list FileManager::GetInfo() {
    return fileList;
}

void FileManager::SetFileInfo(const std::filesystem::path& file) {
    if (std::filesystem::exists(file)) {
        if (fileList.contains(file)) {
            Transaction transaction(Operation::modified, file);
            logger->AddTransaction(transaction);
        } else {
            RestoreFile(file);
            Transaction transaction(Operation::created, file);
            logger->AddTransaction(transaction);
        }
        versionManager->CreateVersion(file);

        auto lastOperationTime = std::filesystem::last_write_time(file);
        fileList.insert_or_assign(file, lastOperationTime);

        logger->FixTransaction();
    }
}

void FileManager::DeleteFile(const std::filesystem::path& file) {
    try {
        fileList.erase(file);
        deletedFiles.push_back(file);
    } catch (std::exception &e) {
        throw FileSearchException();
    }

    Transaction transaction(Operation::deleted, file);
    logger->AddTransaction(transaction);
    logger->FixTransaction();
}

void FileManager::RestoreFile(const std::filesystem::path &file) {
    if (std::find(deletedFiles.begin(), deletedFiles.end(), file) != deletedFiles.end()) {
        deletedFiles.erase(std::remove(deletedFiles.begin(), deletedFiles.end(), file), deletedFiles.end());
        fileList.insert_or_assign(file, std::filesystem::last_write_time(file));
    }
}

void FileManager::DeleteFileInstantly(const std::filesystem::path &file) {
    if (fileList.contains(file)) {
        fileList.erase(file);
    }
    if (std::find(deletedFiles.begin(), deletedFiles.end(), file) != deletedFiles.end()) {
        deletedFiles.erase(std::remove(deletedFiles.begin(), deletedFiles.end(), file), deletedFiles.end());
    }

    versionManager->DeleteFileInstantly(file);

    Transaction transaction(Operation::deleted, file);
    logger->AddTransaction(transaction);
    logger->FixTransaction();
}

void FileManager::Clear() {
    fileList.clear();
}

void FileManager::Load() {
    if (!std::filesystem::exists(trackfile)) {
        return;
    }
    boost::property_tree::ptree root;
    boost::property_tree::read_json(trackfile, root);

    std::vector<std::pair<std::string, std::string>> list;

    std::string path;
    std::string ext;
    std::string filetime;

    for (boost::property_tree::ptree::value_type &record : root) {
        path = record.first;
        path += ".";

        for (boost::property_tree::ptree::value_type &file : root.get_child(record.first)) {
            ext = file.first;
            filetime = file.second.data();

            list.emplace_back(path + ext, filetime);
        }
        //boost::property_tree::write_json(std::cout, root);
    }

    tm tm{};
    for (const auto& item : list) {
        std::istringstream ss(item.second);
        ss >> std::get_time(&tm, "%c");
        std::time_t timeT = std::mktime(&tm);

        auto tp = std::chrono::system_clock::from_time_t(timeT);
        // TODO: convert to file clock?
        // TODO: possible in C++20, but "clock_cast" not founded
        fileList.insert_or_assign(std::filesystem::path(item.first), std::filesystem::last_write_time(item.first));
        //auto ftp =  clock_cast<chrono::file_clock>(chrono::system_clock::from_time_t(timeT));
        //fileList.insert_or_assign(std::filesystem::path(item.first), tp);

        //std::cout << item.first << ":" << item.second << std::endl;
    }
}

void FileManager::Save() {
    boost::property_tree::ptree root;

    for (auto &file : fileList) {
        auto readable_time = to_time_t(file.second);
        root.put(file.first.string(), std::asctime(std::localtime(&readable_time)));
    }

    boost::property_tree::write_json(trackfile, root);
}

int FileManager::ClearAll() {
    Clear();

    int successTrack = std::filesystem::remove_all(trackfile);
    //int successDeleted = std::filesystem::remove_all(deletedfile);

    return successTrack/* + successDeleted*/;
}



