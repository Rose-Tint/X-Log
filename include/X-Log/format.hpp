#ifndef X_LOG_FORMAT_HPP
#define X_LOG_FORMAT_HPP

#include "X-Log/stl_includes"
#include "X-Log/typedefs.hpp"


namespace xlog
{
    struct FormatInfo
    {
        std::string file = "";
        int line = 0;
        std::string msg = "";
        std::string lgr_name = "";
        Level lvl = TEST;
    };

    typedef std::string (var_fmt_f*)(FormatInfo);

    class Format
    {
        const static std::string def_time_fmt = "Y/M/D H:m:S:s";
            // year/month/day hour/minute/second/millisecond
        std::string time_fmt;
        std::string fmt;
        static map<std::string, var_fmt_f> vars;
        std::string value_of(const std::string& var) const;
        static std::string get_ftime(FormatTime) const;

      public:
        Format(Format&&) = default;
        explicit Format(std::string, std::string = def_time_fmt);

        std::string operator()(std::string msg);
        void set_info(const info_t& inf) { info = inf; }
        static void add_var(std::string, var_fmt_f);
    };


    std::string Format::get_ftime(FormatTime) const
    {
        std::string time_s = time_fmt;
        std::time_t t = std::time(0);
        std::tm time = std::gmtime(t);
        std::timespec ts;
        std::timespec_get(&tp, TIME_UTC);
        long int ms = ts.tv_sec * 1000 + ts.tv_nsec / 1000;

        time_s.replace(time.find('Y'), 4, tm.tm_year);
        time_s.replace(time.find('M'), 2, tm.tm_mon);
        time_s.replace(time.find('D'), 2, tm.tm_mday);
        time_s.replace(time.find('H'), 2, tm.tm_hour);
        time_s.replace(time.find('m'), 2, tm.tm_min);
        time_s.replace(time.find('S'), 2, tm.tm_sec);
        time_s.replace(time.find('s'), 4, ms);
        return time_s;
    }

    std::string Format::operator()(FormatInfo info)
    {
        std::string new_msg = info.msg, curr_var = "";
        char curr = 0, last_char = 0, scd_last = 0;
        bool read = false;
        int nmsg_i = 0, r_start = 0, r_size = 0;

        for (int i = 0; i < info.msg.size(); curr = info.msg[++i])
        {
            if (read)
            {
                if (curr == '}' && last_char != '\\')
                {
                    new_msg.replace(r_start, r_size, vars[curr_var](info));
                    nmsg_i += r_size - 1;
                    read = false;
                    curr_var.clear();
                }
                else if (curr == ' ' || curr == '\t' || curr == '\n')
                {
                    throw err::InvalidArgName();
                }
                else
                {
                    curr_var += c;
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

#endif