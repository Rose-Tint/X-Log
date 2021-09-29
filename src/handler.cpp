#include "handler.hpp"


namespace xlog
{
    Handler::Handler(unsigned int level, PreFilter pref, Filter filt, PostFilter postf)
        : lvl(level), pre(pref), filter(filt), post(postf) { }

    bool Handler::operator()(FormatInfo& info) const
    {
        pre(info);
        if (filter(info)) return false;
        post(info);
        return true;
    }
}
