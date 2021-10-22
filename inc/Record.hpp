#ifndef X_LOG_RECORD_HPP
#define X_LOG_RECORD_HPP

#include "fwd_declares.hpp"


namespace xlog
{
    class Record final
    {
        friend class Logger;

        // set to default because Logger will set them post construction
        u8String msg = "";
        u8String lgr = "";
        uchar lvl = 0;

        // set by ctr
        u8String func;
        uint line;
        u8String file;
        arg_map_t args;

      public:
        Record(const u8String&, uint, const u8String&, ilist<str_pair_t> = { });

        // observers
        const u8String& get_msg() const { return msg; }
        const u8String& get_lgr() const { return lgr; }
        const uchar& get_lvl() const { return lvl; }
        const u8String& get_file() const { return file; }
        const uint& get_line() const { return line; }
        const arg_map_t& get_args() const { return args; }

        arg_map_t get_dict() const;
        void insert_args(const u8String&, const u8String&);
        void insert_args(const str_pair_t&);
        void insert_args(ilist<str_pair_t>);
        template<class It, utils::EnableIterFor<str_pair_t, It> = true>
        void insert_args(It, It);

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