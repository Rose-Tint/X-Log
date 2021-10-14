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
        friend const Logger& find_logger(const std::string&);

        static lookup_map<Logger> loggers;

        std::string name;
        std::string filter_name;
        std::vector<std::string> handler_names;

        std::vector<Handler*> handlers(const uchar&); // done

      public:
        Logger() = delete;
        Logger(const std::string&); // done

        static inline Format def_fmt = Format("std");

        void log(const std::string&, const uchar&, Record); // done
        const std::string& get_name() const { return name; }

        Logger& add_handler(const std::string&); // done
        Logger& add_handlers(ilist<std::string>); // done
        Logger& set_filter(const std::string&); // done
    };
}
#endif