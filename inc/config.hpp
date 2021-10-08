#ifndef X_LOG_CONFIG_HPP
#define X_LOG_CONFIG_HPP


#ifdef X_LOG_COMPONENT_CONFIG
#  ifndef X_LOG_CONFIGS_OBJECT_HPP
#    include "configs/object.hpp"
#  endif
namespace xlog { using ObjectConfig = config::Object; }
#endif

namespace xlog
{
    template<class ConfigType> void config(const ConfigType&);
}

#endif