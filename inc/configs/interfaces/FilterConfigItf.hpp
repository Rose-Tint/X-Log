#ifndef X_LOG_CONFIGS_INTERFACES_FILTERCONFIGITF_HPP
#define X_LOG_CONFIGS_INTERFACES_FILTERCONFIGITF_HPP

#include "fwd_declares.hpp"
#include "configs/interfaces/ConfigItfBase.hpp"


namespace xlog::cnfg
{
    class ConfigItf : public ConfigItfBase
    {
        pre_filter_f prefilter = nullptr;
        filter_f filter = Filter::def_filter;
        post_filter_f postfilter = nullptr;

      public:
        FilterConfigItf() = default;

        pre_filter_f PreFilter() const;
        filter_f Filter() const;
        post_filter_f PostFilter() const;

        FilterConfigItf& PreFilter(pre_filter_f);
        FilterConfigItf& Filter(filter_f);
        FilterConfigItf& PostFilter(post_filter_f);
    };
}

#endif