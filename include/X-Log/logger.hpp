#ifndef X_LOG_LOGGER_HPP
#define X_LOG_LOGGER_HPP

#include "X-Log/stl_includes"
#include "X-Log/typedefs.hpp"
#include "X-Log/errors.hpp"
#include "X-Log/format.hpp"
#include "X-Log/handler.hpp"


namespace xlog
{
    class Logger final
    {
        friend Logger& get_logger(std::string);

        struct LogStream
        {
            std::vector<buffer_t> buffers;
            void write(const std::string&);
            ~LogStream();
        };

        static std::unordered_set<std::string> log_exts;
        static std::unordered_map<std::string&, Logger*> loggers;
        static LogStream termination_stream;
        static std::string termination_msg;
        static void termination_h();

        std::string name;
        LogStream lstream;
        Format fmt;
        std::map<Level, std::vector<Handler>> handlers;
        std::vector<fs::path> open_fpaths;

        const std::vector<Handler>& get_handlers(const Level&);

        static Format def_fmt;

      public:
        Logger() = delete;
        explicit Logger(std::string, Format = def_fmt);
        explicit Logger(std::string, fs::path, Format = def_fmt);
        explicit Logger(std::string, fs::recursive_directory_iterator, Format = def_fmt);
        explicit Logger(std::string, ilist<buffer_t>, Format = def_fmt);
        explicit Logger(std::string, ilist<fs::path>, Format = def_fmt);

        Logger(const Logger&) = delete;
        Logger(Logger&&) = delete;
        Logger& operator=(const Logger&) = delete;
        Logger& operator=(Logger&&) = delete;

        ~Logger();

        static void log_all(std::string, const Level&);
        static void add_ext(const std::string&);
        static void set_termination_stream(buffer_t);
        static void set_termination_msg(const std::string&);

        void rename(std::string);
        void register_buffer(std::streambuf*);
        void add_path(fs::path);
        void add_handler(Handler);
        void set_format(Format = def_fmt);
        void log(std::string, const Level&, FormatInfo);
    };


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
        return Logger::loggers[name];
    }

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
        : fmt(std::move(format)), name(std::move(_name))
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

    const std::vector<Handler>& Logger::get_handlers(Level lvl)
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
        log_all(termination_msg);
        old_h();
    }

    void Logger::log(std::string msg, Level lvl, FormatInfo info)
    {
        info.msg = msg.txt;
        info.lgr_name = name;
        info.lvl = lvl;

        const std::vector<Handler>& handlers = get_handler(lvl);
        for (const Handler& handle : handlers)
        {
            // if handle's filter returns false, return
            if (!handle(info)) return;
        }
        fmt(info);
        lstream.write(msg);
    }

    void Logger::log_all(std::string msg, const Level& lvl, FormatInfo info)
    {
        for (auto pair : loggers) pair.second->log(msg, lvl, info);
    }
}
#endif