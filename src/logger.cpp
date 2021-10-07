#include "logger.hpp"


namespace xlog
{
    Logger& get_logger(const std::string& name)
    {
        if (name == "")
        {
            return *Logger::loggers["root"];
        }
        if (Logger::loggers.count(name) == 0)
        {
            Logger new_lgr = Logger(name);
        }
        return *Logger::loggers[name];
    }

    str_uset_t Logger::log_exts = { ".log", ".xlog" };

    Logger::Logger(const std::string& nm)
        : name(nm)
    {
        loggers.insert({ name, this });
    }

    Logger::~Logger()
    {
        loggers.erase(name);
    }

    std::vector<Handler*> Logger::handlers(const uchar& lvl)
    {
        std::vector<Handler*> valids;
        for (const std::string& hname : handler_names)
        {
            Handler& handler = xlog::get_handler(hname);
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

    Logger& Logger::add_handler(const Handler& handler)
    {
        handler_names.push_back(handler.get_name());
        return *this;
    }

    Logger& Logger::add_handlers(ilist<Handler> handlers)
    {
        for (const Handler& handler : handlers) add_handler(handler.get_name());
        return *this;
    }

    Logger& Logger::add_handlers(ilist<std::string> handlers)
    {
        for (std::string hname : handlers) add_handler(hname);
        return *this;
    }

    void Logger::add_ext(std::string ext)
    {
        if (ext[0] != '.') ext.insert(0, 1, '.');
        log_exts.insert(ext);
    }

    void Logger::add_exts(ilist<std::string> exts)
    {
        for (const std::string& ext : exts) add_ext(ext);
    }

    void Logger::log(const std::string& msg, const uchar& lvl, Record rcd)
    {
        rcd.init_rest(msg, name, lvl);
        auto& valid_handlers = handlers(lvl);
        for (Handler* h_ptr : valid_handlers)
        {
            h_ptr->handle(rcd);
        }
    }
}
