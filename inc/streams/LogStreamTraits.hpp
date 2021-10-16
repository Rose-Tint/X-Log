#ifndef X_LOG_STREAMS_LOGSTREAMTRAITS_HPP
#define X_LOG_STREAMS_LOGSTREAMTRAITS_HPP

#include "fwd_declares.hpp"


namespace xlog
{
    struct LogStreamTraits
    {
        typedef buffer_t value_type;
        typedef std::ptrdiff_t difference_type;
        typedef value_type* pointer;
        typedef value_type& reference;
        typedef std::output_iterator_tag iterator_category;
    };
}

#endif