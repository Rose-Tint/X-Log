#include "format/DateTimeFormat.hpp"


namespace xlog
{
    string_t DateTimeFormat::format(const string_t& str, uchar count)
    {
        std::tm time = std::local_time(nullptr);
        string_t fstr(count, ' ');
#ifdef _WIN32
        wcsftime(&fstr.data()[0], fstr.size(), &date_fmt.data()[0], &time);
#else
        strftime(&fstr.data()[0], fstr.size(), &date_fmt.data()[0], &time);
#endif
        fstr.shrink_to_fit();
        return fstr;
    }

    string_t DateTimeFormat::time()
    {
        return format(time_fmt);
    }

    string_t DateTimeFormat::date()
    {
        return format(date_fmt);
    }

    string_t DateTimeFormat::datetime()
    {
        string_t fstr = datetime_fmt;
        uchar time_idx = datetime_fmt.find("time");
        if (time_idx != string_t::npos)
            fstr.replace(time_idx, 4, time_fmt);

        uchar date_idx = datetime_fmt.find("date");
        if (date_idx != string_t::npos)
            fstr.replace(date_idx, 4, date_fmt);

        return format(fstr, 100);
    }

}
