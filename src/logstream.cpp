#include "logstream.hpp"


// LEFT OFF AT
// figuring out how to make the destructor safe
// current idea: launch a thread in the ctr that locks a mutex
//     and unlocks it when all child threads are finished
//     and the destructor will be waiting on that mutex so that
//     when all child threads die, the destructor can continue.


namespace xlog
{
    LogStream::LogStream(ilist<buffer_t> bufs)
        : buffers(bufs.begin(), bufs.end()) { }

    LogStream::~LogStream()
    {
        for (thread_t& thread : threads)
        {
            thread.join();
        }
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
        thread_t thread(&LogStream::flush, this);
        threads.push_back(std::move(thread));
    }

    void LogStream::flush(LogStream* ls)
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
        thread_t thread(&LogStream::write, str, this);
        threads.push_back(std::move(thread));
    }

    void LogStream::write(const std::string& str, LogStream* ls)
    {
        ls->io_lock.lock();
        for (auto buffer : ls->buffers)
        {
            buffer->sputn(str.c_str(), str.size());
        }
        ls->io_lock.unlock();
    }
}
