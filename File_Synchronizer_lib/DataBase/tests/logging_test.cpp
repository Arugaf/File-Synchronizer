#include <gtest/gtest.h>
// #include <gmock/gmock.h>
#include <fstream>

#include "transactionjournal.h"
#include "versionmanager.h"

/*
class MockTransaction : public ITransaction {
public:
    MOCK_METHOD(std::string, GetMessage, ());
};
*/

class TestJournal : public ITransactionJournal {
private:
    std::vector<Transaction> log;
public:
    void AddTransaction(Transaction _tr) override {
        _tr.SetMessage("I'm transaction for test!");
        log.push_back(_tr);
    };
    void DeleteTransaction() override {
        log.pop_back();
    };
    void Clear() override {
        log.clear();
    };
    std::string GetLastTransaction() {
        return log.back().GetMessage();
    }
    int GetJournalSize() override {
        return log.size();
    }
};


TEST(JournalTest, AddTransaction) {
    TestJournal testLogger;
    int size = 0;
    std::string message;

    Transaction transaction;
    testLogger.AddTransaction(transaction);

    size = testLogger.GetJournalSize();
    message = testLogger.GetLastTransaction();

    EXPECT_EQ(size, 1);
    EXPECT_EQ(message, "I'm transaction for test!");

}

TEST(JournalTest, DeleteTransaction) {
    TestJournal testLogger;
    int size = 0;

    Transaction transaction;
    testLogger.AddTransaction(transaction);
    testLogger.AddTransaction(transaction);

    size = testLogger.GetJournalSize();
    EXPECT_EQ(size, 2);

    testLogger.DeleteTransaction();
    size = testLogger.GetJournalSize();
    EXPECT_EQ(size, 1);
}

TEST(JournalTest, ClearJournal) {
    TestJournal testLogger;
    int size = 5;

    for (int i = 0; i < size; i++) {
        Transaction transaction;
        testLogger.AddTransaction(transaction);
    }

    testLogger.Clear();
    size = testLogger.GetJournalSize();
    EXPECT_EQ(size, 0);
}

#include "filesystem_imitation.hpp"

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

    VersionManager vManager(&testLogger);
    vManager.SetVersionsPath(source.parent_path());

    File fileObject(source);

    vManager.CreateVersion(fileObject);

    int size = testLogger.GetJournalSize();
    EXPECT_EQ(size, 2);
}
