#include "logstream.hpp"


namespace xlog
{
    void LogStream::write(const std::string& str)
    {
        io_lock.lock();
        for (buffer_t buffer : buffers)
        {
            std::ostream(buffer) << str;
        }
        io_lock.unlock();
    }

    void LogStream::send(const std::string& str)
    {
        thread_t thread = thread_t(&write, str);
        thread.detach();
    }
}
