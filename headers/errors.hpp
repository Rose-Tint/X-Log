#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <exception>


namespace logging
{
    namespace err
    {
        class Error : public std::exception
        {
            using std::exception::exception;
        }

        class NoViableHandler : public Error
        {
            ;
        }

        class NoExistingLogger : public Error
        {
            ;
        }

        class FileCannotBeOpened : public Error
        {
            ;
        }
    }
}

#endif