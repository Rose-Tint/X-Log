#ifndef X_LOG_ERRORS_HPP
#define X_LOG_ERRORS_HPP

#include <exception>


namespace xlog
{
    namespace err
    {
        class Error : public ::std::exception
        {
            ;
        };

        class NoViableHandler : public Error
        {
            ;
        };

        class NoExistingLogger : public Error
        {
            ;
        };

        class FileCannotBeOpened : public Error
        {
            ;
        };

        class FormatArgNotFound : public Error
        {
            ;
        }

        class InvalidArgName : public Error
        {
            ;
        };
    }
}

#endif