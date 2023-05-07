
#include "utils.hpp"
#include "yacht_init.hpp"
#include <fstream>
#include <iostream>
#include <string>

namespace Utils {

// TODO: Add `yacht --help` message

void baseUsageMessage(void) {
    system("clear");
    std::cout << "Usage: yacht [OPTION]..." << std::endl;
    std::cout << "Try 'yacht --help' for more information." << std::endl;
}

void copyFile(std::string src_filepath, std::string dest_filepath) {
    std::string line;
    std::ifstream src{src_filepath};
    std::ofstream dst{dest_filepath};
    if (src && dst) {
        while (getline(src, line)) {
            dst << line << "\n";
        }
    } else {
        std::cout << "Error occured while copying file" << std::endl;
    }
    // Closing file
    src.close();
    dst.close();
}

CliArgs determineCliArgs(int argc, char **argv) {
    switch (argc) {
    case 1:
        return CliArgs::InvalidArg;
        break;

    case 2:
        // TODO: Match other arugments and handle them correctly (run, build)
        if (Init::cliArgIsInit(argv[1])) {
            return CliArgs::IncompleteInitArg;
        }
        break;

    case 3:
        if (Init::cliArgIsInit(argv[1]) && Init::projectNameIsValid(argv[2])) {
            return CliArgs::Init;
        } else if (Init::cliArgIsInit(argv[1])) {
            return CliArgs::InvalidInitArg;
        }
        // TODO: Add cases for other args!!
        break;
    }

    return CliArgs::InvalidArg;
}

} // namespace Utils
