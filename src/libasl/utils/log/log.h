#pragma once

#define ASL_LOG(format, ...)   asl::log(format, __VA_ARGS__)

namespace asl
{
    void log(const char* format, ...);
}
