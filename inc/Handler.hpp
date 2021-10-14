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
        friend const Handler& find_handler(const std::string&);

        static lookup_map<Handler> handlers;

        std::string name;
        std::string format_name = "std";
        std::string filter_name = "std";
        LogStream lstream = { };
        uchar min = 0;
        uchar max = -1;
        const Filter& filter() { return get_filter(filter_name); }

      public:
        Handler() = delete;
        Handler(const std::string&);

        Handler& set_min(uchar); // done
        Handler& set_max(uchar); // done
        Handler& set_format(const std::string&); // done
        Handler& set_filter(const std::string&); // done
        Handler& add_buffer(buffer_t); // done
        Handler& add_file(const fs::path&); // done
        Handler& add_buffers(ilist<buffer_t>); // done
        Handler& add_files(ilist<fs::path>); // done
        bool handle(Record&) const; // dpme
        const uchar& get_min() const { return min; }
        const uchar& get_max() const { return max; }
        const std::string& get_name() const { return name; }
    };
}

#endif