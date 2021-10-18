#ifndef X_LOG_FORMAT_DATETIMEFORMAT_HPP
#define X_LOG_FORMAT_DATETIMEFORMAT_HPP


namespace xlog
{
    class DateTimeFormat final
    {
        string_t time_fmt;
        string_t date_fmt;
        string_t datetime_fmt;

        static inline string_t format(const string_t&, uchar = 50);

      public:
        DateTimeFormat()
            : time_fmt(def_time), date_fmt(def_date), datetime_fmt(def_datetime) { }
        DateTimeFormat(const string_t& time, const string_t& date)
            : time_fmt(time), date_fmt(date), datetime_fmt(date + " " + time) { }
        DateTimeFormat(const string_t& time, const string_t& date, const string_t& datetime)
            : time_fmt(time), date_fmt(date), datetime_fmt(datetime) { }

        static inline const string_t def_time = "[%H:%M:%S:%s]";
        static inline const string_t def_date = "%Y/%m/%e";
        static inline const string_t def_datetime = "%Y/%m/%e - [%H:%M:%S:%s]";

        string_t time() const;
        string_t date() const;
        string_t datetime() const;

        void time(const string_t&);
        void date(const string_t&);
        void datetime(const string_t&);
    };
}

#endif