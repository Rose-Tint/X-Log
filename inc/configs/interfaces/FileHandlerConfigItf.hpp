#ifndef X_LOG_CONFIGS_INTERFACES_FILECONFIGITF_HPP
#define X_LOG_CONFIGS_INTERFACES_FILECONFIGITF_HPP

#include "fwd_declares.hpp"
#include "configs/interfaces/ConfigItfBase.hpp"
#include "configs/interfaces/HandlerBaseConfigItf.hpp"


namespace xlog::cnfg
{
    class FileConfigItf : public ConfigItfBase, public HandlerBaseConfigItf
    {
      public:
        HandlerBaseConfigItf& Buffers(ilist<buffer_t>) = delete;

        const std::vector<fs::path>& Files() const;

        FileConfigItf& Files(ilist<fs::path>);
        FileConfigItf& Buffers(ilist<filebuf_t>);
    };
}

#endif