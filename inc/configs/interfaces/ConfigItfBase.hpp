#ifndef X_LOG_CONFIGS_INTERFACES_CONFIGITF_HPP
#define X_LOG_CONFIGS_INTERFACES_CONFIGITF_HPP

#include "fwd_declares.hpp"
#include "configs/interfaces/ConfigItfBase.hpp"


namespace xlog::cnfg
{
    class ConfigItf
    {
        string_t name;

      public:
        ConfigItfBase() = default;
        const string_t& Name() const;
        ConfigItfBase& Name(const string_t&);
    };
}

#endif