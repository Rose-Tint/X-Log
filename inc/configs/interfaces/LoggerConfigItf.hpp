#ifndef X_LOG_CONFIGS_INTERFACES_CONFIGITF_HPP
#define X_LOG_CONFIGS_INTERFACES_CONFIGITF_HPP

#include "fwd_declares.hpp"
#include "configs/interfaces/ConfigItfBase.hpp"


namespace xlog::cnfg
{
    class LoggerConfigItf : public ConfigItfBase
    {
        std::vector<string_t> handlers = { };
        string_t filter = "std";

      public:
        LoggerConfigItf() = default;

        const std::vector<string_t>& Handlers() const;
        const string_t& Filter() const;

        LoggerConfigItf& Handlers(ilist<string_t>);
        LoggerConfigItf& Filter(const string_t&);
    };
}

#endif