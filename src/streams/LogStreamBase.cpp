#include "streams/LogStreamBase.hpp"


namespace xlog
{
    LogStreamBase::LogStreamBase()
        : io_lock(io_mtx, std::defer_lock) { }

    LogStreamBase::LogStreamBase(ulock_t&& lock)
        : io_lock(lock) { }

    LogStreamBase::LogStreamBase(buffer_t buffer)
        : LogStreamBase() // call default ctor for io_lock
    {
        add_outstreams(buffer);
    }

    template<class It, utils::EnableIterFor<fs::path, It>>
    LogStreamBase::LogStreamBase(It begin, It end)
        : LogStreamBase() // call default ctor for io_lock
    {
        for (auto iter = begin; iter < end; iter++)
            add_outstreams(*iter);
    }

    void LogStreamBase::write(buffer_t buffer, const string_t& msg)
    {
        buffer->sputn(msg.c_str(), msg.size());
    }

    void LogStreamBase::vemit(const string_t& msg)
    {
        for (buffer_t buffer : buffers)
            write(buffer, msg);
    }

    void LogStreamBase::emit(const string_t& msg)
    {
        threads.emplace_back(io_lock, &LogStreamBase::vemit, this, msg);
    }

    void LogStreamBase::flush()
    {
        threads.emplace_back(io_lock, &LogStreamBase::vflush, this);
        for (Thread& thread : threads)
            thread.join();
    }

    void LogStreamBase::vflush()
    {
        for (buffer_t buffer : buffers)
            threads.emplace_back(io_lock, &LogStreamBase::vflush, this, buffer);
    }

    template<class It, utils::EnableIterFor<fs::path, It>>
    void LogStreamBase::add_outstreams(It begin, It end)
    {
        for (auto iter = begin; iter < end; iter++)
            buffers.push_back(*iter);
    }

    void LogStreamBase::swap(LogStreamBase& other)
    {
        Thread this_thread(&LogStreamBase::flush, this);
        Thread other_thread(&LogStreamBase::flush, &other);
        this_thread.join();
        other_thread.join();
        buffers.swap(other.buffers);
        io_lock.swap(other.io_lock);
    }
}
