#include "logger.hpp"


namespace xlog
{
    Logger& get_logger(const std::string& name)
    {
        return root;
    }

    Logger& get_logger(const std::string& name)
    {
        if (name == "" || name == "root")
            return root;
        if (Logger::loggers.count(name) == 0)
            Logger(name);
        return Logger::loggers.at(name);
    }

    const Logger& find_logger()
    {
        return root;
    }

    const Logger& find_logger(const std::string& name)
    {
        if (name == "" || name == "root")
            return root;
        auto iter = Logger::loggers.find(name);
        if (iter == Logger::loggers.end())
            ;//throw...
        return iter->second;
    }

    Logger::Logger(const std::string& nm)
        : name(nm), usable(true)
    {
        if (loggers.count(name))
            ;// throw...
        loggers.insert({ name, this });
    }

    std::vector<Handler*> Logger::handlers(const uchar& lvl)
    {
        std::vector<Handler*> valids;
        for (const std::string& hname : handler_names)
        {
            Handler& handler = get_handler(hname);
            if (handler.get_min() < lvl && lvl < handler.get_max())
            {
                valids.push_back(&handler);
            }
        }
        return valids;
    }

    Logger& Logger::add_handler(const std::string& handler_name)
    {
        handler_names.push_back(handler_name);
        return *this;
    }

    Logger& Logger::add_handlers(ilist<std::string> handlers)
    {
        for (std::string hname : handlers) add_handler(hname);
        return *this;
    }

    Logger& Logger::set_filter(const std::string& handler_name)
    {
        filter_name = handler_name;
        return *this;
    }

    void Logger::log(const std::string& msg, const uchar& lvl, Record rcd)
    {
        rcd.msg = msg;
        rcd.lgr = lgr;
        rcd.lvl = lvl;
        auto valid_handlers = handlers(lvl);
        for (Handler* h_ptr : valid_handlers)
        {
            h_ptr->handle(rcd);
        }
    }
}
