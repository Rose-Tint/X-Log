#ifndef X_LOG_CONFIGS_INTERFACES_CONFIGITF_HPP
#define X_LOG_CONFIGS_INTERFACES_CONFIGITF_HPP

#include "fwd_declares.hpp"
#include "configs/interfaces/ConfigItfBase.hpp"


namespace xlog::cnfg
{
    class ConfigItf : public ConfigItfBase
    {
        string_t format = Format::def_fmt;
        string_t time = Format::def_dft.time;
        string_t date = Format::def_dft.date;
        string_t datetime = Format::def_dft.datetime;

      public:
        FormatConfigItf() = default;

        const string_t& Format() const;
        const string_t& Time() const;
        const string_t& Date() const;
        const string_t& DateTime() const;

        FormatConfigItf& Format(const string_t&);
        FormatConfigItf& Time(const string_t&);
        FormatConfigItf& Date(const string_t&);
        FormatConfigItf& DateTime(const string_t&);
    };
}

#endif