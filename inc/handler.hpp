#ifndef X_LOG_HANDLER_HPP
#define X_LOG_HANDLER_HPP

#include "fwd_declares.hpp"
#include "record.hpp"


namespace xlog
{
    typedef void (*PreFilter)(Record&);
    typedef bool (*Filter)(const Record&);
    typedef void (*PostFilter)(Record&);

    class Handler final
    {
        class LogStream
        {
            static std::mutex io_mtx;
            void aquire() { io_mtx.lock(); }
            void release() { io_mtx.unlock(); }
            void write(const std::string&);
            std::vector<buffer_t> buffers;
          public:
            void add_buffer(buffer_t);
            void send(const std::string&);
            ~LogStream();
        };

        LogStream lstream;
        PreFilter pre;
        Filter filter;
        PostFilter post;
        uint level;

        static bool def_filter(const Record&) { return true; }

        void init(uint, PreFilter, Filter, PostFilter);

      public:
        explicit Handler(uint, PreFilter = nullptr, Filter = def_filter, PostFilter = nullptr);
        explicit Handler(uint, ilist<buffer_t>, PreFilter = nullptr, Filter = def_filter, PostFilter = nullptr);
        explicit Handler(uint, ilist<fs::path>, PreFilter = nullptr, Filter = def_filter, PostFilter = nullptr);

        void set_prefilter(PreFilter pref) { pre = pref; }
        void set_filter(Filter filt) { filter = filt; }
        void set_postfilter(PostFilter postf) { post = postf; }

        void rm_prefilter() { pre = nullptr; }
        void rm_filter() { filter = def_filter; }
        void rm_postfilter() { post = nullptr; }

        const uint& get_level() const { return level; }

        Handler& add_buffer(buffer_t);
        Handler& add_file(fs::path)

        bool handle(Record&) const;
    };
}

#endif