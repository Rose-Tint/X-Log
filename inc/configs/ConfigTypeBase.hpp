#ifndef X_LOG_CONFIGS_TYPECONFIGITF_HPP
#define X_LOG_CONFIGS_TYPECONFIGITF_HPP

#include "fwd_declares.hpp"


namespace xlog::cnfg
{
    class ConfigTypeBase
    {
      protected:
        std::vector<LoggerConfigItf> loggers;
        std::vector<HandlerConfigItf> handlers;
        std::vector<FormatConfigItf> formats;
        std::vector<FilterConfigItf> filters;
    };
}

#endif