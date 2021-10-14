#ifndef X_LOG_CONFIG_HPP
#define X_LOG_CONFIG_HPP

#include "fwd_declares.hpp"


namespace xlog
{
    class Config
    {
        void configure(const ConfigTypeBase&) const;

      public:
        explicit Config(const fs::path&);
        template<std::enable_if<components::config::object>>
            explicit Config(const cnfg::Object&)
    };
}

#endif