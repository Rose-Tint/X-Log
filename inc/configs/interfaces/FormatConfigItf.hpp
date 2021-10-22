#ifndef X_LOG_CONFIGS_INTERFACES_FORMATCONFIGITF_HPP
#define X_LOG_CONFIGS_INTERFACES_FORMATCONFIGITF_HPP

#include "fwd_declares.hpp"
#include "configs/interfaces/ConfigItfBase.hpp"


namespace xlog::cnfg
{
    class ConfigItf : public ConfigItfBase
    {
        u8String format = Format::def_fmt;
        u8String time = Format::def_dft.time;
        u8String date = Format::def_dft.date;
        u8String datetime = Format::def_dft.datetime;

      public:
        FormatConfigItf() = default;

        const u8String& Format() const;
        const u8String& Time() const;
        const u8String& Date() const;
        const u8String& DateTime() const;

        FormatConfigItf& Format(const u8String&);
        FormatConfigItf& Time(const u8String&);
        FormatConfigItf& Date(const u8String&);
        FormatConfigItf& DateTime(const u8String&);
    };
}

#endif