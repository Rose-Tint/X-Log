#ifndef X_LOG_FORMAT_HPP
#define X_LOG_FORMAT_HPP

#include "fwd_declares.hpp"
#include "record.hpp"


namespace xlog
{
    typedef std::string (*var_fmt_f)(const Format&, const Record&);

    struct DateTimeFormat
    {
        std::string time;
        std::string date;
        std::string date_time = std::string();
        std::string get_dtime() const;
    };

    class Format final
    {
        friend Format& get_format(const std::string&);

        // year/month/day hour/minute/second/millisecond
        static inline const std::string def_time_fmt = "H:m:S:s";
        static inline const std::string def_date_fmt = "Y/M/D";
        static inline const std::string def_fmt = "${date} | ${file} - line ${line}:\n -- ${msg}";
        static lookup_map<Format> formats;

        std::string name;
        DateTimeFormat dt_fmt;
        std::string fmt;

        arg_map_t get_args(const Record&) const;

      public:
        explicit Format(const std::string&, const std::string& = def_fmt, const DateTimeFormat& = { def_time_fmt, def_date_fmt });

        std::string operator()(const Record&) const;
        const std::string& get_name() const { return name; }

        void set_fmt(const std::string& format) { fmt = format; };
        void set_time_fmt(const std::string& tfmt) { dt_fmt.time = tfmt; };
        void set_date_fmt(const std::string& tfmt) { dt_fmt.date = tfmt; };
        void set_dtime_fmt(const std::string& tfmt) { dt_fmt.date_time = tfmt; };
    };

    Format& get_format(const std::string&);
}

#endif