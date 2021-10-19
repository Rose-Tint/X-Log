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

    std::vector<HandlerBase*> Logger::handlers(const uchar& lvl)
    {
        std::vector<HandlerBase*> valids;
        for (const string_t& hname : handler_names)
        {
            HandlerBase& handler = get_handler(hname);
            if (handler.get_min() < lvl && lvl < handler.get_max())
            {
                valids.push_back(&handler);
            }
        }
        return valids;
    }

    void Logger::add_handlers(const string_t& hname)
    {
        handler_names.insert(hname);
    }

    template<class It, utils::EnableIterFor<string_t, It>>
    void Logger::add_handlers(It begin, It end)
    {
        for (auto iter = begin; iter < end; iter++)
            handler_names.insert(iter);
    }

    void Logger::set_filter(const string_t& hname)
    {
        filter_name = hname;
    }

    void Logger::log(const string_t& msg, const uchar& lvl, Record&& rcd)
    {
        rcd.msg = msg;
        rcd.lgr = name;
        rcd.lvl = lvl;
        auto valid_handlers = handlers(lvl);
        for (HandlerBase* h_ptr : valid_handlers)
            h_ptr->handle(rcd);
    }
}
