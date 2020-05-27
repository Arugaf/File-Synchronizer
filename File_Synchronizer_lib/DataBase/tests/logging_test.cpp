#include <gtest/gtest.h>
#include <fstream>

#include "TransactionJournal.h"
#include "FileManager.h"


TEST(JournalTest, LogVersions) {
    std::string testSequence = "test";

    std::string testFile = "test.txt";
    std::filesystem::path relativePath = "sandbox";
    relativePath /= testFile;
    std::filesystem::path source = std::filesystem::absolute(relativePath);

    std::filesystem::create_directory(source.parent_path());
    std::filesystem::remove_all(source.parent_path() / source.stem());

    std::ofstream fOut(source);
    fOut << testSequence;
    fOut.close();

    TestJournal testLogger;

    FileManager manager(source.parent_path(), &testLogger);

    manager.SetFileInfo(source);

    int size = testLogger.GetSize();
    EXPECT_EQ(size, 1);
}

