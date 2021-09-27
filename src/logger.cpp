#include "headers/logger.hpp"
#include "headers/errors.hpp"


namespace logging
{
    Logger::Logger(std::string _name, Format format)
        : fmt(std::move(format)), name(std::move(_name))
    {
        loggers.insert({name, this});
    }

    Logger::Logger(std::string _name, fs::path path, Format format)
        : fmt(std::move(format)), name(std::move(_name))
    {
        loggers.insert({name, this});
        std::fstream file(path, std::ios_base::app|std::ios_base::out);
        if (!file) throw err::FileCannotBeOpened();
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
            if (!file) throw err::FileCannotBeOpened();
            register_buffer(file.rdbuf());
            open_fpaths.push_back(path);
        }
    }

    Logger::Logger(std::string _name, fs::recursive_directory_iterator dir, Format format)
        : fmt(format), name(_name)
    {
        loggers.insert({name, this});;
        for (fs::path path : dir)
        {
            if (log_exts.count(path.extension()) == 0) continue;
            std::fstream file(path, std::ios_base::app|std::ios_base::out);
            if (!file) throw err::FileCannotBeOpened();
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

    const Handler& Logger::get_handler(const Severity& level)
    {
        if (handlers.count(level) == 0) throw err::NoViableHandler();
        return handlers[level];
    }

    void Logger::add_handler(Handler h)
    {
        handlers[h.min] = h;
    }

    void Logger::set_termination_stream(buffer_t buf)
    {
        termination_stream = {{ buf }};
    }

    void Logger::set_termination_msg(const Message& msg)
    {
        termination_msg = msg;
    }

    void Logger::termination_h()
    {
        auto old_h = std::get_terminate();
        log_all(FATAL, termination_msg);
    }

    void Logger::log(const Severity& lvl, Message msg)
    {
        const Handler& handler = get_handler(lvl);
        lstream.write(handler(msg));
    }

    void Logger::log_all(const Severity& lvl, Message msg)
    {
        for (auto pair : loggers) pair.second->log(lvl, msg);
    }
}
