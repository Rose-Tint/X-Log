#ifndef X_LOG_FILTER_HPP
#define X_LOG_FILTER_HPP

#include "fwd_declares.hpp"
#include "record.hpp"

namespace xlog
{
    typedef void (*pre_filter_f)(Record&);
    typedef bool (*filter_f)(const Record&);
    typedef void (*post_filter_f)(const Record&);

    class Filter final
    {
        friend Filter& get_filter(const std::string&); // done

        static lookup_map<Filter> filters;

        std::string name;
        pre_filter_f pre = nullptr;
        filter_f main_ = def_filter;
        post_filter_f post = nullptr;

      public:
        Filter() = delete;
        Filter(const std::string&); // done

        static bool def_filter(const Record&) { return true; }

        void set_prefilter(pre_filter_f pref) { pre = pref; }
        void set(filter_f filt) { main_ = filt; }
        void set_postfilter(post_filter_f postf) { post = postf; }

        bool operator()(Record&) const;
        const std::string& get_name() const { return name; }
    };
}

#endif