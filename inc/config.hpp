#ifndef X_LOG_CONFIG_HPP
#define X_LOG_CONFIG_HPP


#include "configs/object.hpp"
#include "configs/json.hpp"


namespace xlog
{
    using ObjectConfig = config::Object;
    using JSONConfig = config::Json;

    template<class ConfigType>
    void config(const ConfigType&);
}

#endif