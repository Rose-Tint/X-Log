#include "logger.hpp"


namespace xlog
{
    ::std::unordered_map<::std::string&, Logger*> Logger::loggers = { };

    ::std::unordered_set<std::string> Logger::log_exts = { ".log", ".xlog" }

    Format Logger::def_fmt = Format("${date} | ${file} - line ${line}: ${msg}");

    void Logger::LogStream::write(const ::std::string& str)
    {
        for (buffer_t buf : buffers)
        {
            ::std::ostream stream = ::std::ostream(buf);
            stream << str;
        }
    }

    Logger& get_logger(::std::string name)
    {
        if (Logger::loggers.count(name) == 0)
        {
            Logger new_lgr = Logger(name);
        }
        return *(Logger::loggers[name]);
    }

    Logger::Logger(::std::string _name, Format format)
        : fmt(::std::move(format)), name(::std::move(_name))
    {
        loggers.insert({name, this});
    }

    Logger::Logger(::std::string _name, buffer_t buf, Format format)
        : fmt(::std::move(format)), name(::std::move(_name))
    {
        loggers.insert({name, this});
        register_buffer(buf);
    }

    Logger::Logger(::std::string _name, fs::path path, Format format)
        : fmt(::std::move(format)), name(::std::move(_name))
    {
        loggers.insert({name, this});
        ::std::fstream file(path, ::std::ios_base::app|::std::ios_base::out);
        if (!file) throw err::FileCannotBeOpened();
        register_buffer(file.rdbuf());
        open_fpaths.push_back(path);
    }

    Logger::Logger(::std::string _name, ilist<buffer_t> bufs, Format format)
        : fmt(::std::move(format)), name(::std::move(_name))
    {
        loggers.insert({name, this});
        for (auto buf : bufs) register_buffer(buf);
    }

    Logger::Logger(::std::string _name, ilist<fs::path> paths, Format format)
        : fmt(::std::move(format)), name(::std::move(_name))
    {
        loggers.insert({name, this});
        for (fs::path path : paths)
        {
            ::std::fstream file(path, ::std::ios_base::app|::std::ios_base::out);
            if (!file) throw err::FileCannotBeOpened();
            register_buffer(file.rdbuf());
            open_fpaths.push_back(path);
        }
    }

    Logger::Logger(::std::string _name, fs::recursive_directory_iterator dir, Format format)
        : fmt(::std::move(format)), name(::std::move(_name))
    {
        loggers.insert({name, this});;
        for (fs::path path : dir)
        {
            if (log_exts.count(path.extension().string()) == 0) continue;
            ::std::fstream file(path, ::std::ios_base::app|::std::ios_base::out);
            if (!file) throw err::FileCannotBeOpened();
            register_buffer(file.rdbuf());
            open_fpaths.push_back(path);
        }
    }

    Logger::LogStream::~LogStream()
    {
        ::std::filebuf* fbuf;
        for (buffer_t buf : buffers)
        {
            fbuf = dynamic_cast<::std::filebuf*>(buf);
            if (fbuf)
            {
                if (fbuf->is_open()) fbuf->close();
            }
        }
    }

    void Logger::register_buffer(::std::streambuf* buff)
    {
        lstream.buffers.push_back(buff);
    }

    const ::std::vector<Handler>& Logger::get_handlers(const int& lvl)
    {
        if (handlers.count(lvl) == 0)
        {
            throw err::NoViableHandler();
        }
        return handlers[lvl];
    }

    void Logger::add_handler(Handler h)
    {
        handlers[h.min].push_back(h);
    }

    Logger::LogStream termination_stream = { std::cout.rdbuf() }

    void Logger::set_termination_stream(buffer_t buf)
    {
        termination_stream = {{ buf }};
    }

    std::string Logger::termination_msg = "Program terminated\n";

    void Logger::set_termination_msg(const ::std::string& msg)
    {
        termination_msg = msg;
    }

    void Logger::termination_h()
    {
        auto old_h = ::std::get_terminate();
        log_all(termination_msg, 100, {});
        old_h();
    }

    void Logger::add_ext(std::string ext)
    {
        if (ext[0] != '.')
        {
            ext.insert(0, 1, ".");
        }
        log_exts.insert(ext);
    }

    void Logger::log(::std::string msg, const int& lvl, FormatInfo info)
    {
        info.msg = msg;
        info.lgr_name = name;
        info.lvl = lvl;

        const ::std::vector<Handler>& handlers = get_handlers(lvl);
        for (const Handler& handle : handlers)
        {
            // if handle's filter returns false, return
            if (!handle(info)) return;
        }
        msg = fmt(info);
        lstream.write(info.msg);
    }

    void Logger::log_all(::std::string msg, const int& lvl, FormatInfo info)
    {
        for (auto pair : loggers)
        {
            pair.second->log(msg, lvl, info);
        }
    }
}
