#ifndef X_LOG_RECORD_HPP
#define X_LOG_RECORD_HPP

#include "fwd_declares.hpp"


namespace xlog
{
    class Record final
    {
        friend class Logger;

        // set to default because Logger will set them post construction
        string_t msg = "";
        string_t lgr = "";
        uchar lvl = 0;

        // set by ctr
        string_t func;
        uint line;
        string_t file;
        arg_map_t args;

      public:
        Record(const string_t&, uint, const string_t&, ilist<str_pair_t> = { });

        // observers
        const string_t& get_msg() const { return msg; }
        const string_t& get_lgr() const { return lgr; }
        const uchar& get_lvl() const { return lvl; }
        const string_t& get_file() const { return file; }
        const uint& get_line() const { return line; }
        const arg_map_t& get_args() const { return args; }

        arg_map_t get_dict() const;
        void insert_args(const string_t&, const string_t&);
        void insert_args(const str_pair_t&);
        void insert_args(ilist<str_pair_t>);
        template<class It>
        void insert_args(It, It, iter_tag<It>* = nullptr);

#if CPP_STD >= 20
        Record(const std::source_location&, ilist<str_pair_t>);
#endif
    };
}

#ifndef MAKE_RCD
#if CPP_STD >= 20
#define MAKE_RCD(...) xlog::Record(std::source_location::current())
#endif
#define MAKE_RCD(...) xlog::Record( __FILE__, __LINE__, { __VA_ARGS__ } )
#endif

#endif