#ifndef X_LOG_ERRORS_HPP
#define X_LOG_ERRORS_HPP

#include <exception>


namespace xlog
{
    namespace err
    {
        class Error : public ::std::exception
        {
            using ::std::exception::exception;
        };

        class NoViableHandler : public Error
        {
            using Error::Error;
        };

        class NoExistingLogger : public Error
        {
            using Error::Error;
        };

        class FileCannotBeOpened : public Error
        {
            using Error::Error;
        };

        class InvalidArgName : public Error
        {
            using Error::Error;
        };
    }
}

#endif