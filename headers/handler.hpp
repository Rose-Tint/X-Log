#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <string>

#include "severity.hpp"


namespace logging
{
    typedef std::string Message;
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
        explicit Handler(Severity = TEST, Severity = FATAL, PreFilter = nullptr, Filter = def_filter, PostFilter = nullptr);

        Handler(const Handler&) = delete;
        Handler(Handler&&) = delete;
        Handler& operator=(Handler&&) = delete;

        void set_prefilter(PreFilter);
        void set_filter(Filter);
        void set_postfilter(PostFilter);

        void rm_prefilter() { pre = nullptr; }
        void rm_filter();
        void rm_postfilter() { post = nullptr; }

        const Message& operator()(Message&) const;
    };
}

#endif