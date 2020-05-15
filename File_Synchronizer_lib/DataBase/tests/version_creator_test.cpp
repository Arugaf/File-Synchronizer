#include <gtest/gtest.h>
#include <fstream>

#include "versioncreator.h"


TEST (VersionCreatorTest, CreateIndexCopy) {
    std::string message;
    VersionCreator vCreator;

    std::string firstSequence = "FIRST";
    std::string secondSequence = "SECOND";

    std::string testFile = "tracking.txt";
    std::filesystem::path relativePath = "sandbox";
    relativePath /= testFile;
    std::filesystem::path source = std::filesystem::absolute(relativePath);

    std::filesystem::create_directory(source.parent_path());

    std::ofstream fOut(source);
    fOut << firstSequence;
    fOut.close();

    std::ifstream fRead(source);
    std::getline(fRead, message);
    ASSERT_EQ(message, firstSequence);

    vCreator.AddToIndex(source, source.parent_path());

    std::ifstream indexRead("index" + source.extension().string());
    std::getline(indexRead, message);

    EXPECT_EQ(message, firstSequence);

    fOut.open(source);
    fOut << secondSequence;
    fOut.close();

    vCreator.AddToIndex(source, source.parent_path());

    indexRead.open("index" + source.extension().string());
    std::getline(indexRead, message);

    EXPECT_EQ(message, firstSequence);
}

TEST (VersionCreatorTest, CreateVersionByCopy) {
    std::string message;
    VersionCreator vCreator;
    std::vector<std::filesystem::path> history;

    std::string firstSequence = "FIRST";
    std::string secondSequence = "SECOND";

    std::string testFile = "tracking.txt";
    std::filesystem::path relativePath = "sandbox";
    relativePath /= testFile;
    std::filesystem::path source = std::filesystem::absolute(relativePath);

    std::filesystem::create_directory(source.parent_path());
    std::filesystem::remove_all(source.parent_path() / source.stem());

    std::ofstream fOut(source);
    fOut << firstSequence;
    fOut.close();

    std::ifstream fRead(source);
    std::getline(fRead, message);
    ASSERT_EQ(message, firstSequence);

    vCreator.CreateDiff(source, source.parent_path());

    fOut.open(source);
    fOut << secondSequence;
    fOut.close();

    vCreator.CreateDiff(source, source.parent_path());

    for ( auto& item: std::filesystem::directory_iterator(source.parent_path() / source.stem()) ) {
        history.push_back(item);
    }
    std::sort(history.begin(), history.end(), [](const std::filesystem::path& l, const std::filesystem::path& r) {
        return (std::filesystem::last_write_time(l) < std::filesystem::last_write_time(r));
    });

    std::ifstream versionRead;
    versionRead.open(history[0]);
    std::getline(versionRead, message);
    EXPECT_EQ(message, firstSequence);
    versionRead.close();

    versionRead.open(history[1]);
    std::getline(versionRead, message);
    EXPECT_EQ(message, secondSequence);
}

