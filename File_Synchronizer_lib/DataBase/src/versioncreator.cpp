#include <vector>
#include <functional>

#include "versioncreator.h"

void VersionCreator::AddToIndex(File file, const std::filesystem::path& versionsDirectory) {
    try {
        std::filesystem::path source = file.GetFilepath();
        std::filesystem::path target = versionsDirectory / file.GetFilename() / file.GetFilepath().stem();

        if (!std::filesystem::exists(target)) {
            std::filesystem::create_directories(target);
        }

        std::filesystem::copy_file(source, target, std::filesystem::copy_options::overwrite_existing);

    } catch (std::filesystem::filesystem_error& exception) {
        std::ostringstream msg;
        msg << exception.what() << std::endl;
    }
}

void VersionCreator::CreateDiff(File file) {


}

std::string VersionCreator::ComputeMD5() {
    std::string element;
    std::vector<std::string> sequenceFrom;


}
