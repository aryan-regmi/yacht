
#include <string>

namespace Utils {

void baseUsageMessage(void);

void copyFile(std::string src_filepath, std::string dest_filepath);

enum class CliArgs {
    Init,
    Build,
    Run,
    InvalidArg,
    InvalidInitArg,
    IncompleteInitArg
};

CliArgs determineCliArgs(int argc, char **argv);

} // namespace Utils
