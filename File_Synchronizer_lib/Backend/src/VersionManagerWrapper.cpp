#include "VersionManagerWrapper.h"

#include <iostream>
#include <iomanip>

using FileSynchronizer::VersionManagerWrapper;

VersionManagerWrapper::VersionManagerWrapper(std::unique_ptr<IVersionManager> manager) : manager(std::move(manager)) {

}

void VersionManagerWrapper::ShowFileVersions(const std::filesystem::path& file) {
    int index = 0;

    auto func2 = [](std::filesystem::file_time_type tp) ->std::time_t {
        using namespace std::chrono;
        auto sctp = time_point_cast<system_clock::duration>(tp - std::filesystem::file_time_type ::clock::now() + system_clock::now());
        return system_clock::to_time_t(sctp);
    };

    std::cout << std::setw(8) << std::setiosflags(std::ios::right) << "index" << std::setw(30) << std::setiosflags(std::ios::right) << "hash" << std::setiosflags(std::ios::right) << std::setw(30) << "time" << std::endl;
    for (const auto& it : manager->GetVersionHistoryForFile(file)) {
        auto readable_time = func2(std::filesystem::last_write_time(it));
        std::stringstream stream(std::asctime(std::localtime(&readable_time)));

        std::cout << std::setiosflags(std::ios::left) << std::setw(8) << index++ << ' ' << std::setiosflags(std::ios::left) << std::setw(30) << it.stem() << ' ' <<
        std::setiosflags(std::ios::left) << std::setw(30) << std::string(stream.str().c_str(), stream.str().size() - 1) << std::endl;
    }
}

void VersionManagerWrapper::RestoreFileVersion(const std::filesystem::path& file, int index) {
    fs::copy_file(manager->GetVersionHistoryForFile(file)[index], file, fs::copy_options::overwrite_existing);
}

#ifndef DATABASE
VersionManagerWrapper::VersionManagerWrapper() : manager(nullptr) {

}
#endif
