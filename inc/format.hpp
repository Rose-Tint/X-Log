#ifndef X_LOG_FORMAT_HPP
#define X_LOG_FORMAT_HPP

#include "fwd_declares.hpp"
#include "record.hpp"


namespace xlog
{
    typedef std::string (*var_fmt_f)(const Format&, const Record&);

    struct DateTimeFormat
    {
        std::string time;
        std::string date;
        std::string datetime = "";
        std::string get_dtime() const; // done
    };

    class Format final
    {
        friend Format& get_format(const std::string&); // done
        friend const Format& find_format(const std::string&);

        static lookup_map<Format> formats;

        // becomes usable when it gets a name to make
        // unusable when defaut constructed
        bool usable = false;
        std::string name;
        DateTimeFormat dt_fmt = def_dtf;
        std::string fmt = def_fmt;

        arg_map_t get_args(const Record&) const; // done

        Format() = default;
        Format& operator=(Format&&) = default;
        Format& operator=(const Format&) = default;
        Format(Format&&) = default;
        Format(const Format&) = default;

      public:
        explicit Format(const std::string&); // done

        static inline const DateTimeFormat def_dtf = { "H:m:S:s", "Y/M/D", "H:m:S:s - Y/M/D" }
        static inline const std::string def_fmt = "${date} | ${file} - line ${line}:\n -- ${msg}";

        std::string operator()(const Record&) const; // done?
        const std::string& get_name() const; // done

        void set_fmt(const std::string& format); // done
        void set_time(const std::string& tfmt); // done
        void set_date(const std::string& tfmt); // done
        void set_dtime(const std::string& tfmt); // done
    };
}

#endif