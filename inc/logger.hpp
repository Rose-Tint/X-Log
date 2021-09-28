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

        typedef ::std::unique_lock<::std::mutex> ulock_t;

        struct LogStream
        {
            ::std::vector<buffer_t> buffers;
            void write(const ::std::string&);
            ~LogStream();
        };

        // for multithreading
        static ::std::mutex log_mtx;

        static inline ::std::unordered_map<::std::string&, Logger*> loggers = { };
        static inline LogStream termination_stream = LogStream(std::cout.rdbuf());
        static inline ::std::string termination_msg = "Program Terminated\n";
        static inline Format def_fmt = Format("${date} | ${file} - line ${line}: ${msg}");
        static ::std::unordered_set<::std::string> log_exts;
        static void termination_h();

        ::std::string name;
        LogStream lstream;
        Format fmt;
        ::std::unordered_map<int, ::std::vector<Handler>> handlers;
        ::std::vector<fs::path> open_fpaths;

        const ::std::vector<Handler>& get_handlers(const int&);
        void exc_log(const ::std::string&, const int&, FormatInfo&);

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
        static void add_ext(::std::string);
        static void set_termination_stream(buffer_t);
        static void set_termination_msg(const ::std::string&);

        void rename(::std::string rn) { name = std::move(rn); }
        void register_buffer(::std::streambuf*);
        void add_path(fs::path);
        void add_handler(Handler);
        void set_format(Format format = def_fmt) { fmt = format; }
        ::std::jthread& log(const ::std::string&, const int&, FormatInfo);
    };
}
#endif