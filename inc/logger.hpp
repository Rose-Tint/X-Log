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
        friend void make_logger(const std::string&);
        friend Logger& get_logger(const std::string&);
        friend Logger& find_logger(const std::string&);

        static lookup_map<Logger> loggers;

        std::string name;
        bool usable = false; // becomes usable when it gets a name;
        std::vector<std::string> handler_names;

        std::vector<Handler*> handlers(const uchar&);

        Logger() = default;
        Logger(const std::string&);
        Logger(Logger&&) = delete;
        Logger& operator=(Logger&&) = default;
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = default;

      public:
        static inline Format def_fmt = Format("std");

        void log(const std::string&, const uchar&, Record);
        const std::string& get_name() const { return name; }

        // returns `*this` so that users can do things like
        // `Logger lgr = Logger().add_handler(hdlr);`
        Logger& add_handler(const std::string&);
        Logger& add_handler(const Handler&);
        Logger& add_handlers(ilist<Handler>);
        Logger& add_handlers(ilist<std::string>);
    };

    void make_logger(const std::string&);
    Logger& get_logger(const std::string&);
    Logger& find_logger(const std::string&);
}
#endif