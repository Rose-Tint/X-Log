#ifndef X_LOG_ERRORS_HPP
#define X_LOG_ERRORS_HPP

#include "stl_includes.hpp"


namespace xlog
{
    namespace err
    {
        class Error : public ::std::exception
        {
            protected:
            static inline unsigned int idt = 0;
            static inline ::std::string indents(int n = 0) { return ::std::string(idt + n, '\t'); }
            const ::std::string msg;
            explicit Error(const ::std::string& message)
                : msg("Error:\n"+indents(1)+message) { }
            public:
            virtual const char* what() const noexcept override
            {
                return msg.c_str();
            }
        };

        class NoViableHandler : public Error
        {
            public:
            explicit NoViableHandler(const ::std::string& message)
                : Error("NoViableHandler") { }
        };

        class NoExistingLogger : public Error
        {
            public:
            explicit NoExistingLogger(const ::std::string& name)
                : Error("NoExistingLogger:\n"+indents(2)+"name ["+name+"]") { }
        };

        class FileCannotBeOpened : public Error
        {
            public:
            explicit FileCannotBeOpened(const ::std::string& fname)
                : Error("FileCannotBeOpened:\n"+indents(2)+"file ["+fname+"]") { }
        };

        class FormatArgNotFound : public Error
        {
            public:
            explicit FormatArgNotFound(const ::std::string& arg)
                : Error("FormatArgNotFound:\n"+indents(2)+"arg ["+arg+"]") { }
        };

        class InvalidArgName : public Error
        {
            public:
            explicit InvalidArgName(const ::std::string& arg)
                : Error("InvalidArgName:\n"+indents(2)+"arg ["+arg+"]") { }
        };
    }
}

#endif