#ifndef X_LOG_HANDLER_HPP
#define X_LOG_HANDLER_HPP

#include "fwd_declares.hpp"
#include "filter.hpp"
#include "logstream.hpp"
#include "record.hpp"


namespace xlog
{
    class Handler final
    {
        friend Handler& get_handler(const string_t&);

        static lookup_map<Handler> handlers;

        string_t name;
        string_t format_name;
        string_t filter_name;
        // ptr to allow polymorphism
        uptr_t<LogStreamBase> lstream_ptr;
        uchar min;
        uchar max;

        Filter& filter() const;
        Format& format() const;

      public:
        Handler() = delete;
        Handler(const string_t&);

        Handler& set_min(uchar);
        Handler& set_max(uchar);
        Handler& set_format(const string_t&);
        Handler& set_filter(const string_t&);
        Handler& add_outputs(const fs::path&);
        Handler& add_outputs(ilist<fs::path>);
        Handler& add_outputs(buffer_t);
        Handler& add_outputs(ilist<buffer_t>);

        virtual bool handle(Record&) const;?
        const uchar& get_min() const { return min; }
        const uchar& get_max() const { return max; }
        const string_t& get_name() const { return name; }
    };
}

#endif