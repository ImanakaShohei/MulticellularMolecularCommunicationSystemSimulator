#pragma once

#include <thread>
#include <vector>
#include <queue>
#include <condition_variable>
#include <functional>
#include <coroutine>
#include "AsyncAction.hpp"

class ThreadPool final {
    public:
    using TaskEntryPoint = void(*)(void*);

    private:
    struct s_task {
        TaskEntryPoint m_func;
        void* args;
    };

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

    ::std::vector<::std::thread> m_workers;
    ::std::queue<s_task> m_tasks;
    ::std::mutex m_mutex;
    ::std::condition_variable m_condition;
    bool m_isRunning;

    s_task m_getTask();

    template <class FArgs, class Args>
    static void s_callback0(void* args);

    template <class FArgs, class Args>
    static void s_callback1(void* args);

    static void s_workerEntryPoint(ThreadPool* pThreadPool);
    public:

    explicit ThreadPool();
    explicit ThreadPool(size_t threadCount);

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

    AsyncAction parallelFor(size_t begin, size_t end, ::std::function<void(size_t)>&& f);
    AsyncAction parallelFor(uint32_t threadCount, size_t begin, size_t end, ::std::function<void(size_t)>&& f);

    template <class FArgs, class Args>
    AsyncAction runAsync(void(*func)(FArgs), Args args);

    template <class FArgs, class Args>
    AsyncAction runAsync(::std::function<void(FArgs)> const& func, Args args);

    template <class FArgs, class Args>
    AsyncAction runAsync(::std::function<void(FArgs)>&& func, Args args);

    /// @brief ワーカースレッド数
    [[nodiscard]]
    constexpr size_t threadCount() const noexcept { return m_workers.size(); }
    
};

template <class FArgs, class Args>
AsyncAction ThreadPool::runAsync(void(*func)(FArgs), Args args)
{
    struct tmpAwaiter {
        constexpr bool await_ready() noexcept { return false; } // すぐには完了しない
        void await_suspend(::std::coroutine_handle<> h) {

            m_s.h = h;

            m_s.pThreadPool->appendTask(ThreadPool::s_callback0<FArgs, Args>, &m_s);
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

            m_s.pThreadPool->appendTask(ThreadPool::s_callback1<FArgs, Args>, &m_s);
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