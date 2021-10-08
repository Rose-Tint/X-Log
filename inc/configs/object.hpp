#ifndef X_LOG_CONFIGS_OBJECT_HPP
#define X_LOG_CONFIGS_OBJECT_HPP

#include "fwd_declares.hpp"


namespace config
{
    template<class ConfigType> void config(const ConfigType&);

    class Object
    {
        // there is no Filter config support for the
        // same reason that there is no buffer support
        // for Handlers; the arguments cannot be
        // dynamically loaded (name lookup)

        template<class> friend void config<Object>(const Object&);

        static inline bool already_configured = false;

        struct _type
        {
            std::string name;
        };

        struct _logger : _type
        {
            std::vector<std::string> handlers = { };
            operator Logger();
        };

        struct _handler : _type
        {
            std::string format = "std";
            uchar min = 0;
            uchar max = -1;
            std::vector<fs::path> files = { };
            operator Handler();
        };

        struct _format : _type
        {
            std::string fmt = Format::def_fmt;
            std::string time = Format::def_dft.time;
            std::string date = Format::def_dft.date;
            std::string datetime = Format::def_dft.date_time;
            operator Format();
        };

        std::vector<_logger> loggers;
        std::vector<_handler> handlers;
        std::vector<_format> formats;

      public:
        Object(str_umap<std::vector<_type*>>, bool = true);
    };
}

#endif