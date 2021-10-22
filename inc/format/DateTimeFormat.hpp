#ifndef X_LOG_FORMAT_DATETIMEFORMAT_HPP
#define X_LOG_FORMAT_DATETIMEFORMAT_HPP


namespace xlog
{
    class DateTimeFormat final
    {
        u8String time_fmt;
        u8String date_fmt;
        u8String datetime_fmt;

        static inline u8String format(const u8String&, uchar = 50);

      public:
        DateTimeFormat()
            : time_fmt(def_time), date_fmt(def_date), datetime_fmt(def_datetime) { }
        DateTimeFormat(const u8String& time, const u8String& date)
            : time_fmt(time), date_fmt(date), datetime_fmt(date + " " + time) { }
        DateTimeFormat(const u8String& time, const u8String& date, const u8String& datetime)
            : time_fmt(time), date_fmt(date), datetime_fmt(datetime) { }

        static inline const u8String def_time = "[%H:%M:%S:%s]";
        static inline const u8String def_date = "%Y/%m/%e";
        static inline const u8String def_datetime = "%Y/%m/%e - [%H:%M:%S:%s]";

        u8String time() const;
        u8String date() const;
        u8String datetime() const;

        void time(const u8String&);
        void date(const u8String&);
        void datetime(const u8String&);
    };
}

#endif