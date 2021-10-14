#include "format.hpp"
#include "errors.hpp"

using std::to_string;

namespace xlog
{
    std::string DateTimeFormat::get_dtime() const
    {
        if (date_time.empty())
            return (date+" "+time);
        else return date_time;
    }
    
    Format& get_format()
    {
        return stdfmt;
    }

    Format& get_format(const std::string& name)
    {
        if (name == "" || name == "std")
            return stdfmt;
        if (Format::formats.count(name))
            Format(name);
        return Format::formats.at(name);
    }

    const Format& find_format()
    {
        return stdfmt;
    }

    const Format& find_format(const std::string& name)
    {
        if (name == "" || name == "std")
            return stdfmt;
        auto iter = Format::formats.find(name);
        if (iter == Format::formats.end())
            ;// throw...
        return iter->second;
    }

    Format::Format(const std::string& name)
        : name(name), usable(true)
    {
        if (formats.count(name) != 0)
            ;// throw
        formats.insert({ name, this });
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

    const std::string& Format::get_name() const
    {
        return name;
    }

    void set_fmt(const std::string& format)
    {
        fmt = format;
    }

    void set_time(const std::string& tfmt)
    {
        dt_fmt.time = tfmt;
    }

    void set_date(const std::string& dfmt)
    {
        dt_fmt.date = dfmt;
    }

    void set_dtime(const std::string& dtfmt)
    {
        dt_fmt.datetime = dtfmt;
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