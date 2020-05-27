#include "VersionManagerWrapper.h"

#include <iostream>

using FileSynchronizer::VersionManagerWrapper;

VersionManagerWrapper::VersionManagerWrapper(std::unique_ptr<IVersionManager> manager) : manager(std::move(manager)) {

}

void VersionManagerWrapper::ShowFileVersions(const std::filesystem::path& file) {
    int index = 0;
    for (const auto& it : manager->GetVersionHistoryForFile(file)) {
        std::cout << it << ' ' << index++ << std::endl;
    }
}

void VersionManagerWrapper::RestoreFileVersion(const std::filesystem::path& file, int index) {
    fs::copy_file(manager->GetVersionHistoryForFile(file)[index], file, fs::copy_options::overwrite_existing);
}

#ifndef DATABASE
VersionManagerWrapper::VersionManagerWrapper() : manager(nullptr) {

}
#endif
