#include "yacht_init.hpp"
#include "utils.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>

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

// TODO: Use ninja instead!!
void createCompileCommands(std::string project_name) {
    char buf[8192];
    auto cwd_abs = getcwd(buf, 8192);
    auto builddir = std::string{cwd_abs} + "/" + project_name + +"/build";

    std::ofstream compile_commands(builddir + "/compile_commands.json");
    compile_commands << "[\n  {\n";

    compile_commands << "\t\t\"directory\": \"" << builddir << "\",\n";
    compile_commands << "\t\t\"command\": \"c++ -I../external/acutest/ -Wall "
                        "-Wextra -Wpedantic -std=c++14\",\n";
    compile_commands << "\t\t\"file\": \"\"";

    compile_commands << "\n  }\n]\n";
    compile_commands.close();
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
    // TODO: Create a sample test!
    auto testfile_name = testdir + "/test_" + project_name + ".cpp";
    std::ofstream testfile(testfile_name);
    testfile << "#include \"acutest.h\"\n";
    testfile << "void exampleTest(void) {\n";
    testfile << "\tint val = 1 + 1;\n";
    testfile << "\tTEST_CHECK(val == 2);\n}";
    testfile
        << "\nTEST_LIST = {{\"Example Test\", exampleTest}, {NULL, NULL}};\n";
    testfile.close();

    // Create `include` directory
    auto incdir = project_name + "/include";
    mkdir(incdir.c_str(), 0777);

    // Create `external` directory
    auto externdir = project_name + "/external";
    mkdir(externdir.c_str(), 0777);

    // Create main file
    // TODO: Only do this if type is binary! otherwise its a .hpp file
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
    createCompileCommands(project_name);

    std::cout << project_name << " created!" << std::endl;
}

} // namespace Init
