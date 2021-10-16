#ifndef X_LOG_STREAMS_LOGFILE_HPP
#define X_LOG_STREAMS_LOGFILE_HPP

#include "fwd_declares.hpp"
#include "streams/LogStreamBase.hpp"


namespace xlog
{
    class LogFile : public LogStreamBase
    {
        virtual void vwrite(const string_t&) override;
        virtual void vflush() override;

      public:
        LogFile() = default;
        explicit LogFile(filebuf_t);
        explicit LogFile(ilist<filebuf_t>);
        LogFile(filebuf_t*, filebuf_t*);
        explicit LogFile(const fs::path&);
        explicit LogFile(ilist<fs::path>);
        LogFile(fs::path*, fs::path*);
        template<class It>
        LogFile(It, It, iter_tag<It>* = nullptr);

        void add_output(const fs::path&);
    };
}

#endif