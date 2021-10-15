#ifndef X_LOG_STREAMS_LOGSTREAMITER_HPP
#define X_LOG_STREAMS_LOGSTREAMITER_HPP

#include "fwd_declares"


namespace xlog
{
    class LogStreamIter final
    {
        char_t* c;
      public:
        typedef std::iterator_traits<LogStreamIter> Traits;

        LogStreamIter(const LogStreamIter&);
        LogStreamIter& operator=(const LogStreamIter&);

        ~LogStreamIter();

        void swap(LogStreamIter&);
        Traits::reference operator*();
        LogStreamIter& operator++();
    };

    template<>
    struct std::iterator_traits<LogStreamIter>
    {
        typedef buffer_t value_type;
        typedef std::ptrdiff_t difference_type;
        typedef value_type* pointer;
        typedef value_type& reference;
        typedef std::output_iterator_tag iterator_category;
    };
}

#endif