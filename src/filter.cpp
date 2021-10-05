#include "format.hpp"


namespace xlog
{
    Filter::Filter()
    {
        rm_pre();
        reset_main();
        rm_post();
    }

    Filter::Filter(filter_f filt, pre_filter_f pref = nullptr, post_filter_f postf = nullptr)
    {
        if (filt != nullptr)
        {
            main_ = filt;
        }
        else
        {
            reset_main();
        }
        set_pre(pref);
        set_post(postf);
    }

    bool operator()(Record& rcd) const
    {
        if (pre != nullptr) pre(rcd);
        if (!main_(rcd)) return false;
        if (post != nullptr) post(rcd);
        return true;
    }
}
