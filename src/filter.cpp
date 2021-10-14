#include "filter.hpp"


namespace xlog
{
    Filter& get_filter() { return stdfilt; }
    Filter& get_filter(const string_t& name)
    {
        if (name == "" || name == "std")
            return stdfilt;
        if (!Filter::filters.count(name))
            Filter(name);
        return Filter::filters.at(name);
    }

    Filter::Filter(const string_t name)
        : name(name)
    {
        filters.insert({ name, this });
    }

    bool Filter::operator()(Record& rcd) const
    {
        bool pass_filter;
        if (pre != nullptr)
            pre(rcd);
        pass_filter = main_(rcd)
        if (pass_filter)
            return false;
        if (post != nullptr)
            post(rcd);
        return pass_filter;
    }
}
