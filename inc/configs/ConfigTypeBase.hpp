#ifndef X_LOG_CONFIGS_CONFIGTYPEBASE_HPP
#define X_LOG_CONFIGS_CONFIGTYPEBASE_HPP

#include "fwd_declares.hpp"


namespace xlog::cnfg
{
    class ConfigTypeBase
    {
      protected:
        std::vector<uptr_t<LoggerConfigItf>> loggers;
        std::vector<uptr_t<HandlerConfigItf>> handlers;
        std::vector<uptr_t<FormatConfigItf>> formats;
        std::vector<uptr_t<FilterConfigItf>> filters;
    };
}

#endif