#ifndef X_LOG_STREAM_LOGSTREAMBASE_HPP
#define X_LOG_STREAM_LOGSTREAMBASE_HPP

#include "fwd_declares.hpp"
#include "Thread.hpp"
#include "streams/LogStreamIter.hpp"


namespace xlog
{
    class LogStreamBase
    {
      protected:
        static mutex_t io_mtx;

        virtual void vemit(const string_t&);
        virtual void vflush();
        virtual void vflush(buffer_t);
        virtual void write(buffer_t, const string_t&);

        // current problem: waste of memory when a thread finishes
        // execution until it gets flushed due to staying in vector
        ulock_t io_lock;
        std::vector<Thread> threads;
        std::vector<buffer_t> buffers;

      public:
        LogStreamBase();
        explicit LogStreamBase(ulock_t&&);
        explicit LogStreamBase(buffer_t);
        template<class It, utils::EnableIterFor<buffer_t, It> = true>
        explicit LogStreamBase(It, It);

        LogStreamBase(LogStreamBase&&) = delete;
        LogStreamBase(const LogStreamBase&) = delete;
        LogStreamBase& operator=(LogStreamBase&&) = delete;
        LogStreamBase& operator=(const LogStreamBase&) = delete;

        virtual ~LogStreamBase() = default;

        void add_outstreams(buffer_t buffer) { buffers.push_back(buffer); }
        template<class It, utils::EnableIterFor<buffer_t, It> = true>
        void add_outstreams(It, It);
        void emit(const string_t&);
        void flush();
    };
}

#endif