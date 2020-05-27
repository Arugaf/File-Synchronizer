#include <vector>
#include <functional>
#include <fstream>
#include <iostream>

#include "VersionCreator.h"
#include "dtl/dtl.hpp"

std::string VersionCreator::SimpleHashSum(const std::filesystem::path& targetSource) {
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


std::filesystem::path VersionCreator::AddToIndex(const std::filesystem::path& sourceFilePath, const std::filesystem::path& versionsDirectory) {
    try {
        std::string indexName = "index" + sourceFilePath.extension().string();

        std::filesystem::path index = versionsDirectory / sourceFilePath.stem() / indexName;

        if (!std::filesystem::exists(index.parent_path())) {
            std::filesystem::create_directories(index.parent_path());
        }

        std::filesystem::copy_file(sourceFilePath, index, std::filesystem::copy_options::overwrite_existing);

        return index;

    } catch (std::filesystem::filesystem_error& exception) {
        std::ostringstream msg;
        msg << exception.what() << std::endl;
    }
}

std::filesystem::path VersionCreator::CreateVersion(const std::filesystem::path& sourceFilePath, const std::filesystem::path& versionsDirectory) {
    // ВЕРСИИ СОЗДАЮТСЯ КОПИРОВАНИЕМ ФАЙЛА
    // работает не только для .txt

    std::string version = computeHash(sourceFilePath) + sourceFilePath.extension().string();
    std::filesystem::path versionPath = versionsDirectory / sourceFilePath.stem() / version ;

    if (!std::filesystem::exists(versionPath.parent_path())) {
        std::filesystem::create_directories(versionPath.parent_path());
    }

    std::filesystem::copy_file(sourceFilePath, versionPath, std::filesystem::copy_options::update_existing);

    return versionPath;
}


std::filesystem::path VersionCreator::CreateDiff(const std::filesystem::path &file, const std::filesystem::path& versionsDirectory) {
        // A - исходный файл по sourceFilePath
        // B - последний индекс по пути <versionsDirectory>/<GetFilename>/index.[exp]
        std::string indexName = "index" + file.extension().string();
        std::filesystem::path A = file;
        std::filesystem::path B = versionsDirectory / file.filename() / indexName;

        std::string version = computeHash(file) + file.extension().string();
        std::filesystem::path versionPath = versionsDirectory / file.stem() / version ;

        if (!std::filesystem::exists(versionPath.parent_path())) {
            std::filesystem::create_directories(versionPath.parent_path());
        }

        std::string buf;
        std::vector<std::string> ALines;
        std::vector<std::string> BLines;

        std::ifstream Aifs(A);
        std::ifstream Bifs(B);

        while (getline(Aifs, buf)) {
            ALines.push_back(buf);
        }
        while (getline(Bifs, buf)) {
            BLines.push_back(buf);
        }

        dtl::Diff<std::string> diff(ALines, BLines);

        diff.onHuge();
        diff.compose();

        diff.composeUnifiedHunks();
        diff.printUnifiedFormat();

        std::filesystem::copy_file(file, versionPath, std::filesystem::copy_options::update_existing);

        return versionPath;
}
