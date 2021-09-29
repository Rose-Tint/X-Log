#ifndef X_LOG_FORMAT_HPP
#define X_LOG_FORMAT_HPP

#include "stl_includes.hpp"
#include "errors.hpp"


namespace xlog
{
    class Format;
    struct FormatInfo
    {
        ::std::string file = "";
        int line = 0;
        ::std::unordered_map<std::string, std::string> args = { };
        int lvl = 0;
        ::std::string msg = "";
        ::std::string lgr_name = "";
    };

    typedef ::std::string (*var_fmt_f)(const Format&, const FormatInfo&);

    class Format
    {
        static inline const ::std::string def_time_fmt = "Y/M/D H:m:S:s";
            // year/month/day hour/minute/second/millisecond
        ::std::string time_fmt;
        ::std::string fmt;
        static const ::std::unordered_map<::std::string, var_fmt_f> def_fmt_args;
        static ::std::string get_time(const Format&, const FormatInfo&);

      public:
        explicit Format(::std::string format, ::std::string tfmt = def_time_fmt)
            : fmt(format), time_fmt(tfmt) { }

        Format(const Format&);
        Format& operator=(const Format&);

        ::std::string operator()(const FormatInfo&) const;

        void set_fmt(const ::std::string& format) { fmt = format; }
        void set_time_fmt(const ::std::string& tfmt) { time_fmt = tfmt; }

        static void add_var(::std::string, var_fmt_f);
    };
}
#endif