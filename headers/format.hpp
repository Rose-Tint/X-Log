#ifndef FORMAT_HPP
#define FORMAT_HPP

#include "message.hpp"


namespace logging
{
    class Format
    {
        std::string time_fmt;
        std::string fmt;
        Message& operator()(Message) const;
    };
}

#endif