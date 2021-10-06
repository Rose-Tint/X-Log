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
        friend Handler& get_handler(const std::string&);
        static lookup_map<Handler> handlers;

        std::string name;
        LogStream lstream;
        Filter filter;
        uchar min;
        uchar max;

      public:
        explicit Handler(const std::string&, uchar = 0);

        const uchar get_min() const { return min; }
        const uchar& get_max() const { return max; }

        // returns `*this` so that users can do things like
        // `Handler hdler = Handler(0).add_buffer(std::cout.rdbuf());`
        Handler& set_max(uchar);
        Handler& set_filter(const Filter&);
        Handler& add_buffer(buffer_t);
        Handler& add_file(const fs::path&);
        Handler& add_buffers(ilist<buffer_t>);
        Handler& add_files(ilist<fs::path>);

        void rename(const std::string& new_name) { name = new_name; }
        bool handle(Record&) const;
    };
}

#endif