#ifndef X_LOG_LOGGER_HPP
#define X_LOG_LOGGER_HPP

#include "stl_includes.hpp"
#include "errors.hpp"
#include "format.hpp"
#include "handler.hpp"


namespace xlog
{
    class Logger final
    {
        friend Logger& get_logger(::std::string);

        struct LogStream
        {
            ::std::vector<buffer_t> buffers;
            void write(const ::std::string&);
            ~LogStream();
        };

        static ::std::unordered_set<::std::string> log_exts;
        static ::std::unordered_map<::std::string&, Logger*> loggers;
        static LogStream termination_stream;
        static ::std::string termination_msg;
        static void termination_h();

        ::std::string name;
        LogStream lstream;
        Format fmt;
        ::std::map<int, ::std::vector<Handler>> handlers;
        ::std::vector<fs::path> open_fpaths;

        const ::std::vector<Handler>& get_handlers(const int&);

        static Format def_fmt;

      public:
        Logger() = delete;
        explicit Logger(::std::string, Format = def_fmt);
        explicit Logger(::std::string, buffer_t, Format = def_fmt);
        explicit Logger(::std::string, fs::path, Format = def_fmt);
        explicit Logger(::std::string, fs::recursive_directory_iterator, Format = def_fmt);
        explicit Logger(::std::string, ilist<buffer_t>, Format = def_fmt);
        explicit Logger(::std::string, ilist<fs::path>, Format = def_fmt);

        Logger(const Logger&) = delete;
        Logger(Logger&&) = delete;
        Logger& operator=(const Logger&) = delete;
        Logger& operator=(Logger&&) = delete;

        ~Logger();

        static void log_all(::std::string, const int&, FormatInfo);
        static void add_ext(const ::std::string&);
        static void set_termination_stream(buffer_t);
        static void set_termination_msg(const ::std::string&);

        void rename(::std::string);
        void register_buffer(::std::streambuf*);
        void add_path(fs::path);
        void add_handler(Handler);
        void set_format(Format = def_fmt);
        void log(::std::string, const int&, FormatInfo);
    };
}
#endif