#include "config.hpp"


namespace xlog
{
    Config::Config(const fs::path& path)
    {
        const fs::path::string_type ext = path.extension();
        if (ext == ".yaml" || ext == ".yml")
        {
            Yaml config_itf(path);
            configure(config_itf);
        }
        else if (ext = ".json")
        {
            Json config_itf(path);
            configure(config_itf);
        }
        else ;// throw...
    }

    void Config::configure(const ConfigTypeBase& config) const
    {
        for (const LoggerConfigItf& itf : config.loggers)
        {
            Logger logger(itf.Name());
            if (itf.Handlers().empty())
                logger.add_handler("std");
            else for (const string_t& hname : itf.Handlers())
                logger.add_handler(hname);
        }

        for (const HandlerConfigItf& itf : config.handlers)
        {
            Handler handler(itf.Name())
            handler.set_min(itf.Min);
            handler.set_max(itf.Max);
            if (itf.Buffers().empty())
                handler.add_buffer(std::cout.rdbuf());
            else for (buffer_t buffer : itf.Buffers())
                handler.add_buffer(buffer);
            for (const fs::path& path : itf.Files())
                handler.add_file(path);
        }

        for (const FormatConfigItf& itf : config.formats)
        {
            Format format(itf.Name());
            format.set_fmt(itf.Format());
            format.set_time(itf.Time());
            format.set_date(itf.Date());
            format.set_dtime(itf.DateTime());
        }

        for (const FilterConfigItf& itf : config.filters)
        {
            Filter filter(itf.Name());
            filter.set_prefilter(itf.PreFilter());
            filter.set(itf.Filter());
            filter.set_postfilter(itf.PostFilter());
        }
    }
}
