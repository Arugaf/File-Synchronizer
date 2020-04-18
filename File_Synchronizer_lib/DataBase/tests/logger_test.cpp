#include <gtest/gtest.h>

#include <utility>

#include "logger.h"

#include <fstream>

class TestTransaction : ITransaction {
private:
    std::string _message;
public:
    TestTransaction() = default;
    TestTransaction(const std::string& message): _message(message) {};

    std::string get_message() {
        return _message;
    }
};

class TestLogger : ILogger {
private:
    std::string log_path;
public:
    void set_log_path(const std::string& source) {
        log_path = source;
    }
    void CreateTransaction(const std::string& message) override {
        auto *transaction = new TestTransaction(message);
        std::ofstream file;
        file.open(log_path, std::ios::out);
        file << transaction->get_message();
        file.close();
    }
};

TEST(name, test) {
    TestLogger logger;

    std::string log_file = "log.txt";
    std::string log_message = "I'm transaction for test!";
    std::string message;

    logger.set_log_path(log_file);
    logger.CreateTransaction(log_message);

    std::ifstream file;
    file.open(log_file, std::ios::in);
    getline(file, message);

    EXPECT_EQ(message, log_message);
}