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
        std::string file;
        uint line;
        str_umap args;

      public:
        Record(const std::string& f, const uint& ln, const str_umap& map)
            : file(f), line(ln), args(map) { }

        Record(Record&&);

        // observers
        const std::string& get_msg() const { return msg; }
        const std::string& get_lgr() const { return lgr; }
        const uchar& get_lvl() const { return lvl; }
        const std::string& get_file() const { return file; }
        const uint& get_line() const { return line; }
        const str_umap& get_args() const { return args; }

        str_umap get_dict() const;
    };
}

#ifndef MAKE_RCD
#define MAKE_RCD(args...) xlog::Record( __FILE__, __LINE__, { args } )
#endif

#endif