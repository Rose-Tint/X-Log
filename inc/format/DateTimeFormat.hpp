#ifndef X_LOG_FORMAT_DATETIMEFORMAT_HPP
#define X_LOG_FORMAT_DATETIMEFORMAT_HPP


namespace xlog
{
    struct DateTimeFormat final
    {
        string_t time;
        string_t date;
        string_t datetime = "";
        string_t get_dtime() const;
    };
}

#endif