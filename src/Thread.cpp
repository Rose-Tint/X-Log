#include "Thread.hpp"


namespace xlog
{
    template<class F, class... Args_t>
    void Thread::locking_wrapper(F func, Args_t... args)
    {
        lock.lock();
        std::invoke(std::forward<F>(func), std::forward<Args_t>(args)...);
        lock.unlock();
    }

    template<class F, class... Args_t>
    void Thread::run(F func, Args_t... args)
    {
        if (thread.joinable())
            join();
            thread = Thread(
            &Thread::locking_wrapper,
            this,
            std::forward<F>(func), 
            std::forward<Args_t>(args)...
        );
    }

    void Thread::join()
    {
        if (thread.joinable())
            thread.join();
    }
}
