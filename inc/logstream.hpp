#ifndef X_LOG_LOGSTREAM_HPP
#define X_LOG_LOGSTREAM_HPP

#include "fwd_declares.hpp"
#include "record.hpp"


namespace xlog
{
    class LogStream
    {
        static mutex_t io_mtx;
        virtual void _write(const std::string&, LogStream*);
        virtual void _flush(LogStream*);

        ulock_t io_lock;
        std::vector<thread_t> threads;
        std::vector<buffer_t> buffers;

      public:
        LogStream() = default;
        explicit LogStream(ilist<buffer_t>);
        LogStream& operator=(LogStream&&);
        LogStream& operator=(const LogStream&);

        virtual ~LogStream();

        LogStream(const LogStream&) = delete;

        LogStream& add_buffer(buffer_t);
        LogStream& add_stream(const std::ostream&);
        void write(const std::string&);
        void flush();
    };
}

#endif