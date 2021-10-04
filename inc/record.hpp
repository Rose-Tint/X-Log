#ifndef X_LOG_RECORD_HPP
#define X_LOG_RECORD_HPP

#include "fwd_declares.hpp"


namespace xlog
{
    class Record final
    {
        friend class Logger;
        friend class Format;
        friend class Handler;

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
        Record(const std::string& f, const uint& ln, const str_umap map)
            : file(f), line(ln), args(map) { }
    };
}

#endif