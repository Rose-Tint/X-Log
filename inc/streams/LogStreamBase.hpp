#ifndef X_LOG_STREAM_LOGSTREAMBASE_HPP
#define X_LOG_STREAM_LOGSTREAMBASE_HPP

#include "fwd_declares.hpp"
#include "Thread.hpp"
#include "record.hpp"
#include "streams/LogStreamIter.hpp"


namespace xlog
{
    template<class BufferType>
    class LogStreamBase
    {
      protected:
        typedef BufferType value_type;
        typedef value_type& reference;
        typedef const reference const_reference;
        typedef LogStreamIter iterator;
        typedef LogStreamIter const_iterator;
        typedef uint size_type;
        typedef signed int difference_type;

        static mutex_t io_mtx;

        virtual void _write(const string_t&) = 0;
        virtual void _flush() = 0;

        ulock_t io_lock;
        std::vector<Thread> threads;
        std::vector<value_type> buffers;

      public:
        LogStreamBase() = default;
        explicit LogStreamBase(ilist<value_type>);
        LogStreamBase(LogStreamBase&&);
        LogStreamBase(const LogStreamBase&);
        LogStreamBase& operator=(LogStreamBase&&);
        LogStreamBase& operator=(const LogStreamBase&);

        virtual ~LogStreamBase();

        LogStreamBase& add_buffer(value_type);
        void write(const string_t&);
        void flush();
        // STL container named requirements
        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
        const_iterator cbegin();
        const_iterator cend();
        bool operator==(const LogStreamBase&) const;
        bool operator!=(const LogStreamBase&) const;
        void swap(LogStreamBase&);
        size_type size() const;
        size_type max_size() const;
        bool empty() const;
    };
}

#endif