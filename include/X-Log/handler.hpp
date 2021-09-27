#ifndef X_LOG_HANDLER_HPP
#define X_LOG_HANDLER_HPP

#include <string>

#include "X-Log/format.hpp"


namespace xlog
{
    typedef void (*PreFilter)(::std::string&);
    typedef bool (*Filter)(const ::std::string&);
    typedef void (*PostFilter)(::std::string&);

    class Handler
    {
        friend class Logger;
        PreFilter pre;
        Filter filter;
        PostFilter post;
        unsigned int min;
        unsigned int max;

        static bool def_filter(const ::std::string&) { return true; }

        public:
        Handler& operator=(const Handler&) = default;
        explicit Handler(unsigned int, unsigned int = 100, PreFilter = nullptr, Filter = def_filter, PostFilter = nullptr);

        void set_prefilter(PreFilter);
        void set_filter(Filter);
        void set_postfilter(PostFilter);

        void rm_prefilter() { pre = nullptr; }
        void rm_filter() { filter = def_filter; }
        void rm_postfilter() { post = nullptr; }

        bool operator()(FormatInfo) const;
    };
}

#endif