#ifndef X_LOG_HANDLER_HPP
#define X_LOG_HANDLER_HPP

#include <string>

#include "format.hpp"


namespace xlog
{
    typedef void (*PreFilter)(FormatInfo&);
    typedef bool (*Filter)(const FormatInfo&);
    typedef void (*PostFilter)(FormatInfo&);

    class Handler
    {
        PreFilter pre;
        Filter filter;
        PostFilter post;
        unsigned int lvl;

        static bool def_filter(const FormatInfo&) { return true; }

        public:
        explicit Handler(unsigned int, PreFilter = nullptr, Filter = def_filter, PostFilter = nullptr);

        void set_prefilter(PreFilter pref) { pre = pref; }
        void set_filter(Filter filt) { filter = filt; }
        void set_postfilter(PostFilter postf) { post = postf; }

        void rm_prefilter() { pre = nullptr; }
        void rm_filter() { filter = def_filter; }
        void rm_postfilter() { post = nullptr; }

        const unsigned int& get_lvl() const { return lvl; }

        bool operator()(FormatInfo&) const;
    };
}

#endif