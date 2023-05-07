#include <cctype>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sys/stat.h>

using namespace std;

// TODO: Add `yacht --help` message
// TODO: Add `yacht init --help` message

void baseUsageMessage(void) {
    system("clear");
    cout << "Usage: yacht [OPTION]..." << endl;
    cout << "Try 'yacht --help' for more information." << endl;
}

void initUsageMessage(void) {
    system("clear");
    cout << "Usage: yacht init [PROJECT_NAME]... [OPTIONS]..." << endl;
    cout << "Try 'yacht init --help' for more information." << endl;
}

bool argIsInit(char *arg) { return strcmp(arg, "init") == 0; }

void copyFile(string src_filepath, string dest_filepath) {
    string line;
    ifstream src{src_filepath};
    ofstream dst{dest_filepath};
    if (src && dst) {
        while (getline(src, line)) {
            dst << line << "\n";
        }
    } else {
        cout << "Error occured while copying file" << endl;
    }
    // Closing file
    src.close();
    dst.close();
}

void initProject(string project_name) {
    cout << "Creating project `" << project_name << "`..." << endl;

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
    ofstream outfile(mainfile);
    outfile << "int main(void) { return 0; }" << endl;
    outfile.close();

    // Copy `acutest` to external!
    auto acutestdir = externdir + "/acutest";
    mkdir(acutestdir.c_str(), 0777);
    // TODO: Don't hardcode acutest.h location: write program to find it given
    // the installtion directory of yacht
    copyFile("/home/aryan/Dev/Cpp/yacht/resources/acutest/acutest.h",
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

    cout << project_name << " created!" << endl;
}

bool isValidName(string name) {
    for (auto &c : name) {
        if (isalnum(c)) {
            continue;
        } else {
            return false;
        }
    }

    return true;
}

int main(int argc, char **argv) {
    switch (argc) {
    case 1:
        baseUsageMessage();
        break;

    case 2:
        if (argIsInit(argv[1])) {
            initUsageMessage();
        } else {
            baseUsageMessage();
        }
        break;

    case 3:
        if (argIsInit(argv[1])) {
            string project_name = argv[2];
            if (isValidName(project_name)) {
                initProject(argv[2]);
            } else {
                cout << "[ERROR] Invalid project name: must be alphanumeric"
                     << endl;
            }

        } else { // TODO: Add cases for other types
            baseUsageMessage();
        }
        break;
    }
}
