#ifndef X_LOG_HANDLER_HPP
#define X_LOG_HANDLER_HPP

#include "fwd_declares.hpp"
#include "record.hpp"


namespace xlog
{
    class LogStream
    {
        static std::mutex io_mtx;
        ulock_t io_lock = ulock_t(io_mtx, std::defer_lock);
        static void write(buffer_t, const std::string&);
        std::vector<buffer_t> buffers;

      public:
        explicit LogStream() = default;
        void add_buffer(buffer_t);
        void send(const std::string&);
    };
}

#endif