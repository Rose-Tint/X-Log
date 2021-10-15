#ifndef X_LOG_CONFIGS_JSON_HPP
#defin X_LOG_CONFIGS_JSON_HPP

#include "fwd_declares.hpp"
#include "config.hpp"
#include "configs/TypeConfigItf.hpp"
#include "configs/ParserBase.hpp"
#include "configs/ValueType.hpp"


namespace xlog::cnfg
{
    class Json : public ParserBase, public ConfigTypeBase
    {
        virtual ValueType get_value() override;
        virtual _String get_key() override;
        virtual _String get_string() override;
        virtual _Map get_map() override;
        virtual _Array get_array() override;

      public:
        Json(const fs::path);
    };
}

#endif