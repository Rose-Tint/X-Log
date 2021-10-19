#ifndef X_LOG_HANDLERS_FILEHANDLER_HPP
#define X_LOG_HANDLERS_FILEHANDLER_HPP

#include "fwd_declares.hpp"
#include "handlers/HandlerBase.hpp"


namespace xlog
{
    class FileHandler : public HandlerBase
    {
      public:
        using HandlerBase::HandlerBase;

        void add_outstreams(const fs::path&);
        template<class It, utils::EnableIterFor<fs::path, It>>
        void add_outstreams(It, It);
    };
}

#endif