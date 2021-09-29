#include "format.hpp"

using std::to_string;

namespace xlog
{
    const ::std::unordered_map<::std::string, var_fmt_f> Format::def_fmt_args
    {
        { "time", &Format::get_time },
        { "msg" , [](const Format&, const FormatInfo& info){ return info.msg; } },
        { "lvl" , [](const Format&, const FormatInfo& info){ return to_string(info.lvl); } },
        { "file", [](const Format&, const FormatInfo& info){ return info.file; } },
        { "line", [](const Format&, const FormatInfo& info){ return to_string(info.line); } },
        { "lgr" , [](const Format&, const FormatInfo& info){ return info.lgr_name; } },
    };

    Format::Format(const Format& other)
    {
        set_fmt(other.fmt);
        set_time_fmt(other.time_fmt);
    }

    Format& Format::operator=(const Format& other)
    {
        if (this == &other) return *this;
        set_fmt(other.fmt);
        set_time_fmt(other.time_fmt);
        return *this;
    }

    ::std::string Format::get_time(const Format& fmt, const FormatInfo&)
    {
        ::std::string time_s = fmt.time_fmt;
        ::std::time_t t = ::std::time(0);
        ::std::tm tm = *::std::gmtime(&t);
        ::std::timespec ts;
        ::std::timespec_get(&ts, TIME_UTC);
        long int ms = ts.tv_sec * 1000 + ts.tv_nsec / 1000;

        time_s.replace(time_s.find('Y'), 4, to_string(tm.tm_year));
        time_s.replace(time_s.find('M'), 2, to_string(tm.tm_mon));
        time_s.replace(time_s.find('D'), 2, to_string(tm.tm_mday));
        time_s.replace(time_s.find('H'), 2, to_string(tm.tm_hour));
        time_s.replace(time_s.find('m'), 2, to_string(tm.tm_min));
        time_s.replace(time_s.find('S'), 2, to_string(tm.tm_sec));
        time_s.replace(time_s.find('s'), 4, to_string(ms));

        return time_s;
    }

    ::std::string Format::operator()(const FormatInfo& info) const
    {
        ::std::string new_msg = info.msg, curr_var = "";
        char curr = 0, last_char = 0, scd_last = 0;
        bool read = false;
        int nmsg_i = 0, r_start = 0, r_size = 0;
        ::std::unordered_map<std::string, std::string> fmt_args = info.args;
        for (auto pair : def_fmt_args)
        {
            fmt_args.insert({ pair.first, pair.second(*this, info) });
        }

        for (int i = 0; i < info.msg.size(); curr = info.msg[++i])
        {
            if (read)
            {
                if (curr == '}' && last_char != '\\')
                {
                    if (fmt_args.count(curr_var) == 0)
                    {
                        throw err::FormatArgNotFound(curr_var);
                    }
                    new_msg.replace(r_start, r_size, fmt_args[curr_var]);
                    nmsg_i += r_size - 1;
                    read = false;
                    curr_var.clear();
                }
                else if (curr == ' ' || curr == '\t' || curr == '\n')
                {
                    throw err::InvalidArgName(curr_var);
                }
                else
                {
                    curr_var += curr;
                    r_size += 1;
                }
            }
            else if (curr == '{' && last_char == '$' && scd_last != '\\')
            {
                read = true;
                r_start = nmsg_i - 1;
            }
            scd_last = last_char;
            last_char = curr;
            nmsg_i += 1;
        }
        return new_msg;
    }
}