#ifndef X_LOG_LOGGER_HPP
#define X_LOG_LOGGER_HPP

#include "fwd_declares.hpp"
#include "filter.hpp"
#include "format.hpp"
#include "record.hpp"
#include "handler.hpp"


namespace xlog
{
    class Logger final
    {
        friend Logger& get_logger(const string_t&);

        static lookup_map<Logger> loggers;

        string_t name;
        string_t filter_name;
        std::vector<string_t> handler_names;

        std::vector<HandlerBase*> handlers(const uchar&) const;
        Filter& filter() const;

      public:
        Logger() = delete;
        Logger(const string_t&);

        static inline Format& def_fmt = get_format("std");

        void log(const string_t&, const uchar&, Record&&);
        const string_t& get_name() const { return name; }
        void add_handlers(const string_t&);
        template<class It, utils::EnableIterFor<string_t, It> = true>
        void add_handlers(It, It);
        void set_filter(const string_t&);
    };
}
#endif