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
        std::string date_time = std::string();
        std::string get_dtime() const;
    };

    class Format final
    {
        friend void make_format(const std::string&);
        friend Format& get_format(const std::string&);
        friend Format& find_format(const std::string&);

        static lookup_map<Format> formats;

        std::string name;
        DateTimeFormat dt_fmt = def_dtf;
        std::string fmt = def_fmt;

        arg_map_t get_args(const Record&) const;

        Format() = default;
        explicit Format(const std::string&);
        Format(Format&&) = delete;
        Format& operator=(Format&&) = default;
        Format(const Format&) = delete;
        Format& operator=(const Format&) = default;

      public:
        static inline const DateTimeFormat def_dtf = { "H:m:S:s", "Y/M/D", "H:m:S:s - Y/M/D" }
        static inline const std::string def_fmt = "${date} | ${file} - line ${line}:\n -- ${msg}";

        std::string operator()(const Record&) const;
        const std::string& get_name() const { return name; }

        void set_fmt(const std::string& format) { fmt = format; };
        void set_time_fmt(const std::string& tfmt) { dt_fmt.time = tfmt; };
        void set_date_fmt(const std::string& tfmt) { dt_fmt.date = tfmt; };
        void set_dtime_fmt(const std::string& tfmt) { dt_fmt.date_time = tfmt; };
    };

    void make_format(const std::string&);
    Format& get_format(const std::string&);
    Format& find_format(const std::string&);
}

#endif