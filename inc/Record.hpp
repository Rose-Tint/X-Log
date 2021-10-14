#ifndef X_LOG_RECORD_HPP
#define X_LOG_RECORD_HPP

#include "fwd_declares.hpp"


namespace xlog
{
    class Record final
    {
        friend class Logger;

        // set to default because Logger will set them post construction
        std::string msg = "";
        std::string lgr = "";
        uchar lvl = 0;

        // set by ctr
        std::string func;
        std::string file;
        uint line;
        arg_map_t args;

      public:
        Record(const std::string&, const uint&, const std::string, str_pair_t = { });

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
#endif
    };
}

#ifndef MAKE_RCD
#ifdef CPP20
#define MAKE_RCD(...) xlog::Record(std::source_location::current())
#endif
#define MAKE_RCD(...) xlog::Record( __FILE__, __LINE__, { __VA_ARGS__ } )
#endif

#endif