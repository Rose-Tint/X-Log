#ifndef X_LOG_LOGGER_HPP
#define X_LOG_LOGGER_HPP

#include "fwd_declares.hpp"
#include "errors.hpp"
#include "format.hpp"
#include "record.hpp"
#include "handler.hpp"


namespace xlog
{
    class Logger final
    {
        friend Logger& get_logger(std::string);

        static inline std::unordered_map<std::string&, Logger*> loggers = { };
        static inline LogStream termination_stream = LogStream {{std::cout.rdbuf()}};
        static inline std::string termination_msg = "Program Terminated\n";
        static inline Format def_fmt = Format("${date} | ${file} - line ${line}:\n\t${msg}");
        static std::unordered_set<std::string> log_exts;
        static void termination_h();

        std::string name;
        LogStream lstream;
        Format fmt;
        std::unordered_map<int, std::vector<Handler>> handlers;
        std::vector<fs::path> open_fpaths;

        const std::vector<Handler>& get_handlers(const int&);
        void exc_log(Record&);

      public:
        Logger() = delete;
        explicit Logger(std::string, Format = def_fmt);

        Logger(const Logger&) = delete;
        Logger(Logger&&) = delete;
        Logger& operator=(const Logger&) = delete;
        Logger& operator=(Logger&&) = delete;

        ~Logger();

        static void log_all(std::string, const int&, Record);
        static void add_ext(std::string);
        static void set_termination_stream(buffer_t);
        static void set_termination_msg(const std::string&);

        void rename(std::string rn) { name = std::move(rn); }
        void add_handler(Handler);
        void set_format(Format format = def_fmt) { fmt = format; }
        void log(const std::string&, const int&, Record);
    };
}
#endif