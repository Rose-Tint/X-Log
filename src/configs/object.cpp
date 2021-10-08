#include "configs/object.hpp"


namespace xlog::config
{
    Object(str_umap<std::vector<_type*>> map)
    {
        {
            if (already_configured) ;// throw...
            bool no_lgrs=1, no_hdlrs=1, no_fmts=1;

            if (map.count("Loggers") != 0)
            {
                const auto& loggers = map["Loggers"];
                if (!loggers.empty())
                {
                    no_lgrs = false;
                    for (_type* value : loggers)
                    {
                        auto lgr = dynamic_cast<_logger*>(value);
                        if (!lgr);// throw...
                        Logger(*lgr);
                    }
                }
            }

            if (map.count("Handlers") != 0)
            {
                const auto& handlers = map["Handlers"];
                if (!handlers.empty())
                {
                    no_hdlrs = false;
                    for (_type* value : handlers)
                    {
                        auto hdlr = dynamic_cast<_handler*>(value);
                        if (!hdlr);// throw...
                        Handler(*hdlr);
                    }
                }
            }

            if (map.count("Format") != 0)
            {
                const auto& formats = map["Formats"];
                if (!formats.empty())
                {
                    no_fmts = false;
                    for (_type* value : formats)
                    {
                        auto fmt = dynamic_cast<_format*>(value);
                        if (!fmt);// throw...
                        Filter(*fmt);
                    }
                }
            }

            if (no_lgrs && no_hdlrs && no_filts)
                std::cout <<
                " -- warning: Object configuration object is empty"
                << std::endl;

            already_configured = true;
        }
    }

    Object::_logger::operator Logger()
    {
        make_logger(name);
        Logger& logger = find_logger(lgr->name);
        for (std::string hname : lgr->handlers)
        {
            logger.add_handler(hname);
        }
        return logger;
    }

    Object::_handler::operator xlog::Handler()
    {
        if (min > max) std::swap(min, max);
        make_handler(name);
        Handler& handler = find_handler(name);
        handler.set_format(format);
        handler.set_min(min);
        handler.set_max(max);
        for (std::string filtname : filters)
        {
            handler.add_filter(filtname);
        }
        for (fs::path fpath : files)
        {
            handler.add_file(fpath);
        }
        return handler;
    }

    Object::_format::operator Format()
    {
        make_format(name);
        Format& format = find_format(name);
        format.set_fmt(format);
        format.set_time_fmt(time);
        format.set_date_fmt(date);
        format.set_dtime_fmt(datetime);
    }

    /*EXAMPLE
    Object configuration
    {
        { "Loggers",{
            { "main",{
                "Handlers",{
                    "std",
                    "fatal",
                    "debug",
                },
            }},
            { "secondary",{
                "Handlers",{
                    "debug",
                },
            }},
        }},
        { "Handlers"{
            { "fatal"{
                { "Format", "${dtime} Fatal Error: ${msg}" },
                { "Min", 5 },
                { "Max", -1 },
                { "Files",{
                    "logs/fatal.log",
                    "logs/all.log",
                }},
            }},
            { "debug",{
                { "Format", "" },
                { "Min", 0 },
                { "Max", -1 },
                { "Files",{
                    "logs/debug.log"
                }},
            }},
        }},
    };*/
}
