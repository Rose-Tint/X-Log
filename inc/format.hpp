#ifndef X_LOG_FORMAT_HPP
#define X_LOG_FORMAT_HPP

#include "fwd_declares.hpp"
#include "record.hpp"
#include "errors.hpp"


namespace xlog
{
    typedef std::string (*var_fmt_f)(const Format&, const Record&);

    class Format final
    {
        static inline const std::string def_time_fmt = "Y/M/D H:m:S:s";
            // year/month/day hour/minute/second/millisecond
        std::string time_fmt;
        std::string fmt;
        static const std::unordered_map<std::string, var_fmt_f> def_fmt_args;
        static std::string get_time(const Format&, const Record&);

      public:
        explicit Format(std::string format, std::string tfmt = def_time_fmt)
            : fmt(format), time_fmt(tfmt) { }

        Format(const Format&);
        Format& operator=(const Format&);

        std::string operator()(const Record&) const;

        void set_fmt(const std::string& format) { fmt = format; }
        void set_time_fmt(const std::string& tfmt) { time_fmt = tfmt; }

        static void add_var(std::string, var_fmt_f);
    };
}
#endif