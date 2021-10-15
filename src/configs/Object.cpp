#include "configs/Object.hpp"


namespace xlog::cnfg
{
    void Object::Loggers(ilist<LoggerConfigItf> lgrs)
    {
        loggers.insert(loggers.end(), lgrs);
    }
}
