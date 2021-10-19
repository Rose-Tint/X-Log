#ifndef X_LOG_CONFIGS_CONFIGTYPEBASE_HPP
#define X_LOG_CONFIGS_CONFIGTYPEBASE_HPP

#include "fwd_declares.hpp"


namespace xlog::cnfg
{
    class ConfigTypeBase
    {
      protected:
        void add_logger(const _Map&);
        void add_handler(const _Map&);
        void add_format(const _Map&);

        std::vector<LoggerConfigItf> loggers;
        std::vector<uptr_t<HandlerConfigItf>> handlers;
        std::vector<FormatConfigItf> formats;
        std::vector<FilterConfigItf> filters;
    };
}

#endif