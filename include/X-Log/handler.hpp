#ifndef X_LOG_HANDLER_HPP
#define X_LOG_HANDLER_HPP

#include <string>

#include "X-Log/severity.hpp"
#include "X-Log/message.hpp"
#include "X-Log/format.hpp"


namespace xlog
{
    typedef void (*PreFilter)(Message&);
    typedef bool (*Filter)(const Message&);
    typedef void (*PostFilter)(Message&);

    class Handler
    {
        friend class Logger;
        PreFilter pre;
        Filter filter;
        PostFilter post;
        Severity min;
        Severity max;

        static bool def_filter(const Message&) { return true; }

        public:
        Handler& operator=(const Handler&) = default;
        explicit Handler(Severity, Severity = FATAL, PreFilter = nullptr, Filter = def_filter, PostFilter = nullptr);

        void set_prefilter(PreFilter);
        void set_filter(Filter);
        void set_postfilter(PostFilter);

        void rm_prefilter() { pre = nullptr; }
        void rm_filter() { filter = def_filter; }
        void rm_postfilter() { post = nullptr; }

        bool operator()(Message&, FormatInfo) const;
    };
}

#endif