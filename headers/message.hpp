#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>

#include "severity.hpp"


namespace logging
{
    struct Message
    {
        std::string txt;
        Severity lvl;
    }
}

#endif