#ifndef X_LOG_LOGGER_HPP
#define X_LOG_LOGGER_HPP

#include "fwd_declares.hpp"
#include "format.hpp"
#include "record.hpp"
#include "handler.hpp"


namespace xlog
{
    class Logger final
    {
        friend Logger& get_logger(const std::string&);

        static lookup_map<Logger> loggers;
        static str_uset_t log_exts;
        static inline Format def_fmt = Format("std");

        std::string name;
        std::vector<std::string> handler_names;

        std::vector<Handler*> handlers(const uchar&);

      public:
        explicit Logger(const std::string&);

        Logger() = delete;
        Logger(const Logger&) = delete;
        Logger(Logger&&) = delete;
        Logger& operator=(const Logger&) = delete;
        Logger& operator=(Logger&&) = delete;

        static void add_ext(std::string);
        static void add_exts(ilist<std::string>);

        void log(const std::string&, const uchar&, Record);
        const std::string& get_name() const { return name; }

        // returns `*this` so that users can do things like
        // `Logger lgr = Logger().add_handler(hdlr);`
        Logger& add_handler(const std::string&);
        Logger& add_handler(const Handler&);
        Logger& add_handlers(ilist<Handler>);
        Logger& add_handlers(ilist<std::string>);
    };

    Logger& get_logger(const std::string&);
}
#endif