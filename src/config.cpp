#include "config.hpp"


namespace xlog
{
    template<class ConfigType>
    void config(const ConfigType&)
    {
        // throw...
    }

    template<>
    void config<config::Object>(const config::Object& obj)
    {
        if (obj)
        bool no_lgrs=1, no_hdlrs=1, no_filters=1, no_formats=1;
        if (obj.count("loggers") != 0)
        {
            const auto& loggers = obj["loggers"];
            if (!loggers.empty())
            {
                no_lgrs = false;
            }
            else
            {
                for (auto lgr : loggers)
                {
                    xlog::Logger& logger = get_logger(lgr.name);
                    for (std::string hname : lgr.handlers)
                    {
                        logger.add_handler(hname);
                    }
                }
            }
        }

        if (obj.count("handlers"))
    }
}
