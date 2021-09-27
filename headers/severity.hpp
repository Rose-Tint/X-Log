#ifndef SEVERITY_HPP
#define SEVERITY_HPP


namespace logging
{
    enum Severity : unsigned char
    {
        TEST      = 0,
        DEBUG     = 1,
        INFO      = 2,
        EXCEPTION = 3,
        ERROR     = 4,
        FATAL     = 5
    };
}

#endif