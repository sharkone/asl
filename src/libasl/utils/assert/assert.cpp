#include "precomp/precomp.h"

namespace asl
{
    void assert_handler(const std::string& condition, const std::string& function, const std::string& file, unsigned int line)
    {
        ASL_LOG("=====================================================================");
        ASL_LOG("Assertion: %s", condition.c_str());
        ASL_LOG(" Function: %s", function.c_str());
        ASL_LOG("     File: %s", file.c_str());
        ASL_LOG("     Line: %d", line);
        ASL_LOG("=====================================================================");
    }
}
