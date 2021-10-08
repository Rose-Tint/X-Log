#include "configs/object.hpp"


namespace xlog::config
{
    Object(str_umap<std::vector<_type*>> map)
    {
        {
            bool no_lgrs=1, no_hdlrs=1, no_filt=1, no_fmts=1;

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
                        Logger& logger = (Logger)(*lgr);
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
                        Handler& handler = (Handler)(*hdlr);
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
                        Filter& filter = (Filter)(*fmt);
                    }
                }
            }
        }
    }

    Object::_logger::operator Logger()
    {
        xlog::Logger& logger = get_logger(lgr->name);
        for (std::string hname : lgr->handlers)
        {
            logger.add_handler(hname);
        }
        return logger;
    }

    Object::_handler::operator xlog::Handler&()
    {
        if (min > max) std::swap(min, max);
        Handler& handler = get_handler(name);
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

    Object::_format::operator Format&()
    {
        Format& format = get_format(name);
    }
}
