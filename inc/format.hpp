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
        static inline const std::string def_time_fmt = "Y/M/D H:m:S:s";
            // year/month/day hour/minute/second/millisecond
        DateTimeFormat dt_fmt;
        std::string fmt;

        arg_map_t get_args(const Record&) const;

      public:
        typedef str_umap<std::string> arg_map_t;
        explicit Format(std::string format, std::string dtf = def_time_fmt)
            : fmt(format), dt_fmt(dtf) { }

        std::string operator()(const Record&) const;

        void set_fmt(const std::string& format) { fmt = format; };
        void set_time_fmt(const std::string& tfmt) { time_fmt = tfmt; };
    };
}

#endif