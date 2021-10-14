#include "filter.hpp"


namespace xlog
{
    Filter& get_filter()
    {
        return stdfilt;
    }

    Filter& get_filter(const std::string& name)
    {
        if (name == "" || name == "std")
            return stdfilt;
        auto iter = Filter::filters.find(name);
        if (iter == Filter::filters.end())
            Filter(name);
        return iter->second;
    }

    const Filter& find_filter()
    {
        return stdfilt;
    }

    const Filter& find_filter(const std::string& name)
    {
        if (name == "" || name == "std")
            return stdfilt;
        auto iter = Filter::filters.find(name);
        if (iter == Filter::filters.end())
            ;// throw...
        return iter->second;
    }

    Filter::Filter(const std::string name)
        : name(name), usable(true)
    {
        if (filters.count(name) != 0)
            ;// throw
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
