#include <cstring>
#include <string>

namespace Init {

bool isInit(int num_args, std::string arg) {
    return (num_args == 3) && (strcmp(arg.c_str(), "init") == 0);
}

} // namespace Init
