#ifndef X_LOG_CONFIGS_JSON_HPP
#defin X_LOG_CONFIGS_JSON_HPP

#include "fwd_declares.hpp"
#include "config.hpp"
#include "configs/TypeConfigItf.hpp"
#include "configs/ParserBase.hpp"
#include "configs/ValueType.hpp"


namespace xlog::cnfg
{
    class Json : public ParserBase, TypeConfigItfBase
    {
        typedef ValueType JsonType;

        ;

      public:
        Json(const fs::path);
    };
}

#endif