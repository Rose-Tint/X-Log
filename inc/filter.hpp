#ifndef X_LOG_FILTER_HPP
#define X_LOG_FILTER_HPP

#include "fwd_declares.hpp"
#include "format.hpp"
#include "record.hpp"

namespace xlog
{
    typedef void (*pre_filter_f)(Record&);
    typedef bool (*filter_f)(const Record&);
    typedef void (*post_filter_f)(Record&);

    class Filter final
    {
        friend void make_filter(const std::string&);
        friend Filter& get_filter(const std::string&);
        friend Filter& find_filter(const std::string&);

        static lookup_map<Filter> filters;

        std::string name;
        pre_filter_f pre = nullptr;
        filter_f main_ = def_filter;
        post_filter_f post = nullptr;

        Filter() = default;
        explicit Filter(const std::string&);
        Filter(Filter&&) = delete;
        Filter& operator=(Filter&&) = default;
        Filter(const Filter&) = delete;
        Filter& operator=(const Filter&) = default;

      public:
        static bool def_filter(const Record&) { return true; }

        void set_pre(pre_filter_f pref) { pre = pref; }
        void set(filter_f filt) { main_ = filt; }
        void set_post(post_filter_f postf) { post = postf; }

        void rm_pre() { pre = nullptr; }
        void reset_main() { main_ = [](const Record&){ return true; }; }
        void rm_post() { post = nullptr; }
        void reset() { rm_pre(); reset_main(); rm_post(); }

        bool operator()(Record&) const;
        const std::string& get_name() const { return name; }
    };

    void make_filter(const std::string&);
    Filter& get_filter(const std::string&);
    Filter& find_filter(const std::string&);
}

#endif