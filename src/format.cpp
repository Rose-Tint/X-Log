#include "format.hpp"
#include "errors.hpp"

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

    Format& get_format(const std::string& name)
    {
        if (name == "")
        {
            return *(Format::formats["std"]);
        }
        if (Format::formats.count(name) == 0)
        {
            // throw...
        }
        return *(Format::formats[name]);
    }

    Format::Format(const std::string& _name, const std::string& format, const DateTimeFormat& dtf)
        : name(_name), fmt(format), dt_fmt(dtf)
    {
        formats.insert({ name, this });
    }

    Format::~Format()
    {
        formats.erase(name);
    }

    arg_map_t Format::get_args(const Record& rcd) const
    {
        arg_map_t new_args = rcd.get_dict();
        new_args.insert({
            { "time" , dt_fmt.time        },
            { "date" , dt_fmt.date        },
            { "dtime", dt_fmt.get_dtime() }
        });
        return new_args;
    }

    std::string Format::operator()(const Record& rcd) const
    {
        std::string new_msg, curr_var;
        char curr = 0, last_char = 0, scd_last = 0;
        bool read = false;
        int rep_start = 0, rep_size = 0;
        auto args = get_args(rcd);

        for (int i = 0; i < rcd.get_msg().size(); curr = rcd.get_msg()[++i])
        {
            if (read)
            {
                if (curr == '}' && last_char != '\\')
                {
                    if (rcd.get_args().count(curr_var) == 0)
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