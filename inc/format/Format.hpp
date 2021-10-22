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
        u8String fmt = def_fmt;

        arg_map_t get_args(const Record&) const;

      public:
        Format() = delete;
        explicit Format(const string_t&);

        static inline const DateTimeFormat def_dtf = DateTimeFormat();
        static inline const u8String def_fmt = "${date} | ${file} - ln ${line}:\n -- ${msg}"_u8;

        u8String operator()(const Record&) const;
        const string_t& get_name() const { return name; }
        void set_fmt(const u8String& format) { fmt = format; }
        void set_time(const u8String& tfmt) { dtf.time(tfmt); }
        void set_date(const u8String& tfmt) { dtf.date(dfmt); }
        void set_dtime(const u8String& tfmt) { dtf.datetime(dtfmt); }
    };
}

#endif