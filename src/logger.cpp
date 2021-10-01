#include "logger.hpp"


namespace xlog
{
    std::unordered_map<std::string&, Logger*> Logger::loggers = { };

    std::unordered_set<std::string> Logger::log_exts = { ".log", ".xlog" };

    void Logger::LogStream::write(const std::string& str)
    {
        for (buffer_t buf : buffers)
        {
            std::ostream stream = std::ostream(buf);
            stream << str;
        }
    }

    Logger& get_logger(std::string name)
    {
        if (Logger::loggers.count(name) == 0)
        {
            Logger new_lgr = Logger(name);
        }
        return *(Logger::loggers[name]);
    }

    Logger::Logger(std::string _name, Format format)
        : fmt(std::move(format)), name(std::move(_name))
    {
        loggers.insert({name, this});
    }

    Logger::Logger(std::string _name, buffer_t buf, Format format)
        : fmt(std::move(format)), name(std::move(_name))
    {
        loggers.insert({name, this});
        register_buffer(buf);
    }

    Logger::Logger(std::string _name, fs::path path, Format format)
        : fmt(std::move(format)), name(std::move(_name))
    {
        loggers.insert({name, this});
        std::fstream file(path, std::ios_base::app|std::ios_base::out);
        if (!file) throw err::FileCannotBeOpened(path.filename().string());
        register_buffer(file.rdbuf());
        open_fpaths.push_back(path);
    }

    Logger::Logger(std::string _name, ilist<buffer_t> bufs, Format format)
        : fmt(std::move(format)), name(std::move(_name))
    {
        loggers.insert({name, this});
        for (auto buf : bufs) register_buffer(buf);
    }

    Logger::Logger(std::string _name, ilist<fs::path> paths, Format format)
        : fmt(std::move(format)), name(std::move(_name))
    {
        loggers.insert({name, this});
        for (fs::path path : paths)
        {
            std::fstream file(path, std::ios_base::app|std::ios_base::out);
            if (!file) throw err::FileCannotBeOpened(path.filename().string());
            register_buffer(file.rdbuf());
            open_fpaths.push_back(path);
        }
    }

    Logger::Logger(std::string _name, fs::recursive_directory_iterator dir, Format format)
        : fmt(std::move(format)), name(std::move(_name))
    {
        loggers.insert({name, this});;
        for (fs::path path : dir)
        {
            if (log_exts.count(path.extension().string()) == 0) continue;
            std::fstream file(path, std::ios_base::app|std::ios_base::out);
            if (!file) throw err::FileCannotBeOpened(path.filename().string());
            register_buffer(file.rdbuf());
            open_fpaths.push_back(path);
        }
    }

    Logger::LogStream::~LogStream()
    {
        std::filebuf* fbuf;
        for (buffer_t buf : buffers)
        {
            fbuf = dynamic_cast<std::filebuf*>(buf);
            if (fbuf)
            {
                if (fbuf->is_open()) fbuf->close();
            }
        }
    }

    void Logger::register_buffer(std::streambuf* buff)
    {
        lstream.buffers.push_back(buff);
    }

    const std::vector<Handler>& Logger::get_handlers(const int& lvl)
    {
        if (handlers.count(lvl) == 0)
        {
            throw err::NoViableHandler(std::to_string(lvl));
        }
        return handlers[lvl];
    }

    void Logger::add_handler(Handler h)
    {
        handlers[h.get_lvl()].push_back(h);
    }

    void Logger::set_termination_stream(buffer_t buf)
    {
        termination_stream = {{ buf }};
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

    void Logger::add_ext(std::string ext)
    {
        if (ext[0] != '.')
        {
            ext.insert(0, 1, '.');
        }
        log_exts.insert(ext);
    }

    void Logger::exc_log(const std::string& msg, const int& lvl, FormatInfo& info)
    {
        lock_gaurd_t lock(log_mtx);

        info.msg = msg;
        info.lgr_name = name;
        info.lvl = lvl;
        const std::vector<Handler>& handlers = get_handlers(lvl);
        for (const Handler& handle : handlers)
        {
            // if handle's filter returns false, return
            if (!handle(info))
            {
                return;
            }
        }

        lstream.write(fmt(info));
    }

    void Logger::log(const std::string& msg, const int& lvl, FormatInfo info)
    {
        thread_t thread(&exc_log, msg, lvl, info);
        thread.detach();
    }

    void Logger::log_all(std::string msg, const int& lvl, FormatInfo info)
    {
        for (auto pair : loggers)
        {
            pair.second->log(msg, lvl, info);
        }
    }
}
