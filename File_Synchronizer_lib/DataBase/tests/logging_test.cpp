#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>

#include "transactionjournal.h"
#include "../src/filemanagers.hpp"

class MockTransaction : public ITransaction {
public:
    MOCK_METHOD(std::string, GetMessage, ());
};

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

//#include "versionmanager.h"

/*
TEST(JournalTest, LogVersions) {
    TestJournal testLogger;

    VersionManager vManager(&testLogger);
    vManager.SetVersionsPath("");

    std::filesystem::path testFile("test.txt");
    std::filesystem::create_directories(testFile);

    std::ofstream file(testFile);
    if (file.is_open()) {
        file << "Experience tranquility";
    }
    file.close();

    File fileObject(testFile.filename(), testFile);
    vManager.CreateVersion(fileObject);

    int size = testLogger.GetJournalSize();
    EXPECT_EQ(size, 2);

}*/
