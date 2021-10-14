#ifndef X_LOG_CONFIGS_OBJECT_HPP
#define X_LOG_CONFIGS_OBJECT_HPP

#include "fwd_declares.hpp"
#include "configs/TypeConfigItf.hpp"


namespace xlog::cnfg
{
    struct Object : public ConfigTypeBase
    {
        void Loggers(ilist<LoggerConfigItf> lgrs)
            { loggers.insert(loggers.end(), lgrs); }
        void Handlers(ilist<HandlerConfigItf> hdlrs)
            { handlers.insert(handlers.end(), hdlrs); }
        void Filters(ilist<FilterConfigItf> fltrs)
            { filters.insert(filters.end(), fltrs); }
        void Formats(ilist<FormatConfigItf> fmts)
            { formats.insert(formats.end(), fmts); }
    };
}

#endif