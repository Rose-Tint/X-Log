#ifndef X_LOG_CONFIGS_TYPECONFIGITF_HPP
#define X_LOG_CONFIGS_TYPECONFIGITF_HPP

#include "fwd_declares.hpp"


namespace xlog::cnfg
{
    class TypeConfigItfBase
    {
        string_t name;

      public:
        TypeConfigItfBase();

        const string_t& Name() const { return name; }

        TypeConfigItfBase& Name(const string_t& new_name)
            { name = new_name; return *this; }
    };

    class LoggerConfigItf : TypeConfigItfBase
    {
        std::vector<string_t> handlers = { };

      public:
        LoggerConfigItf();
        const std::vector<string_t>& Handlers() const { return handlers; }
        LoggerConfigItf& Handlers(ilist<string_t> hnames)
            { handlers.insert(handlers.end(), hnames); return *this; }
    };

    class HandlerConfigItf : TypeConfigItfBase
    {
        string_t format = "std";
        uchar min = 0;
        uchar max = -1;
        std::vector<fs::path> files = { };
        std::vector<buffer_t> files = { };

      public:
        HandlerConfigItf();

        const string_t& Format() const { return format; }
        const uchar& Min() const { return min; }
        const uchar& Min() const { return min; }
        const std::vector<fs::path> Files() const { return files; }
        const std::vector<buffer_t> Buffers() const { return buffers; }

        HandlerConfigItf& Format(const string_t& fmt)
            { format = fmt; return *this; }
        HandlerConfigItf& Max(const uchar& mn)
            { min = mn; return *this; }
        HandlerConfigItf& Max(const uchar& mx)
            { max = mx; return *this; }
        HandlerConfigItf& Files(ilist<fs::path> _files)
            { files.insert(files.end(), _files); return *this; }
        HandlerConfigItf& Buffers(ilist<buffer_t> bufs)
            { buffers.insert(buffers.end(), bufs); return *this; }
    };

    class FormatConfigItf : TypeConfigItfBase
    {
        string_t format = Format::def_fmt;
        string_t time = Format::def_dft.time;
        string_t date = Format::def_dft.date;
        string_t datetime = Format::def_dft.datetime;

      public:
        FormatConfigItf();

        const string_t& Format() const { return format; }
        const string_t& Time() const { return time; }
        const string_t& Date() const { return date; }
        const string_t& DateTime() const { return datetime; }

        FormatConfigItf& Format(const string_t& fmt)
            { format = fmt; return *this }
        FormatConfigItf& Time(const string_t& tm)
            { time = tm; return *this }
        FormatConfigItf& Date(const string_t& dt)
            { date = dt; return *this }
        FormatConfigItf& DateTime(const string_t& dt)
            { datetime = dt; return *this }
    };

    class FilterConfigItf : TypeConfigItfBase
    {
        pre_filter_f prefilter = nullptr;
        filter_f filter = Filter::def_filter;
        post_filter_f postfilter = nullptr;

      public:
        FilterConfigItf();

        pre_filter_f PreFilter() const { return prefilter; }
        filter_f Filter() const { return filter; }
        post_filter_f PostFilter() const { return postfilter; }

        FilterConfigItf& PreFilter(pre_filter_f pref)
            { prefilter = pref; return *this; }
        FilterConfigItf& Filter(filter_f filt)
            { filter = filt; return *this; }
        FilterConfigItf PostFilter(post_filter_f postf)
            { postfilter = postf; return *this; }
    };

    class ConfigTypeBase
    {
      protected:
        std::vector<LoggerConfigItf> loggers;
        std::vector<HandlerConfigItf> handlers;
        std::vector<FormatConfigItf> formats;
        std::vector<FilterConfigItf> filters;
    };
}

#endif