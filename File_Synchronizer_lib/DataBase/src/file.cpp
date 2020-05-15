#include "file.h"

void File::SetFilename(const std::string &name) {
    filename = name;
}

void File::SetFilename(const std::filesystem::path &source) {
    filename = source.filename().string();
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

void File::Print(std::ostream &out) {
    std::string info;

    info = filename + "\n"
         + filepath.string() + "\n";

    out << info;
}


