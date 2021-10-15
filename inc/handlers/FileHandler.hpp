#ifndef X_LOG_HANDLERS_FILEHANDLER_HPP
#define X_LOG_HANDLERS_FILEHANDLER_HPP

#include "fwd_declares.hpp"
#include "handlers/HandlerBase.hpp"


namespace xlog
{
    class FileHandler : public HandlerBase
    {
      public:
        explicit FileHandler(const string_t&);
        FileHandler(const string_t&, const fs::path&);
        FileHandler(const string_t&, const fs::path*, const fs::path*);
        FileHandler(const string_t&, ilist<fs::path>);

        void add_outstreams(const fs::path&);
        void add_outstreams(ilist<fs::path>);
        void add_outstreams(const fs::path*, const fs::path*);
        template<class It>
        void add_outstreams(It, It, iter_tag<It>* = nullptr);
    };
}

#endif