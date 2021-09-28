#ifndef X_LOG_FORMAT_HPP
#define X_LOG_FORMAT_HPP

#include "stl_includes.hpp"
#include "errors.hpp"


namespace xlog
{
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
        const static ::std::string def_time_fmt;
            // year/month/day hour/minute/second/millisecond
        const ::std::string time_fmt;
        const ::std::string fmt;
        const static ::std::unordered_map<std::string, std::string> def_fmt_args;
        static ::std::string get_ftime(const Format&, FormatInfo);

      public:
        Format(const Format&) = default;
        explicit Format(::std::string format, ::std::string tfmt = def_time_fmt)
            : fmt(format), time_fmt(tfmt) { }

        ::std::string operator()(FormatInfo) const;
        static void add_var(::std::string, var_fmt_f);
    };
}
#endif