#ifndef X_LOG_CONFIGS_OBJECT_HPP
#define X_LOG_CONFIGS_OBJECT_HPP

#include "fwd_declares.hpp"
#include "configs/TypeConfigItf.hpp"


namespace xlog::cnfg
{
    struct Object : public ConfigTypeBase
    {
        Object& Loggers(ilist<LoggerConfigItf> lgrs)
            { loggers.insert(loggers.end(), lgrs); return *this; }
        Object& Handlers(ilist<HandlerConfigItf> hdlrs)
            { handlers.insert(handlers.end(), hdlrs); return *this; }
        Object& Filters(ilist<FilterConfigItf> fltrs)
            { filters.insert(filters.end(), fltrs); return *this; }
        Object& Formats(ilist<FormatConfigItf> fmts)
            { formats.insert(formats.end(), fmts); return *this; }
    };
}

#endif