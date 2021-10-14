#ifndef X_LOG_THREAD_HPP
#define X_LOG_THREAD_HPP


namespace xlog
{
    class Thread
    {
        // std::thread wrapper
        std::thread thread;

      public:
        Thread();
        Thread(mutex_t&);
        Thread(Thread&&);
        Thread(const Thread&);
        Thread& operator=(Thread&&);
        Thread& operator=(const Thread&);

        virtual ~Thread();

        void detach();
        void join();
        template<class Function_f, class... Args_t>
            void run(Function_f, Args_t);
        template<class T, class Function_f, class... Args_t>
            void run_member(T&, Function_f, Args_t);
        template<class Function_f, class... Args_t>
            void run_locked(ulock_t&, Function_f, Args_t);
        template<class T, class Function_f, class... Args_t>
            void run_member_locked(ulock_t&, T&, Function_f, Args_t);
    };
}

#endif