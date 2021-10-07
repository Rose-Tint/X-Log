#ifndef X_LOG_RECORD_HPP
#define X_LOG_RECORD_HPP

#include "fwd_declares.hpp"


namespace xlog
{
    class Record final
    {
        friend class Logger;

        // set to default because Logger will set them after construction
        std::string msg = "";
        std::string lgr = "";
        uchar lvl = 0;
        // sets msg, lgr, and lvl by Logger
        void init_rest(const std::string&, const std::string&, const uchar&);

        // set by ctr
        std::string func;
        std::string file;
        uint line;
        arg_map_t args;

      public:
        Record(const std::string&, const uint&, str_pair_t = { });
        Record(const std::string&, const uint&, const std::string, str_pair_t = { });

        Record(Record&&);

        // observers
        const std::string& get_msg() const { return msg; }
        const std::string& get_lgr() const { return lgr; }
        const uchar& get_lvl() const { return lvl; }
        const std::string& get_file() const { return file; }
        const uint& get_line() const { return line; }
        const arg_map_t& get_args() const { return args; }

        arg_map_t get_dict() const;

#ifdef CPP20
        Record(const std::source_location&, const arg_map_t&);
#ifndef MAKE_RCD
#define MAKE_RCD(...) xlog::Record(std::source_location::current())
#endif
#endif
    };
}

#ifndef MAKE_RCD
#define MAKE_RCD(...) xlog::Record( __FILE__, __LINE__, { __VA_ARGS__ } )
#endif

#endif