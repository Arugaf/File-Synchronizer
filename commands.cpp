#include "File_Synchronizer_lib/Backend/include/ApplicationController.h"
#include "File_Synchronizer_lib/DataBase/include/FileManager.h"
#include "File_Synchronizer_lib/include/IFileManager.h"

#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int main(int ac, char** av) {
    po::options_description desc("Available arguments");
    desc.add_options()
            ("help", "Show possible arguments")
            ("history", po::value<std::string>(), "Show list of file versions")
            ("files", "Show list of tracked files")
            ("restore", po::value<std::string>(), "Restore previous version of file")
            ("cleardb", "Clear database")
            ("watch", po::value<std::string>(), "Add directory to watch")
            ("remove", po::value<std::string>(), "Stop watching directory")
            ("ignore", po::value<std::string>(), "Ignore file")
            ("track", po::value<std::string>(), "Stop ignoring file")
            ("delete", po::value<std::string>(), "Delete all versions of file")
            ;

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    if (vm.count("compression")) {
        std::cout << "Compression level was set to "
             << vm["compression"].as<int>() << ".\n";
    } else {
        std::cout << "Compression level was not set.\n";
    }

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