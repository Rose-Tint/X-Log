#ifndef X_LOG_CONFIGS_CONFIGTYPEBASE_HPP
#define X_LOG_CONFIGS_CONFIGTYPEBASE_HPP

#include "fwd_declares.hpp"


namespace xlog::cnfg
{
    class ConfigTypeBase
    {
        std::vector<LoggerConfigItf> loggers;
        std::vector<uptr_t<HandlerConfigItf>> handlers;
        std::vector<FormatConfigItf> formats;
        std::vector<FilterConfigItf> filters;

      protected:
        void add_logger(const Map&);
        void add_handler(const Map&);
        void add_format(const Map&);

    };
}

#endif