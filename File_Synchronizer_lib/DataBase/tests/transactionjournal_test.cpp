#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "transactionjournal.h"

TEST(SetParam, SetJournalPath){
    TransactionJournal journal;
    std::filesystem::path source = "/etc/db/trjournal/";

    journal.set_transaction_path(source);
    EXPECT_EQ(journal.get_transaction_path(), source);
}

TEST(SetParam, SetMachineTransactionNum){
    TransactionJournal journal;
    int current_tr_num = 10;

    journal.set_current_machine_transaction(current_tr_num);
    EXPECT_EQ(journal.get_current_machine_transaction(), current_tr_num);
}

class MockJournal : public TransactionJournal {
public:
    MOCK_METHOD(void, CreateTransaction, (const std::string& operation_type, const std::string& filename));
    MOCK_METHOD(int, ClearTransactions, ());
    MOCK_METHOD(std::filesystem::path, GetTransactionJournal, ());
};

TEST(JournalTest, CreateTransaction) {
    MockJournal journal;
    EXPECT_CALL(journal, CreateTransaction);
}

TEST(JournalTest, ClearTransaction) {
    using ::testing::Return;
    MockJournal journal;
    EXPECT_CALL(journal, ClearTransactions())
            .Times(3)
            .WillOnce(Return(0))
            .WillRepeatedly(Return(1));
}

TEST(JournalTest, GetJournal) {
    using ::testing::Return;
    MockJournal journal;
    EXPECT_CALL(journal, GetTransactionJournal())
            .WillOnce(Return(std::filesystem::path() ));
}
