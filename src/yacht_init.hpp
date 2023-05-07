
#include <string>

namespace Init {

bool cliArgIsInit(const char *arg);

void initUsageMessage(void);

bool projectNameIsValid(std::string name);

void initProject(std::string project_name);

} // namespace Init
