#ifndef X_LOG_STREAM_LOGSTREAMBASE_HPP
#define X_LOG_STREAM_LOGSTREAMBASE_HPP

#include "fwd_declares.hpp"
#include "Thread.hpp"
#include "record.hpp"
#include "streams/LogStreamIter.hpp"


namespace xlog
{
    class LogStreamBase
    {
        void write_wrapper();
        void flush_wrapper();

      protected:
        static mutex_t io_mtx;

        virtual void vwrite(const string_t&) = 0;
        virtual void vflush() = 0;

        ulock_t io_lock;
        std::vector<thread_t> threads;
        std::vector<value_type> buffers;

      public:
        LogStreamBase();
        explicit LogStreamBase(value_type);
        explicit LogStreamBase(ilist<value_type>);
        LogStreamBase(value_type*, value_type*);
        template<class Iter>
        explicit LogStreamBase(Iter, Iter, iter_tag<Iter>* = nullptr);

        LogStreamBase(LogStreamBase&&);
        LogStreamBase(const LogStreamBase&);
        LogStreamBase& operator=(LogStreamBase&&);
        LogStreamBase& operator=(const LogStreamBase&);

        typedef buffer_t value_type;
        typedef value_type& reference;
        typedef const reference const_reference;
        typedef LogStreamIter iterator;
        typedef LogStreamIter const_iterator;
        typedef uint size_type;
        typedef signed int difference_type;

        virtual ~LogStreamBase() = default;

        LogStreamBase& add_output(value_type);
        void write(const string_t&);
        void flush();

        // STL container named requirements
        virtual iterator begin();
        virtual iterator end();
        virtual const_iterator begin() const;
        virtual const_iterator end() const;
        virtual const_iterator cbegin();
        virtual const_iterator cend();
        virtual bool operator==(const LogStreamBase&) const;
        virtual bool operator!=(const LogStreamBase&) const;
        virtual void swap(LogStreamBase&);
        virtual size_type size() const;
        virtual size_type max_size() const;
        virtual bool empty() const;
    };
}

#endif