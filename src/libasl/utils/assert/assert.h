#pragma once

#define __ASL_STRINGIFY(s)  #s
#define ASL_STRINGIFY(s)    __ASL_STRINGIFY(s)

#define ASL_BREAK() \
    __debugbreak()

#define ASL_ASSERT(condition)                                                                           \
    do                                                                                                  \
    {                                                                                                   \
        if ((condition) == false)                                                                       \
        {                                                                                               \
            asl::assert_handler(ASL_STRINGIFY(condition), BOOST_CURRENT_FUNCTION, __FILE__, __LINE__);  \
            ASL_BREAK();                                                                                \
        }                                                                                               \
    } while (0)

namespace asl
{
    void assert_handler(const std::string& condition, const std::string& function, const std::string& file, unsigned int line);
}
