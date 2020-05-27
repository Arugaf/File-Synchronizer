#ifndef FILE_SYNCHRONIZER_VERSIONCREATOR_H
#define FILE_SYNCHRONIZER_VERSIONCREATOR_H

#include <filesystem>
#include <functional>

#include "dtl/dtl.hpp"

class VersionCreator {
private:
    std::function<std::string (const std::filesystem::path&)> computeHash;

    // Функция для хэшей файлов, используемая по умолчанию
    std::string SimpleHashSum(const std::filesystem::path& targetSource);
public:
    VersionCreator() {
        computeHash = [&](const std::filesystem::path& targetSource) {
          return SimpleHashSum(targetSource);
        };
    }

    typedef std::function<std::string (const std::filesystem::path&)> hasher;
    VersionCreator(const hasher& _hasher) {
        computeHash = _hasher;
    }

    virtual ~VersionCreator() = default;

    virtual std::filesystem::path AddToIndex(const std::filesystem::path& sourceFilePath, const std::filesystem::path& versionsDirectory);
    virtual std::filesystem::path CreateVersion(const std::filesystem::path& sourceFilePath, const std::filesystem::path& versionsDirectory);
};

#endif //FILE_SYNCHRONIZER_VERSIONCREATOR_H
