#include "filter.hpp"


namespace xlog
{
    void make_filter(const std::string name)
    {
        if (Filter::filters.count(name) != 0)
            ;// throw...
        auto& filt = Filter(name);
    }

    Filter& get_filter(const std::string& name)
    {
        if (name == "")
            return find_filter("std");
        if (Filter::filters.count(name) == 0)
            make_filter(name);
        return find_filter(name);
    }

    Filter& find_filter(const std::string& name)
    {
        if (Filter::filters.count(name) == 0)
            ;//throw...
        return Filter::filters[name];
    }

    Filter::Filter(const std::string& _name)
        : name(_name)
    {
        filters.insert({ name, this });
    }

    bool Filter::operator()(Record& rcd) const
    {
        if (pre != nullptr) pre(rcd);
        if (!main_(rcd)) return false;
        if (post != nullptr) post(rcd);
        return true;
    }
}
