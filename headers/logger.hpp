#ifndef LOGGER_HPP
#define LOGGER_HPP
#ifdef __cpp_lib_experimental_filesystem
#elif !defined( __cpp_lib_filesystem )
#include <filesystem>
#endif

#include <map>
#include <string>
#include <fstream>
#include <initializer_list>
#include <exception>

#include "./handler.hpp"
#include "./severity.hpp"
#include "./format.hpp"


namespace logging
{
#ifdef __cpp_lib_filesystem
    namespace fs = std::filesystem;
#elif !defined( __cpp_lib_experimental_filesystem )
    namespace fs = std::experimental::filesystem;
#endif

    typedef std::streambuf* buffer_t;

    template<typename T>
    using ilist = const std::initializer_list<T>&;


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
        static std::map<std::string&, Logger*> loggers;
        static LogStream termination_stream;
        static void termination_h();
        static Message termination_msg;

        std::string name;
        LogStream lstream;
        Format fmt;
        std::map<Severity, Handler> handlers;
        std::vector<fs::path> open_fpaths;

        const Handler& get_handler(const Severity&);

        static Format def_fmt;

      public:
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

        static void log_all(const Severity&, Message);
        static void add_ext(const std::string&);

        static void set_termination_stream(buffer_t);
        static void set_termination_msg(const Message&);

        void rename(std::string);
        void register_buffer(std::streambuf*);
        void add_path(fs::path);
        void add_handler(Handler);
        void set_format(Format);

        void log(const Severity&, Message);
    };

    Logger& get_logger(std::string);
}
#ifndef NO_AUTOMATIC_LOGGER
#include <iostream>
logging::Logger main_lgr = Logger("main", std::cout.rdbuf());
#endif

#endif