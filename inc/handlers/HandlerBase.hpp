#ifndef X_LOG_HANDLERS_HANDLERBASE_HPP
#define X_LOG_HANDLERS_HANDLERBASE_HPP

#include "fwd_declares.hpp"
#include "filter.hpp"
#include "logstream.hpp"
#include "record.hpp"


namespace xlog
{
    class HandlerBase
    {
        friend HandlerBase& get_handler(const string_t&);

        static lookup_map<HandlerBase> handlers;

      protected:
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
        HandlerBase() = delete;
        HandlerBase(const string_t&);

        virtual ~HandlerBase() = default;

        void set_min(uchar);
        void set_max(uchar);
        void set_format(const string_t&);
        void set_filter(const string_t&);
        void add_outstreams(buffer_t);
        void add_outstreams(const buffer_t*, const buffer_t*);
        template<class It, utils::EnableIterFor<buffer_t, It> = true>
        void add_outstreams(It, It);

        virtual bool handle(Record&) const = 0;
        const uchar& get_min() const { return min; }
        const uchar& get_max() const { return max; }
        const string_t& get_name() const { return name; }
    };
}

#endif