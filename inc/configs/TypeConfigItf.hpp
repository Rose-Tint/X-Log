#ifndef X_LOG_CONFIGS_TYPECONFIGITF_HPP
#define X_LOG_CONFIGS_TYPECONFIGITF_HPP

#include "fwd_declares.hpp"


namespace xlog::cnfg
{
    class TypeConfigItfBase
    {
        string_t name;

      public:
        TypeConfigItfBase() = default;
        const string_t& Name() const;
        TypeConfigItfBase& Name(const string_t&);
    };

    class LoggerConfigItf : TypeConfigItfBase
    {
        std::vector<string_t> handlers = { };
        string_t filter = "std";

      public:
        LoggerConfigItf() = default;

        const std::vector<string_t>& Handlers() const;
        const string_t& Filter() const;

        LoggerConfigItf& Handlers(ilist<string_t>);
        LoggerConfigItf& Filter(const string_t&);
    };

    class HandlerConfigItf : TypeConfigItfBase
    {
        string_t format = "std";
        string_t filter = "std";
        uchar min = 0;
        uchar max = -1;
        std::vector<fs::path> files = { };
        std::vector<buffer_t> buffers = { };

      public:
        HandlerConfigItf() = default;

        const string_t& Format() const;
        const string_t& Filter() const;
        const uchar& Min() const;
        const uchar& Max() const;
        const std::vector<fs::path> Files() const;
        const std::vector<buffer_t> Buffers() const;

        HandlerConfigItf& Format(const string_t&);
        HandlerConfigItf& Filter(const string_t&);
        HandlerConfigItf& Min(const uchar&);
        HandlerConfigItf& Max(const uchar&);
        HandlerConfigItf& Files(const fs::path&);
        HandlerConfigItf& Files(ilist<fs::path>);
        HandlerConfigItf& Buffers(buffer_t);
        HandlerConfigItf& Buffers(ilist<buffer_t>);
    };

    class FormatConfigItf : TypeConfigItfBase
    {
        string_t format = Format::def_fmt;
        string_t time = Format::def_dft.time;
        string_t date = Format::def_dft.date;
        string_t datetime = Format::def_dft.datetime;

      public:
        FormatConfigItf() = default;

        const string_t& Format() const;
        const string_t& Time() const;
        const string_t& Date() const;
        const string_t& DateTime() const;

        FormatConfigItf& Format(const string_t&);
        FormatConfigItf& Time(const string_t&);
        FormatConfigItf& Date(const string_t&);
        FormatConfigItf& DateTime(const string_t&);
    };

    class FilterConfigItf : TypeConfigItfBase
    {
        pre_filter_f prefilter = nullptr;
        filter_f filter = Filter::def_filter;
        post_filter_f postfilter = nullptr;

      public:
        FilterConfigItf() = default;

        pre_filter_f PreFilter() const;
        filter_f Filter() const;
        post_filter_f PostFilter() const;

        FilterConfigItf& PreFilter(pre_filter_f);
        FilterConfigItf& Filter(filter_f);
        FilterConfigItf& PostFilter(post_filter_f);
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