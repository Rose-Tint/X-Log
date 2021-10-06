#ifndef X_LOG_HANDLER_HPP
#define X_LOG_HANDLER_HPP

#include "fwd_declares.hpp"
#include "record.hpp"


namespace xlog
{
    class LogStream
    {
        static mutex_t io_mtx;
        static void write(const std::string&, LogStream*);
        static void flush(LogStream*);

        ulock_t io_lock = ulock_t(io_mtx, std::defer_lock);

        std::vector<thread_t> threads;

        /* 
         * even though unique value insertion would be much
         * faster using `unordered_set` or `set`, `vector` is
         * used because it iterates faster and uses less memory;
         * insertion (`add_buffer` | `add_path`) will happen
         * much less than iteration (`write`).
         */
        std::pmr::vector<buffer_t> buffers;

      public:
        LogStream() = default;
        explicit LogStream(std::ilist<buffer_t>);
        virtual ~LogStream();

        LogStream& add_buffer(buffer_t);

        void flush();
        void write(const std::string&);
    };
}

#endif