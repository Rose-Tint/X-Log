#ifndef X_LOG_THREAD_HPP
#define X_LOG_THREAD_HPP


namespace xlog
{
    class Thread
    {
        std::thread thread;
        ulock_t& lock;

        template<class F, class... Args_t>
        void locking_wrapper(F, Args_t...);

      public:
        explicit Thread(ulock_t& lock)
            : lock(lock) { }
        template<class F, class... Args_t>
        explicit Thread(ulock_t& lock, F fn, Args_t... args)
            : lock(lock) { run(std::forward<F, Args_t... >(fn, args...)); }

        virtual ~Thread() { join(); }

        void join();
        template<class F, class... Args_t>
        void run(F, Args_t...);
    };
}

#endif