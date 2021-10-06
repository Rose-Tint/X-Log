#ifndef X_LOG_LOGGER_HPP
#define X_LOG_LOGGER_HPP

#include "fwd_declares.hpp"
#include "format.hpp"
#include "record.hpp"
#include "handler.hpp"


namespace xlog
{
    class Logger final
    {
        friend Logger& get_logger(const std::string&);

        static lookup_map<Logger*> loggers;
        static str_set_t log_exts;
        static inline Format def_fmt = Format("${date} | ${file} - line ${line}:\n -- ${msg}");
        static inline LogStream termination_stream = LogStream({std::cout.rdbuf()});
        static inline std::string termination_msg = "Program Terminated";
        static void handle_termination();

        std::string name;
        std::vector<std::string> handler_names;

        std::vector<Handler*> handlers(const uchar&);

      public:
        Logger() = delete;
        explicit Logger(const std::string&);

        Logger(const Logger&) = delete;
        Logger(Logger&&) = delete;
        Logger& operator=(const Logger&) = delete;
        Logger& operator=(Logger&&) = delete;

        static void log_all(const std::string&, const uchar&, Record);
        static void add_ext(const std::string&);
        static void add_exts(ilist<std::string>);
        static void set_termination_stream(buffer_t);
        static void set_termination_msg(const std::string&);

        void log(const std::string&, const uchar&, Record);
        const std::string& get_name() const { return name; }

        // returns `*this` so that users can do things like
        // `Logger lgr = Logger().add_handler(hdlr);`
        Logger& add_handler(const std::string&);
        Logger& add_handler(const Handler&);
        Logger& add_handlers(ilist<Handler>);
        Logger& add_handlers(ilist<std::string>);
    };

    Logger& get_logger(const std::string&);
}
#endif