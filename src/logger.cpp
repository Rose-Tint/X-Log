#include "logger.hpp"


namespace xlog
{
    std::unordered_set<std::string> Logger::log_exts = { ".log", ".xlog" };

    Logger& get_logger(const std::string& name)
    {
        if (Logger::loggers.count(name) == 0)
        {
            Logger new_lgr = Logger(name);
        }
        return *(Logger::loggers[name]);
    }

    Logger::Logger(const std::string& nm)
        : name(nm)
    {
        loggers.insert({name, this});
    }

    std::vector<Handler*> Logger::get_handlers(const uchar& lvl)
    {
        std::vector<Handler*> valids;
        for (Handler& handler : handlers)
        {
            if (handler.get_min() < lvl && lvl < handler.get_max())
            {
                valids.push_back(&handler);
            }
        }
        return valids;
    }

    Logger& Logger::add_handler(const Handler& handler)
    {
        handlers.push_back(handler);
        return *this;
    }

    Logger& Logger::add_handlers(ilist<Handler&> handlers)
    {
        for (const Handler& handler : handlers) add_handler(handler);
    }

    Logger& Logger::set_termination_stream(buffer_t buf)
    {
        termination_stream = {{ buf }};
        return *this;
    }

    void Logger::set_termination_msg(const std::string& msg)
    {
        termination_msg = msg;
    }

    void Logger::termination_h()
    {
        auto old_h = std::get_terminate();
        log_all(termination_msg, 100, {});
        old_h();
    }

    void Logger::add_ext(const std::string& ext)
    {
        if (ext[0] != '.') ext.insert(0, 1, ".");
        log_exts.insert(ext);
    }

    void Logger::add_exts(ilist<std::string&> exts)
    {
        for (const std::string& ext : exts) add_ext(ext);
    }

    void Logger::log(const std::string& msg, const uchar& lvl, Record rcd)
    {
        rcd.init_rest(msg, lvl, name);
        auto& valid_handlers = get_handlers(lvl);
        for (Handler* h_ptr : valid_handlers)
        {
            h_ptr->handle(rcd);
        }
    }

    void Logger::log_all(const std::string& msg, const uchar& lvl, Record rcd)
    {
        for (auto pair : loggers) pair.second->log(msg, lvl, rcd);
    }
}
