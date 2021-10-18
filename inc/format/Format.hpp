#ifndef X_LOG_FORMAT_FORMAT_HPP
#define X_LOG_FORMAT_FORMAT_HPP

#include "fwd_declares.hpp"
#include "format/DateTimeFormat.hpp"


namespace xlog
{
    class Format final
    {
        friend Format& get_format(const string_t&);

        static lookup_map<Format> formats;

        string_t name;
        DateTimeFormat dtf = def_dtf;
        string_t fmt = def_fmt;

        arg_map_t get_args(const Record&) const;

      public:
        Format() = delete;
        explicit Format(const string_t&);

        static inline const DateTimeFormat def_dtf = DateTimeFormat();
        static inline const string_t def_fmt = "${date} | ${file} - ln ${line}:\n -- ${msg}";

        string_t operator()(const Record&) const;
        const string_t& get_name() const { return name; }
        void set_fmt(const string_t& format) { fmt = format; }
        void set_time(const string_t& tfmt) { dtf.time(tfmt); }
        void set_date(const string_t& tfmt) { dtf.date(dfmt); }
        void set_dtime(const string_t& tfmt) { dtf.datetime(dtfmt); }
    };
}

#endif