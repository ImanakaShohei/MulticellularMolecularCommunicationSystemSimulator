#include "ThreadPool.hpp"

ThreadPool::ThreadPool() : ThreadPool(::std::thread::hardware_concurrency())
{
}

ThreadPool::ThreadPool(uint32_t threadCount)
    : m_workers()
    , m_tasks()
    , m_mutex()
    , m_condition()
    , m_isRunning(true)
{
    try {
        for (size_t count = 0; count != threadCount; count++) {
            m_workers.emplace_back(s_workerEntryPoint, this);
        }
    }
    catch (...) {
        ThreadPool::~ThreadPool();
        ::std::rethrow_exception(::std::current_exception());
    }
}

ThreadPool::~ThreadPool()
{
    m_isRunning = false;

    m_condition.notify_all();

    for (::std::thread& t : m_workers) {
        t.join();
    }
}

void ThreadPool::appendTask(TaskEntryPoint entryPoint)
{
    ::std::unique_lock<::std::mutex> lock(m_mutex);
    m_tasks.push(s_task{ entryPoint, nullptr });

    m_condition.notify_one();
}

void ThreadPool::appendTask(TaskEntryPoint entryPoint, ::std::nullptr_t)
{
    ::std::unique_lock<::std::mutex> lock(m_mutex);
    m_tasks.push(s_task{ entryPoint, nullptr });

    m_condition.notify_one();
}

void ThreadPool::appendTask(TaskEntryPoint entryPoint, void* args)
{
    ::std::unique_lock<::std::mutex> lock(m_mutex);
    m_tasks.push(s_task{ entryPoint, args });

    m_condition.notify_one();
}

AsyncAction ThreadPool::parallelFor(size_t begin, size_t end, ::std::function<void(size_t)>&& f)
{
    return parallelFor((uint32_t)m_workers.size(), begin, end, ::std::move(f));
}

AsyncAction ThreadPool::parallelFor(uint32_t threadCount, size_t begin, size_t end, ::std::function<void(size_t)>&& f)
{
    ::std::function<void(size_t)> f1 = ::std::move(f);

    struct fArgs {
        size_t b;
        size_t e;
        ::std::function<void(size_t)> f;
    };

    void(*func)(fArgs) = [](fArgs args) {
        try {
            while (args.b != args.e) {
                args.f(args.b);
                ++args.b;
            }
        }
        catch (std::exception& e) {
            puts(e.what());
            exit(1);
        }        
    
    };

    size_t count = end - begin;

    if (count == 0) [[unlikely]] co_return;

    size_t listCapacity;

    if (threadCount > count) listCapacity = count;
    else listCapacity = threadCount;

    ::std::vector<AsyncAction> list;

    size_t c = count % listCapacity;
    size_t d = count / listCapacity;

    if (c == 0) {
        for (size_t i = begin; i != end;) {
            list.emplace_back(runAsync(func, fArgs{ i, i += d, f1 }));
        }
    }
    else {
        size_t n = d * (listCapacity * (d + 1) - count);
        size_t i = 0;

        while (i != n) {
            list.emplace_back(runAsync(func, fArgs{ i, i += d, f1 }));
        }

        d++;

        while (i != count) {
            list.emplace_back(runAsync(func, fArgs{ i, i += d, f1 }));
        }
    }

    for (AsyncAction& a : list) co_await a;

    co_return;
}



ThreadPool::s_task ThreadPool::m_getTask()
{
    ::std::unique_lock<::std::mutex> lock(m_mutex);

    while (m_tasks.size() == 0 && m_isRunning) {
        m_condition.wait(lock);
    }

    if (!m_isRunning) return s_task{};

    s_task result = m_tasks.front();

    m_tasks.pop();

    return result;
}

void ThreadPool::s_workerEntryPoint(ThreadPool* pThreadPool)
{
    ThreadPool& threadPool = *pThreadPool;

    while (threadPool.m_isRunning) {
        s_task task = threadPool.m_getTask();

        if (task.m_func != nullptr) {
            task.m_func(task.args);
        }
    }
}