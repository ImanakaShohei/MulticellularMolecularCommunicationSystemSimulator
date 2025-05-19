#pragma once

#include "../core/base.hpp"

#include <thread>
#include <vector>
#include <queue>
#include <condition_variable>
#include <functional>
#include <coroutine>
#include <atomic>
#include "AsyncAction.hpp"

#if SIM_ENV_WINDOWS
    #include <Windows.h>
#endif

class ThreadPool final {
    public:
    using TaskEntryPoint = void(*)(void*);

    private:

    template <class FArgs, class Args>
    struct s_actionArgs0 {
        ThreadPool* pThreadPool;
        void(*func)(FArgs);
        Args args;
        ::std::coroutine_handle<> h;
    };

    template <class FArgs, class Args>
    struct s_actionArgs1 {
        ThreadPool* pThreadPool;
        const ::std::function<void(FArgs)>* func;
        Args args;
        ::std::coroutine_handle<> h;
    };

    struct s_task {
        TaskEntryPoint m_func;
        void* args;
    };

#if SIM_ENV_WINDOWS
    ::std::atomic<uint32_t> m_currentTasks;
    uint32_t m_threadCount;
    ::PTP_POOL m_pool;
    ::TP_CALLBACK_ENVIRON m_env;

    template <class FArgs, class Args>
    static void s_callback0(::PTP_CALLBACK_INSTANCE instance, ::PVOID context, ::PTP_WORK work);

    template <class FArgs, class Args>
    static void s_callback1(::PTP_CALLBACK_INSTANCE instance, ::PVOID context, ::PTP_WORK work);

    static void s_callback2(::PTP_CALLBACK_INSTANCE instance, ::PVOID context, ::PTP_WORK work);
#else

    ::std::vector<::std::thread> m_workers;
    ::std::queue<s_task> m_tasks;
    ::std::mutex m_mutex;
    ::std::condition_variable m_condition;
    bool m_isRunning;
    ::std::atomic<uint32_t> m_currentTasks;

    s_task m_getTask();

    template <class FArgs, class Args>
    static void s_callback0(void* args);

    template <class FArgs, class Args>
    static void s_callback1(void* args);

    static void s_workerEntryPoint(ThreadPool* pThreadPool);
#endif
    public:

    explicit ThreadPool();
    explicit ThreadPool(uint32_t threadCount);

    ThreadPool(ThreadPool const&) = delete;
    ThreadPool(ThreadPool&&) = delete;

    ~ThreadPool();

    ThreadPool& operator=(ThreadPool const&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

    /// @brief ふぁ！？っく
    void appendTask(::std::nullptr_t) = delete;

    /// @brief ふぁ！？っく
    void appendTask(::std::nullptr_t, ::std::nullptr_t) = delete;

    /// @brief ふぁ！？っく
    void appendTask(::std::nullptr_t, void*) = delete;

    /// @brief タスクを追加
    /// @attention この関数はentryPointがnullptrであるかどうかを判定しないよ！
    /// @param entryPoint エントリーポイント
    void appendTask(TaskEntryPoint entryPoint);

    /// @brief タスクを追加
    /// @attention この関数はentryPointがnullptrであるかどうかを判定しないよ！
    /// @param entryPoint エントリーポイント
    void appendTask(TaskEntryPoint entryPoint, ::std::nullptr_t);

    /// @brief タスクを追加
    /// @attention この関数はentryPointがnullptrであるかどうかを判定しないよ！
    /// @param entryPoint エントリーポイント
    /// @param args パラメータ
    void appendTask(TaskEntryPoint entryPoint, void* args);

    [[nodiscard]]
    uint32_t currentTasks() const noexcept { return m_currentTasks.load(); }

    void parallelFor(size_t begin, size_t end, ::std::function<void(size_t)>&& f);
    void parallelFor(uint32_t threadCount, size_t begin, size_t end, ::std::function<void(size_t)>&& f);

    template <class FArgs, class Args>
    AsyncAction runAsync(void(*func)(FArgs), Args args);

    template <class FArgs, class Args>
    AsyncAction runAsync(::std::function<void(FArgs)> const& func, Args args);

    template <class FArgs, class Args>
    AsyncAction runAsync(::std::function<void(FArgs)>&& func, Args args);

    /// @brief ワーカースレッド数
    [[nodiscard]]
    constexpr uint32_t threadCount() const noexcept;

    /// @brief すべてのタスクが終了するまで待機
    void waitAll() noexcept;
    
};

template <class FArgs, class Args>
AsyncAction ThreadPool::runAsync(void(*func)(FArgs), Args args)
{
    struct tmpAwaiter {
        constexpr bool await_ready() noexcept { return false; } // すぐには完了しない
        void await_suspend(::std::coroutine_handle<> h) {

            m_s.h = h;
#if SIM_ENV_WINDOWS
            ::PTP_WORK work = ::CreateThreadpoolWork(s_callback0<FArgs, Args>, &m_s, m_s.pThreadPool->m_env);
            ::SubmitThreadpoolWork(work);

            ::CloseThreadpoolWork(work);
#else
            m_s.pThreadPool->appendTask(ThreadPool::s_callback0<FArgs, Args>, &m_s);
#endif
        }
        constexpr void await_resume() noexcept {}
        
        ThreadPool::s_actionArgs0<FArgs, Args> m_s;
    };

    co_await tmpAwaiter{ this, func, args };
}

template <class FArgs, class Args>
AsyncAction ThreadPool::runAsync(::std::function<void(FArgs)> const& func, Args args)
{
    struct tmpAwaiter {
        constexpr bool await_ready() noexcept { return false; } // すぐには完了しない
        void await_suspend(::std::coroutine_handle<> h) {
            m_s.h = h;

#if SIM_ENV_WINDOWS
            ::PTP_WORK work = ::CreateThreadpoolWork(s_callback1<FArgs, Args>, &m_s, m_s.pThreadPool->m_env);
            ::SubmitThreadpoolWork(work);

            ::CloseThreadpoolWork(work);
#else
            m_s.pThreadPool->appendTask(ThreadPool::s_callback1<FArgs, Args>, &m_s);
#endif
        }
        constexpr void await_resume() noexcept {}
        
        ThreadPool::s_actionArgs1<FArgs, Args> m_s;
    };

    co_await tmpAwaiter{ this, &func, args };
}

template <class FArgs, class Args>
AsyncAction ThreadPool::runAsync(::std::function<void(FArgs)>&& func, Args args)
{
    ::std::function<void(FArgs)> f = ::std::move(func);

    co_await runAsync(f, args);
}

constexpr uint32_t ThreadPool::threadCount() const noexcept
{
#if SIM_ENV_WINDOWS
    return m_threadCount;
#else
    return (uint32_t)m_workers.size();
#endif
}

#if SIM_ENV_WINDOWS
template <class FArgs, class Args>
void ThreadPool::s_callback0(::PTP_CALLBACK_INSTANCE, ::PVOID context, ::PTP_WORK)
{
    s_actionArgs0<FArgs, Args>& actionArgs = *static_cast<s_actionArgs0<FArgs, Args>*>(context);

    actionArgs.func(actionArgs.args);

    actionArgs.h.resume();
    --actionArgs.pThreadPool->m_currentTasks;
}

template <class FArgs, class Args>
void ThreadPool::s_callback1(::PTP_CALLBACK_INSTANCE, ::PVOID context, ::PTP_WORK)
{
    s_actionArgs1<FArgs, Args>& actionArgs = *static_cast<s_actionArgs1<FArgs, Args>*>(context);

    actionArgs.func->operator()(actionArgs.args);

    actionArgs.h.resume();
    --actionArgs.pThreadPool->m_currentTasks;
}
#else
template <class FArgs, class Args>
void ThreadPool::s_callback0(void* args)
{
    s_actionArgs0<FArgs, Args>& actionArgs = *static_cast<s_actionArgs0<FArgs, Args>*>(args);

    actionArgs.func(actionArgs.args);

    actionArgs.h.resume();
}

template <class FArgs, class Args>
void ThreadPool::s_callback1(void* args)
{
    s_actionArgs1<FArgs, Args>& actionArgs = *static_cast<s_actionArgs1<FArgs, Args>*>(args);

    actionArgs.func->operator()(actionArgs.args);

    actionArgs.h.resume();
}
#endif
