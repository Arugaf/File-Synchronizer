#include "file.h"

void File::SetFilename(const std::string &name) {
    filename = name;
}

std::string File::GetFilename() {
    return filename;
}

void File::SetFilepath(const std::filesystem::path &source) {
    filepath = source;
}

std::filesystem::path File::GetFilepath() {
    return filepath;
}

bool File::IsInBlacklist() {
    return blacklist;
}

void File::AddFileToBlacklist() {
    blacklist = true;
}

void File::DeleteFileFromBlacklist() {
    blacklist = false;
}

void File::Print(std::ostream &out) {
    std::string info;

    info =  filename + "\n"
            + filepath.string() + "\n"
            + std::to_string(blacklist);

    out << info;
}


