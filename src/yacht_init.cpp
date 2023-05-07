#include "yacht_init.hpp"
#include "utils.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <sys/stat.h>

namespace Init {

// TODO: Add `yacht init --help` message

bool cliArgIsInit(const char *arg) { return strcmp(arg, "init") == 0; }

void initUsageMessage(void) {
    system("clear");
    std::cout << "Usage: yacht init [PROJECT_NAME]... [OPTIONS]..."
              << std::endl;
    std::cout << "Try 'yacht init --help' for more information." << std::endl;
}

bool projectNameIsValid(std::string name) {
    for (auto &c : name) {
        if (isalnum(c)) {
            continue;
        } else {
            return false;
        }
    }

    return true;
}

void initProject(std::string project_name) {
    std::cout << "Creating project `" << project_name << "`..." << std::endl;

    // Create project directory
    mkdir(project_name.c_str(), 0777);

    // Create `src` directory
    auto srcdir = project_name + "/src";
    mkdir(srcdir.c_str(), 0777);

    // Create `tests` directory
    auto testdir = project_name + "/tests";
    mkdir(testdir.c_str(), 0777);

    // Create `include` directory
    auto incdir = project_name + "/include";
    mkdir(incdir.c_str(), 0777);

    // Create `external` directory
    auto externdir = project_name + "/external";
    mkdir(externdir.c_str(), 0777);

    // Create main file
    auto mainfile = srcdir + "/" + project_name + ".cpp";
    std::ofstream outfile(mainfile);
    outfile << "int main(void) { return 0; }" << std::endl;
    outfile.close();

    // Copy `acutest` to external!
    auto acutestdir = externdir + "/acutest";
    mkdir(acutestdir.c_str(), 0777);
    // TODO: Don't hardcode acutest.h location: write program to find it given
    // the installtion directory of yacht
    Utils::copyFile("/home/aryan/Dev/Cpp/yacht/resources/acutest/acutest.h",
                    acutestdir + "/acutest.h");

    // Create `build` directory
    auto builddir = project_name + "/build";
    mkdir(builddir.c_str(), 0777);

    // TODO: Add function to create a compile_commands file!
    // This file will take care of relative includes:
    // [
    //   {
    //     "directory": "/home/aryan/Dev/Cpp/hello",
    //     "command": "c++ -I../src/utils -c ../src/hello.cpp",
    //     "file": "../src/hello.cpp",
    //   }
    // ]
    //
    // running `yacht compile` (or equivalent) will update the compile_commands
    // file with correct includes, depending on what the
    // `.mod` file in each directory includes!

    std::cout << project_name << " created!" << std::endl;
}

} // namespace Init
