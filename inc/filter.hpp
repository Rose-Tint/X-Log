#ifndef X_LOG_FILTER_HPP
#define X_LOG_FILTER_HPP


namespace xlog
{
    typedef void (*pre_filter_f)(Record&);
    typedef bool (*filter_f)(const Record&);
    typedef void (*post_filter_f)(Record&);

    class Filter
    {
        static bool def_filter(const Record&) { return true; }
        pre_filter_f pre;
        filter_f main_;
        post_filter_f post;

      public:
        Filter();
        explicit Filter(filter_f, pre_filter_f = nullptr, post_filter_f = nullptr);

        void set_pre(pre_filter_f pref) { pre = pref; }
        void set(filter_f filt) { main_ = filt; }
        void set_post(post_filter_f postf) { post = postf; }

        void rm_pre() { pre = nullptr; }
        void reset_main() { main_ = [](const Record&){ return true; }; }
        void rm_post() { post = nullptr; }
        void reset() { rm_pre(); reset_main(); rm_post(); }

        bool operator()(Record&) const;
    };
}

#endif