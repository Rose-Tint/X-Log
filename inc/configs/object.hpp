#ifndef X_LOG_CONFIGS_OBJECT_HPP
#define X_LOG_CONFIGS_OBJECT_HPP

#include "fwd_declares.hpp"


namespace config
{
    class Object
    {
        // there is no Filter config support for the
        // same reason that there is no buffer support
        // for Handlers; the arguments cannot be
        // dynamically loaded (name lookup)

        template<class>
        friend void config<Object>(const Object&);
        struct _type
        {
            std::string name;
        };

        struct _logger : _type
        {
            std::vector<std::string> handlers = { };
            operator Logger&();
        };

        struct _handler : _type
        {
            std::string format = "std";
            uchar min = 0;
            uchar max = -1;
            std::vector<std::string> filters = { };
            std::vector<fs::path> files = { };
            operator Handler&();
        };

        struct _format : _type
        {
            std::string fmt;
            std::string time;
            std::string date;
            std::string datetime;
            operator Format&();
        };

        std::vector<_logger> loggers;
        std::vector<_handler> handlers;
        std::vector<_format> formats;

      public:
        Object(str_umap<std::vector<_type*>>, bool = true);
    };
}

#endif