#include "format.hpp"


namespace xlog
{
    Filter& get_filter(const std::string& name)
    {
        if (name == "")
        {
            return *(Filter::filters["std"]);
        }
        if (Filter::filters.count(name) == 0)
        {
            Filter new_filt = Filter(name);
        }
        return *(Filter::filters[name]);
    }

    Filter::Filter(const std::string& _name, filter_f filt, pre_filter_f pref, post_filter_f postf)
        : name(_name), pre(pref), post(postf)
    {
        filters.insert({ name, this });
        if (filt != nullptr)
        {
            main_ = filt;
        }
        else
        {
            main_ = &def_filter;
        }
    }

    bool operator()(Record& rcd) const
    {
        if (pre != nullptr) pre(rcd);
        if (!main_(rcd)) return false;
        if (post != nullptr) post(rcd);
        return true;
    }
}
