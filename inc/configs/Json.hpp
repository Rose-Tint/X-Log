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
        void skip_ws();
        void skip_sp();
        virtual void get_value(ValueType&) override;
        virtual std::pair<ValueType, ValueType> get_key_value() override;
        virtual String get_string() override { return get_key(); }
        virtual Map get_map() override;
        virtual Array get_array() override;

      public:
        Json(const fs::path);
    };
}

#endif