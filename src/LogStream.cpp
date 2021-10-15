#include "logstream.hpp"


namespace xlog
{
    LogStreamBase::LogStreamBase(ilist<buffer_t> bufs)
        : buffers(buffers.end(), bufs), io_lock(io_mtx, std::defer_lock) { }

    LogStreamBase& LogStreamBase::operator=(LogStreamBase&& other)
    {
        if (this == &other) return *this;
        for (thread_t& thread : other.threads)
            thread.join();
        buffers = std::move(other.buffers);
        io_lock = std::move(other.io_lock);
        threads = std::move(other.threads);
        return *this;
    }

    LogStreamBase& LogStreamBase::operator=(const LogStreamBase& other)
    {
        if (this == &other) return *this;
        for (thread_t& thread : other.threads)
            thread.join();
        buffers = other.buffers;
        io_lock = ulock_t(io_mtx, std::defer_lock);
        return *this;
    }

    LogStreamBase::LogStreamBase(LogStreamBase&& other)
    {
        for (thread_t& thread : other.threads)
            thread.join();
        io_lock = std::move(other.io_lock);
        buffers = std::move(other.buffers);
        threads = std::move(other.threads);
    }

    LogStreamBase& LogStreamBase::add_buffer(buffer_t buf)
    {
        bool is_new = true;
        for (buffer_t buffer : buffers)
            is_new &= (buf == buffer);

        if (is_new) buffers.push_back(buf);
        return *this;
    }

    void LogStreamBase::flush()
    {
        Thread thread;
        thread.run_locked(io_lock, &LogStreamBase::_flush, *this)
        threads.push_back(std::move(thread));
    }

    void LogStreamBase::_flush()
    {
        for (auto buffer : buffers)
            buffer->pubsync();
    }

    void LogStreamBase::write(const std::string& str)
    {
        Thread thread;
        thread.run_locked(io_lock, &LogStreamBase::vwrite, this, str);
        threads.push_back(std::move(thread));
    }

    void LogStreamBase::vwrite(const std::string& str)
    {
        for (auto buffer : ls->buffers)
            buffer->sputn(str.c_str(), str.size());
    }
}
