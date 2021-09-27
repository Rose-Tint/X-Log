#ifndef INFO_HPP
#define INFO_HPP

#include <string>


namespace logging
{
    struct info_t
    {
        int line;
        std::string file;
    }
}

#define INFO logging::info_t { __FILE__, __LINE__ }
#endif