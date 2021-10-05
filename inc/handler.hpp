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
        LogStream lstream;
        Filter filter;
        uchar min;
        uchar max;

      public:
        explicit Handler(uchar);

        const uchar get_min() const { return min; }
        const uchar& get_max() const { return max; }

        // returns `*this` so that users can do things like
        // `lgr.add_handler(hdlr.set_filter(std::cout.rdbuf*()));`
        // which essentially allows for keword arguments
        Handler& set_max(uchar);
        Handler& set_filter(const Filter&);
        Handler& add_buffer(buffer_t);
        Handler& add_file(const fs::path&);
        Handler& add_buffers(ilist<buffer_t>);
        Handler& add_files(ilist<fs::path>);

        bool handle(Record&) const;
    };
}

#endif