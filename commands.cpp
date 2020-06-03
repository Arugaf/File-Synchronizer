#include "File_Synchronizer_lib/Backend/include/ApplicationController.h"
#include "File_Synchronizer_lib/DataBase/include/FileManager.h"
#include "File_Synchronizer_lib/include/IFileManager.h"

#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>

namespace po = boost::program_options;

int main(int ac, char** av) {

    po::options_description desc("Available arguments");

    std::string arg;
    std::vector<std::string> args;
    desc.add_options()
            ("path", po::value<std::string>(&arg)->value_name("<path>"), "Set path to working directory")
            ("help,h", "Show possible arguments")
            ("files,l", "Show list of tracked files")
            ("history,v", po::value<std::string>(&arg)->value_name("<filename>"), "Show list of file versions")
            ("restore,r", po::value<std::vector<std::string>>(&args)->multitoken()->value_name("<filename> <index>"), "Restore previous version of file")
            /*("watch,w", po::value<std::string>(&arg)->value_name("<filename>"), "Add directory to watch")
            ("remove,R", po::value<std::string>()->value_name("<filename>"), "Stop watching directory")
            ("ignore,i", po::value<std::string>()->value_name("<filename>"), "Ignore file")
            ("track,t", po::value<std::string>()->value_name("<filename>"), "Stop ignoring file")*/
            ("delete", po::value<std::string>(&arg)->value_name("<filename>"), "Delete all versions of file")
            //("cleardb", "Clear database")
            ;

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    if (vm.count("path")) {
        if (std::filesystem::exists(arg)) {
            std::ofstream config("config.cfg");
            config.clear();
            config << arg;
            config.close();
            std::cout << "Path to config was set: " << arg << std::endl;
            return 0;
        } else {
            std::cout << "Working path is not valid" << std::endl;
            return 0;
        }
    }

    std::fstream config("config.cfg");
    std::string path;
    config >> path;
    config.close();

    if (!std::filesystem::exists(path)) {
        std::cout << "Working path is not valid" << std::endl;
        return 0;
    }

    if (vm.count("files")) {
        FileManager fm(path);
        fm.Load();

        if (fm.GetInfo().empty()) {
            std::cout << "Tracked files list is empty" << std::endl;
            return 0;
        }

        std::cout << "Tracked files:" << std::endl;
        for (const auto& it : fm.GetInfo()) {
            std::cout << it.first << std::endl;
        }
        return 0;
    }

    if (vm.count("history")) {
        VersionManager vem(path);
        int index = 0;

        auto func2 = [](std::filesystem::file_time_type tp) ->std::time_t {
            using namespace std::chrono;
            auto sctp = time_point_cast<system_clock::duration>(tp - std::filesystem::file_time_type ::clock::now() + system_clock::now());
            return system_clock::to_time_t(sctp);
        };

        if (vem.GetVersionHistoryForFile(arg).empty()) {
            std::cout << "No versions for this file founded :(" << std::endl;
            return 0;
        }
        std::cout << std::setw(8) << std::setiosflags(std::ios::right) << "index" << std::setw(30) << std::setiosflags(std::ios::right) << "hash" << std::setiosflags(std::ios::right) << std::setw(30) << "time" << std::endl;
        for (const auto& it : vem.GetVersionHistoryForFile(arg)) {
            auto readable_time = func2(std::filesystem::last_write_time(it));
            std::stringstream stream(std::asctime(std::localtime(&readable_time)));

            std::cout << std::setiosflags(std::ios::left) << std::setw(8) << index++ << ' ' << std::setiosflags(std::ios::left) << std::setw(30) << it.stem() << ' ' <<
                      std::setiosflags(std::ios::left) << std::setw(30) << std::string(stream.str().c_str(), stream.str().size() - 1) << std::endl;
        }
        return 0;
    }

    if (vm.count("restore")) {
        FileManager fm(path);
        VersionManager vem(path);

        if (args.size() < 2) {
            std::cout << "Not enough arguments" << std::endl;
            return 0;
        }

        auto fname = args[0];
        auto file_index = args[1];

        int iindex = 0;
        std::stringstream sstream(file_index);
        sstream >> iindex;

        fm.RestoreFile(fname);
        try {
            vem.RestoreFileFromVersion(fname, iindex);
        } catch (bool result) {
            std::cout << "Cannot restore this file" << std::endl;
            return 0;
        }

        std::cout << "File was successfully restored to version " << iindex << std::endl;
        return 0;
        //std::filesystem::copy_file(vem.GetVersionHistoryForFile(fname)[iindex], fname, std::filesystem::copy_options::overwrite_existing);
    }

    if (vm.count("delete")) {
        VersionManager vem(path);
        std::cout << "Confirm deleting (you will lose all data) [Y/n]" << std::endl;
        std::string ans;
        std::cin >> ans;
        if (ans == "Y" || ans == "y" || ans == "Yes" || ans == "yes") {
            if (vem.DeleteFileInstantly(arg) > 0) {
                std::cout << "All file versions were successfully deleted" << std::endl;
            } else {
                std::cout << "No versions for this file founded" << std::endl;
            }
        }
        return 0;
    }

    /*if (vm.count("cleardb")) {
        FileManager fm(path);
        std::cout << "Confirm deleting (your database will be ) [Y/n]" << std::endl;
        std::string ans;
        std::cin >> ans;
        if (ans == "Y" || ans == "y" || ans == "Yes" || ans == "yes") {
            if (vem.DeleteFileInstantly(arg) > 0) {
                std::cout << "All file versions were successfully deleted" << std::endl;
            } else {
                std::cout << "No versions for this file founded" << std::endl;
            }
        }
        return 0;
    }*/

    /*if (vm.count("watch")) {
        std::filesystem::path config_file_path(path);
        config_file_path /= "configure.cfg";
        if (!std::filesystem::exists(config_file_path)) {
            std::cout << "Working path is not valid" << std::endl;
            return 0;
        }
        config.open(config_file_path);
        std::string p;

        while (std::getline(config, p)) {
            if (p == ">>>>>>>>>>") {
                break;
            }

        }
        config << arg;
        *//*std::getline(config, p, '>');
        std::cout << p << std::endl;*//*
        *//*while () {
            config >> p;

        }*//*
    }
*/


    /*if (vm.count("compression")) {
        std::cout << "Compression level was set to "
             << vm["compression"].as<int>() << ".\n";
    } else {
        std::cout << "Compression level was not set.\n";
    }*/

    // delete filename_argument;

    // todo: etc - конфиг, var - бд
    // 1 аргумент - папка
    // --help
    // --history
    // --files
    // --restore
    // quit
    // --cleardb
    // --watch - следить дир
    // --remove - удалить дир
    // --ignore - игнорировать файл // todo: паттерны
    // --track - отслеживать файл
    // --delete - удалить удаленный файл
    //


    return 0;
}