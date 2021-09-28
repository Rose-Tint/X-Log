#include "handler.hpp"


namespace xlog
{
    Handler::Handler(unsigned int _min, unsigned int _max, PreFilter pref, Filter filt, PostFilter postf)
        : min(_min), max(_max), pre(pref), filter(filt), post(postf)
    {
        if (min > max)
        {
            auto tmp = min;
            min = max;
            max = tmp;
        }
    }

    bool Handler::operator()(FormatInfo& info) const
    {
        pre(info);
        if (filter(info)) return false;
        post(info);
        return true;
    }
}
