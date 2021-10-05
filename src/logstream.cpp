#include "logstream.hpp"


namespace xlog
{
    LogStream::LogStream(ilist<buffer_t> bufs)
        : buffers(bufs.begin(), bufs.end()) { }

    void LogStream::add_buffer(buffer_t buf)
    {
        buffers.push_back(buf);
    }

    void LogStream::write(const std::string& str)
    {
        io_lock.lock();
        for (buffer_t buf : buffers)
        {
            std::ostream(buf) << str;
        }
        io_lock.unlock();
    }

    void LogStream::send(const std::string& str)
    {
        thread_t thread = thread_t(&write, str);
        thread.detach();
    }
}
