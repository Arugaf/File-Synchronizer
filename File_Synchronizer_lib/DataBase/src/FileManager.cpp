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
    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
                                                            + system_clock::now());
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
    auto lastOperationTime = std::filesystem::last_write_time(file);

    if (fileList.contains(file)) {
        versionManager->CreateVersion(file);

        Transaction transaction(Operation::modified, file);
        logger->AddTransaction(transaction);
    } else {
        versionManager->CreateIndex(file);

        Transaction transaction(Operation::created, file);
        logger->AddTransaction(transaction);
    }

    fileList.insert_or_assign(file, lastOperationTime);

    logger->FixTransaction();

}

void FileManager::DeleteFile(const std::filesystem::path& file) {
    try {
        fileList.erase(file);
        versionManager->DeleteFile(file.stem());
    } catch (std::exception &e) {
        throw FileSearchException();
    }

    Transaction transaction(Operation::deleted, file);
    logger->AddTransaction(transaction);
    logger->FixTransaction();
}

void FileManager::Clear() {
    fileList.clear();
}

void FileManager::Load() {
    /*boost::property_tree::ptree root;

    boost::property_tree::read_json(trackfile, root);

    std::vector<std::pair<std::string, std::string>> list;

    for (boost::property_tree::ptree::value_type &file : root) {
        //SetFileInfo(std::filesystem::path(file.first), file.second.data());
    }*/
}

void FileManager::Save() {
    boost::property_tree::ptree root;

    for (auto &file : fileList) {
        auto readable_time = to_time_t(file.second);
        root.put(file.first.string(), std::asctime(std::localtime(&readable_time)));
    }

    boost::property_tree::write_json(trackfile, root);
}

