#include "format.hpp"
#include "errors.hpp"

using std::to_string;

namespace xlog
{
    Format& get_format() { return stdfmt; }
    Format& get_format(const string_t& name)
    {
        if (name == "" || name == "std")
            return stdfmt;
        if (!Format::formats.count(name))
            Format(name);
        return Format::formats.at(name);
    }

    Format::Format(const string_t& name)
        : name(name)
    {
        formats.insert({ name, this });
    }

    arg_map_t Format::get_args(const Record& rcd) const
    {
        arg_map_t new_args = rcd.get_dict();
        new_args.insert({
            { "time" , dtf.time()     },
            { "date" , dtf.date()     },
            { "dtime", dtf.datetime() }
        });
        return new_args;
    }

    string_t Format::operator()(const Record& rcd) const
    {
        const std::size_t size = rcd.get_msg().size();
        string_t new_msg;
        string_t curr_var;
        char_t curr = 0;
        char_t last_char = 0;
        char_t scd_last = 0;
        bool read = false;
        bool is_valid_arg = true;
        const arg_map_t args = get_args(rcd);

        for (int i = 0; i < size; curr = rcd.get_msg()[++i])
        {
            if (read)
            {
                // end of arg
                if (curr == '}' && last_char != '\\')
                { 
                    if (rcd.get_args().count(curr_var) == 0)
                        throw err::FormatArgNotFound(curr_var);
                    else if (!is_valid_arg)
                        throw err::InvalidArgName(curr_var);
                    new_msg.append(args.at(curr_var));
                    read = false;
                    curr_var.clear();
                }
                else if (curr == '\t' || curr == '\n')
                    is_valid_arg = false;
                else curr_var += curr;
            }
            else if (curr == '{' && last_char == '$' && scd_last != '\\')
                read = true;
            else new_msg += curr;
            scd_last = last_char;
            last_char = curr;
        }
        return new_msg;
    }
}