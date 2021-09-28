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
        ::std::string msg = "";
        ::std::string lgr_name = "";
        int lvl = 0;
    };

    typedef ::std::string (*var_fmt_f)(FormatInfo);

    class Format
    {
        const static ::std::string def_time_fmt;
            // year/month/day hour/minute/second/millisecond
        ::std::string time_fmt;
        ::std::string fmt;
        static ::std::unordered_map<::std::string, var_fmt_f> vars;
        ::std::string value_of(const ::std::string& var) const;
        ::std::string get_ftime(FormatInfo) const;

      public:
        Format(const Format&) = default;
        explicit Format(::std::string, ::std::string = def_time_fmt);

        ::std::string operator()(FormatInfo);
        static void add_var(::std::string, var_fmt_f);
    };
}
#endif