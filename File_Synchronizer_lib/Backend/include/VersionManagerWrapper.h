#ifndef FILE_SYNCHRONIZER_VERSIONMANAGERWRAPPER_H
#define FILE_SYNCHRONIZER_VERSIONMANAGERWRAPPER_H

#include "IVersionManager.h"

#include <filesystem>
#include <memory>

namespace FileSynchronizer {
    namespace fs = std::filesystem;

    class VersionManagerWrapper { ;
    public:
#ifndef DATABASE
        VersionManagerWrapper();
#endif
        explicit VersionManagerWrapper(std::unique_ptr<IVersionManager> manager);
        void ShowFileVersions(const fs::path& file);
        void RestoreFileVersion(const fs::path& file, int index);

    private:
        std::unique_ptr<IVersionManager> manager;
    };
}

#endif //FILE_SYNCHRONIZER_VERSIONMANAGERWRAPPER_H
