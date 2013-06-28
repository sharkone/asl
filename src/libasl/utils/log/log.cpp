#include "precomp/precomp.h"

namespace asl
{
    void log(const char* format, ...)
    {
        std::va_list args;
        va_start(args, format);
        std::vprintf(format, args);
        std::printf("\n");
    }
}
