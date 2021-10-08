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
        friend void make_handler(const std::string&);
        friend Handler& get_handler(const std::string&);
        friend Handler& find_handler(const std::string&);

        static lookup_map<Handler> handlers;

        std::string name;
        std::string filter_name = "std";
        LogStream lstream;
        uchar min = 0;
        uchar max = -1;
        const Filter& filter() { return xlog::get_filter(filter_name); }

        Handler() = default;
        Handler(const std::string&);
        Handler(Handler&&) = delete;
        Handler& operator=(Handler&&) = default;
        Handler(const Handler&) = delete;
        Handler& operator=(const Handler&) = default;

      public:
        const uchar get_min() const { return min; }
        const uchar& get_max() const { return max; }

        // returns `*this` so that users can do things like
        // `Handler hdler = Handler(0).add_buffer(std::cout.rdbuf());`
        Handler& set_max(uchar);
        Handler& set_filter(const std::string&);
        Handler& set_filter(const Filter&);
        Handler& add_buffer(buffer_t);
        Handler& add_file(const fs::path&);
        Handler& add_buffers(ilist<buffer_t>);
        Handler& add_files(ilist<fs::path>);

        bool handle(Record&);
        const std::string& get_name() const { return name; }
    };

    void make_handler(const std::string&);
    Handler& get_handler(const std::string&);
    Handler& find_handler(const std::string&);
}

#endif