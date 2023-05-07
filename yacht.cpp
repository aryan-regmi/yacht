#include "src/utils.hpp"
#include "src/yacht_init.hpp"
#include <cstdio>

int main(int argc, char **argv) {
    auto cliArgType = Utils::determineCliArgs(argc, argv);

    switch (cliArgType) {
    case Utils::CliArgs::Init:
        Init::initProject(argv[2]);
        break;

    case Utils::CliArgs::Build:
        // TODO: Handle case
        break;

    case Utils::CliArgs::Run:
        // TODO: Handle case
        break;

    case Utils::CliArgs::InvalidArg:
        Utils::baseUsageMessage();
        break;

    case Utils::CliArgs::InvalidInitArg:
        Init::initUsageMessage();
        printf("\n[ERROR] PROJECT_NAME must be alphanumeric\n");
        break;

    case Utils::CliArgs::IncompleteInitArg:
        Init::initUsageMessage();
        break;
    }
}
