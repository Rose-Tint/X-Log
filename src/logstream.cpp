#include "logstream.hpp"


namespace xlog
{
    LogStream::LogStream(ilist<buffer_t> bufs)
        : buffers(bufs.begin(), bufs.end())
    {
        io_lock = ulock_t(io_mtx, std::defer_lock);
    }

    LogStream::~LogStream()
    {
        for (thread_t& thread : threads)
        {
            thread.join();
        }
    }

    LogStream& LogStream::operator=(LogStream&& other)
    {
        UNLIKELY if (this == &other) return *this;
        io_lock = std::move(other.io_lock);
        buffers = std::move(other.buffers);
        for (thread_t& thread : other.threads)
        {
            thread.join();
        }
        threads = std::move(other.threads);
        return *this;
    }

    LogStream::LogStream(LogStream&& other)
    {
        io_lock = std::move(other.io_lock);
        buffers = std::move(other.buffers);
        for (thread_t& thread : other.threads)
        {
            thread.join();
        }
        threads = std::move(other.threads);
    }

    LogStream& LogStream::add_buffer(buffer_t buf)
    {
        bool is_new = true;
        for (buffer_t buffer : buffers)
        {
            is_new &= (buf == buffer);
        }

        if (is_new) buffers.push_back(buf);
        return *this;
    }

    void LogStream::flush()
    {
        thread_t thread(_flush, this);
        threads.push_back(std::move(thread));
    }

    void LogStream::_flush(LogStream* ls)
    {
        ls->io_lock.lock();
        for (auto buffer : ls->buffers)
        {
            buffer->pubsync();
        }
        ls->io_lock.unlock();
    }

    void LogStream::write(const std::string& str)
    {
        thread_t thread(_write, str, this);
        threads.push_back(std::move(thread));
    }

    void LogStream::_write(const std::string& str, LogStream* ls)
    {
        ls->io_lock.lock();
        for (auto buffer : ls->buffers)
        {
            buffer->sputn(str.c_str(), str.size());
        }
        ls->io_lock.unlock();
    }
}
