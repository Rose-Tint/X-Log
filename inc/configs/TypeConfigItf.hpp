#ifndef X_LOG_CONFIGS_CONFIG_TYPES_HPP
#define X_LOG_CONFIGS_CONFIG_TYPES_HPP

#include "fwd_declares.hpp"


namespace xlog::config
{
    struct TypeConfigItfBase
    {
        std::string name;
    };

    struct LoggerConfigItf : TypeConfigItfBase
    {
        std::vector<std::string> handlers = { };
    };

    struct HandlerConfigItf : TypeConfigItfBase
    {
        std::string format = "std";
        uchar min = 0;
        uchar max = -1;
        std::vector<fs::path> files = { };
    };

    struct FormatConfigItf : TypeConfigItfBase
    {
        std::string fmt = Format::def_fmt;
        std::string time = Format::def_dft.time;
        std::string date = Format::def_dft.date;
        std::string datetime = Format::def_dft.datetime;
    };

    struct FilterConfigItf : TypeConfigItfBase
    {
        pre_filter_f prefilter = nullptr;
        filter_f filter = Filter::def_filter;
        post_filter_f postfilter = nullptr;
    };

    class ConfigType
    {
      protected:
        std::vector<LoggerConfigItf> loggers;
        std::vector<HandlerConfigItf> handlers;
        std::vector<FormatConfigItf> formats;
        std::vector<FilterConfigItf> filters;
    };
}

#endif