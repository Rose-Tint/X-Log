#include "logger.hpp"


namespace xlog
{
    Logger& get_logger(const string_t& name) { return root; }
    Logger& get_logger(const string_t& name)
    {
        if (name == "" || name == "root")
            return root;
        if (!Logger::loggers.count(name))
            Logger(name);
        return Logger::loggers.at(name);
    }

    Logger::Logger(const string_t& name)
        : name(name)
    {
        loggers.insert({ name, this });
    }

    std::vector<Handler*> Logger::handlers(const uchar& lvl)
    {
        std::vector<Handler*> valids;
        for (const string_t& hname : handler_names)
        {
            Handler& handler = get_handler(hname);
            if (handler.get_min() < lvl && lvl < handler.get_max())
            {
                valids.push_back(&handler);
            }
        }
        return valids;
    }

    Logger& Logger::add_handler(const string_t& handler_name)
    {
        handler_names.push_back(handler_name);
        return *this;
    }

    Logger& Logger::add_handlers(ilist<string_t> handlers)
    {
        for (string_t hname : handlers) add_handler(hname);
        return *this;
    }

    Logger& Logger::set_filter(const string_t& handler_name)
    {
        filter_name = handler_name;
        return *this;
    }

    void Logger::log(const string_t& msg, const uchar& lvl, Record rcd)
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
