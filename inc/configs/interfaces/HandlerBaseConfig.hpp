#ifndef X_LOG_CONFIGS_INTERFACES_HANDLERBASECONFIGITF_HPP
#define X_LOG_CONFIGS_INTERFACES_HANDLERBASECONFIGITF_HPP

#include "fwd_declares.hpp"
#include "configs/interfaces/ConfigItfBase.hpp"


namespace xlog::cnfg
{
    class ConfigItf : public ConfigItfBase
    {
        u8String format;
        u8String filter;
        uchar min;
        uchar max;
        std::vector<fs::path> files;
        std::vector<buffer_t> buffers;

      public:
        HandlerConfigItf() = default;

        const u8String& Format() const;
        const u8String& Filter() const;
        const uchar& Min() const;
        const uchar& Max() const;
        const std::vector<buffer_t> Buffers() const;

        HandlerConfigItf& Format(const u8String&);
        HandlerConfigItf& Filter(const u8String&);
        HandlerConfigItf& Min(const uchar&);
        HandlerConfigItf& Max(const uchar&);
        HandlerConfigItf& Buffers(buffer_t);
        HandlerConfigItf& Buffers(ilist<buffer_t>);
    };
}

#endif