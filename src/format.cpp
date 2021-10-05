#include "format.hpp"

using std::to_string;

namespace xlog
{
    std::string DateTimeFormat::get_dtime() const
    {
        if (date_time.empty())
        {
            return (date+" "+time);
        }
        else
        {
            return date_time;
        }
    }

    std::string Format::get_time(const Format& fmt, const Record&)
    {
        std::string time_s = fmt.time_fmt;
        std::time_t t = std::time(0);
        std::tm tm = *std::gmtime(&t);
        std::timespec ts;
        std::timespec_get(&ts, TIME_UTC);
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

    str_umap Format::get_args(const Record& rcd) const
    {
        str_umap new_args = rcd.get_dict();
        new_args.merge({
            { "time" , dt_fmt.time        },
            { "date" , dt_fmt.date        },
            { "dtime", dt_fmt.get_dtime() }
        });
        return new_args;
    }

    std::string Format::operator()(const Record& rec) const
    {
        std::string new_msg, curr_var;
        char curr = 0, last_char = 0, scd_last = 0;
        bool read = false;
        int rep_start = 0, rep_size = 0;
        str_umap args = get_args(rcd);

        for (int i = 0; i < rec.msg.size(); curr = rec.msg[++i])
        {
            if (read)
            {
                if (curr == '}' && last_char != '\\')
                {
                    if (rec.args.count(curr_var) == 0)
                    {
                        throw err::FormatArgNotFound(curr_var);
                    }
                    new_msg.replace(rep_start, rep_size, args[curr_var]);
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
                    rep_size += 1;
                }
            }
            else if (curr == '{' && last_char == '$' && scd_last != '\\')
            {
                read = true;
                rep_start = nmsg_i - 1;
            }
            else
            {
                new_msg += curr;
            }
            scd_last = last_char;
            last_char = curr;
        }
        return new_msg;
    }
}