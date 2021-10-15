#ifndef X_LOG_CONFIGS_INTERFACES_HANDLERBASECONFIGITF_HPP
#define X_LOG_CONFIGS_INTERFACES_HANDLERBASECONFIGITF_HPP

#include "fwd_declares.hpp"
#include "configs/interfaces/ConfigItfBase.hpp"


namespace xlog::cnfg
{
    class ConfigItf : public ConfigItfBase
    {
        string_t format = "std";
        string_t filter = "std";
        uchar min = 0;
        uchar max = -1;
        std::vector<fs::path> files = { };
        std::vector<buffer_t> buffers = { };

      public:
        HandlerConfigItf() = default;

        const string_t& Format() const;
        const string_t& Filter() const;
        const uchar& Min() const;
        const uchar& Max() const;
        const std::vector<buffer_t> Buffers() const;

        HandlerConfigItf& Format(const string_t&);
        HandlerConfigItf& Filter(const string_t&);
        HandlerConfigItf& Min(const uchar&);
        HandlerConfigItf& Max(const uchar&);
        HandlerConfigItf& Buffers(buffer_t);
        HandlerConfigItf& Buffers(ilist<buffer_t>);
    };
}

#endif