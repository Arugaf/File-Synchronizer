#include <vector>
#include <functional>
#include <fstream>

#include "versioncreator.h"

std::string VersionCreator::ComputeHashSum(const std::filesystem::path& targetSource) {
    std::string element;
    size_t hash = 1;

    std::ifstream targetFile(targetSource);
    if (targetFile.is_open()) {
        for (int i = 0; !targetFile.eof(); i++) {
            std::getline(targetFile, element);

            size_t currentHash = std::hash<std::string>()(element);
            hash = hash ^ (currentHash << i);
        }
    }
    targetFile.close();

    return std::to_string(hash);
}

std::filesystem::path VersionCreator::AddToIndex(File file, const std::filesystem::path& versionsDirectory) {
    try {
        std::string indexName = "index" + file.GetFilepath().extension().string();

        std::filesystem::path source = file.GetFilepath();
        std::filesystem::path index = versionsDirectory / file.GetFilename() / indexName;

        if (!std::filesystem::exists(index)) {
            std::filesystem::create_directories(index);
        }

        std::filesystem::copy_file(source, index, std::filesystem::copy_options::overwrite_existing);

        return index;

    } catch (std::filesystem::filesystem_error& exception) {
        std::ostringstream msg;
        msg << exception.what() << std::endl;
    }
}

std::filesystem::path VersionCreator::CreateDiff(File file, const std::filesystem::path& versionsDirectory) {
    // A - исходный файл по GetFilepath
    // B - последний индекс по пути <versionsDirectory>/<GetFilename>/index.[exp]
    //std::string indexName = "index" + file.GetFilepath().extension().string();

    //std::filesystem::path A = file.GetFilepath();
    //std::filesystem::path B = versionsDirectory / file.GetFilename() / indexName;

    // ВЕРСИИ СОЗДАЮТСЯ КОПИРОВАНИЕМ ФАЙЛА

    std::filesystem::path source = file.GetFilepath();
    std::filesystem::path version = versionsDirectory / file.GetFilename() / ComputeHashSum(file.GetFilepath());

    if (!std::filesystem::exists(version)) {
        std::filesystem::create_directories(version);
    }

    std::filesystem::copy_file(source, version, std::filesystem::copy_options::update_existing);

    return version;
}