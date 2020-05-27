#include "CommandReader.h"

#include <iostream>

using FileSynchronizer::CommandReader;

namespace fs = std::filesystem;

CommandReader::CommandReader(FileSynchronizer::ApplicationController& controller) : controller(controller) {
    Listen();
}

void CommandReader::Listen() {
    std::string command;
    while (std::getline(std::cin, command)) {
        auto operation = command.substr(0, command.find(' '));
        if (operation == "quit") {
            controller.Stop();
            return;
        } else if (operation == "files") {
            controller.ShowFilesList();
        } else if (operation == "help") {
            Help();
        } else if (operation == "cleardb") {
            std::cout << "Are you sure?" << std::endl;
            char answer;
            std::cin >> answer;
            if (answer == 'y') {
                controller.ClearDB();
            }
        } else if (operation == "log") {
            if (operation.size() == command.size()) {
                controller.ShowLog();
                continue;
            }
            auto argument = command.substr(operation.size() + 1);
            if (argument.empty()) {
                controller.ShowLog();
            } else if (argument.substr(0, argument.find(' ')) == "head") {
                if (argument.size() == argument.substr(0, argument.find(' ')).size()) {
                    controller.ShowLogHead();
                } else {
                    argument = argument.substr(argument.find(' ') + 1);
                    std::stringstream stream(argument);
                    int count = 0;
                    stream >> count;
                    controller.ShowLogHead(count);
                }
            } else if (argument.substr(0, argument.find(' ')) == "tail") {
                if (argument.size() == argument.substr(0, argument.find(' ')).size()) {
                    controller.ShowLogTail();
                } else {
                    argument = argument.substr(argument.find(' ') + 1);
                    std::stringstream stream(argument);
                    int count = 0;
                    stream >> count;
                    controller.ShowLogTail(count);
                }
            }
        } else {
            if (operation.size() == command.size()) {
                continue;
            }
            auto argument = command.substr(operation.size() + 1, operation.find(' '));

            if (operation == "filelog") {
                controller.ShowLogFile(argument);
            } else if (operation == "datelog") {
                controller.ShowLogData(argument);
            } else if (operation == "restore") {
                if (argument.size() == argument.substr(0, argument.find(' ')).size()) {
                    continue;
                }

                std::stringstream stream(argument.substr(argument.find(' ') + 1));
                int count = 0;
                stream >> count;
                controller.RestoreVersion(argument, count);
            } else {
                if (!fs::exists(argument)) {
                    continue;
                }

                if (operation == "watch") {
                    controller.AddDirectory(argument);
                } else if (operation == "delete") {
                    controller.DeleteDirectory(argument);
                } else if (operation == "ignore") {
                    controller.AddIgnoredFile(argument);
                } else if (operation == "track") {
                    controller.DeleteIgnoredFile(argument);
                } else if (operation == "history") {
                    controller.ShowFileVersions(argument);
                }
            }
        }
    }
}

void FileSynchronizer::CommandReader::Help() {
    std::cout << "quit: Close application" << std::endl
              << "files: Show list of tracked files" << std::endl
              << "cleardb: Delete database with files" << std::endl
              << "log <head/tail> <count=5>: Show first/last count log records" << std::endl
              << "filelog: Show all records for file" << std::endl
              << "datelog: Show all records for date" << std::endl
              << "watch <filename>: Add directory for watching" << std::endl
              << "delete <filename>: Remove directory" << std::endl
              << "ignore <filename>: Stop tracking file" << std::endl
              << "track <filename>: Stop ignoring file" << std::endl
              << "history <filename>: Show all versions of file" << std::endl
              << "restore <filename> <index>: Restore file" << std::endl;
}
