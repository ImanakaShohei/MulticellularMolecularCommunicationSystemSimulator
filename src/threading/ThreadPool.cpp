#include "ThreadPool.hpp"
#include <chrono>

ThreadPool::ThreadPool() : ThreadPool(::std::thread::hardware_concurrency())
{
}

#if SIM_ENV_WINDOWS
ThreadPool::ThreadPool(uint32_t threadCount)
    , m_currentTasks(0)
    , m_threadCount(threadCount)
    , m_pool(::CreateThreadpool(nullptr))
    , m_env()
{
    if (m_pool == nullptr) [[unlikely]] throw ::std::runtime_error("Failed to create ThreadPool.");

    ::SetThreadpoolThreadMaximum(m_pool, threadCount);
    ::InitializeThreadpoolEnvironment(&m_env);
    ::SetThreadpoolCallbackPool(&m_env, m_pool);
}

ThreadPool::~ThreadPool()
{
    waitAll();

    ::DestroyThreadpoolEnvironment(&m_env);
    ::CloseThreadpool(m_pool);
}

void ThreadPool::appendTask(TaskEntryPoint entryPoint)
{
    appendTask(entryPoint, (void*)nullptr);
}

void ThreadPool::appendTask(TaskEntryPoint entryPoint, ::std::nullptr_t)
{
    appendTask(entryPoint, (void*)nullptr);
}

void ThreadPool::appendTask(TaskEntryPoint entryPoint, void* args)
{
    ::PTP_WORK work = ::CreateThreadpoolWork(s_callback2, new s_task{ entryPoint, args }, &m_env);
    ++m_currentTasks;
    ::SubmitThreadpoolWork(work);

    ::CloseThreadpoolWork(work);
}

void ThreadPool::parallelFor(size_t begin, size_t end, ::std::function<void(size_t)>&& f)
{
    parallelFor(m_threadCount, begin, end, ::std::move(f));
}

void ThreadPool::waitAll() noexcept
{
    using namespace std::chrono;

    while (currentTasks() != 0) {
        Sleep(1);
    }
}

void ThreadPool::s_callback2(::PTP_CALLBACK_INSTANCE, ::PVOID context, ::PTP_WORK)
{
    s_task* pTask = static_cast<s_task*>(context);

    pTask->m_func(pTask->args);

    delete pTask;
}

#else
ThreadPool::ThreadPool(uint32_t threadCount)
    : m_workers()
    , m_tasks()
    , m_mutex()
    , m_condition()
    , m_isRunning(true)
    , m_currentTasks(0)
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
    {
        ::std::unique_lock<::std::mutex> lock(m_mutex);
        m_tasks.push(s_task{ entryPoint, nullptr });
        ++m_currentTasks;
    }
    
    m_condition.notify_one();
}

void ThreadPool::appendTask(TaskEntryPoint entryPoint, ::std::nullptr_t)
{
    {
        ::std::unique_lock<::std::mutex> lock(m_mutex);
        m_tasks.push(s_task{ entryPoint, nullptr });
        ++m_currentTasks;
    }
    
    m_condition.notify_one();
}

void ThreadPool::appendTask(TaskEntryPoint entryPoint, void* args)
{
    {
        ::std::unique_lock<::std::mutex> lock(m_mutex);
        m_tasks.push(s_task{ entryPoint, args });
        ++m_currentTasks;
    }

    m_condition.notify_one();
}

void ThreadPool::parallelFor(size_t begin, size_t end, ::std::function<void(size_t)>&& f)
{
    parallelFor((uint32_t)m_workers.size(), begin, end, ::std::move(f));
}

void ThreadPool::waitAll() noexcept
{
    using namespace std::chrono;

    while (currentTasks() != 0) {
        ::std::this_thread::sleep_for(1ms);
    }
}

ThreadPool::s_task ThreadPool::m_getTask()
{
    ::std::unique_lock<::std::mutex> lock(m_mutex);

    while (m_tasks.size() == 0 && m_isRunning) {
        m_condition.wait(lock);
    }

    if (!m_isRunning && m_tasks.size() == 0) return s_task{};

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
            --threadPool.m_currentTasks;
        }
    }
}
#endif

void ThreadPool::parallelFor(uint32_t threadCount, size_t begin, size_t end, ::std::function<void(size_t)>&& f)
{
    ::std::function<void(size_t)> f1 = ::std::move(f);

    struct fArgs {
        size_t b;
        size_t e;
        ::std::function<void(size_t)> f;
#if SIM_ENV_WINDOWS
        ::PTP_WORK work;
#endif
    };
#if SIM_ENV_WINDOWS
    void(*func)(::PTP_CALLBACK_INSTANCE, ::PVOID, ::PTP_WORK) = [](::PTP_CALLBACK_INSTANCE, ::PVOID context, ::PTP_WORK) {
        fArgs& fargs = *static_cast<fArgs*>(context);
        while (fargs.b != fargs.e) {
            fargs.f(fargs.b);
            ++fargs.b;
        }
    };
#else
    void(*func)(void*) = [](void* args) {
        fArgs& fargs = *static_cast<fArgs*>(args);
        while (fargs.b != fargs.e) {
            fargs.f(fargs.b);
            ++fargs.b;
        }
    };
#endif
    size_t count = end - begin;

    if (count == 0) [[unlikely]] return;

    size_t listCapacity;

    if (threadCount > count) listCapacity = count;
    else listCapacity = threadCount;

    ::std::vector<fArgs> list;

    if (list.capacity() < listCapacity) {
        list.reserve(listCapacity);
    }

    size_t c = count % listCapacity;
    size_t d = count / listCapacity;

    if (c == 0) {
        for (size_t i = begin; i != end;) {
            list.emplace_back(fArgs{ i, i += d, f1 });
#if SIM_ENV_WINDOWS
            auto& back = list.back();
            ::PTP_WORK work = ::CreateThreadpoolWork(func, &back, &m_env);
            ++m_currentTasks;
            ::SubmitThreadpoolWork(work);
            
            back.work = work;
#else
            appendTask(func, &list.back());
#endif
        }
    }
    else {
        size_t n = d * (listCapacity * (d + 1) - count);
        size_t i = 0;

        while (i != n) {
            list.emplace_back(fArgs{ i, i += d, f1 });
#if SIM_ENV_WINDOWS
            auto& back = list.back();
            ::PTP_WORK work = ::CreateThreadpoolWork(func, &back, &m_env);
            ++m_currentTasks;
            ::SubmitThreadpoolWork(work);
            
            back.work = work;
#else
            appendTask(func, &list.back());
#endif
        }

        d++;

        while (i != count) {
            list.emplace_back(fArgs{ i, i += d, f1 });
#if SIM_ENV_WINDOWS
            auto& back = list.back();
            ::PTP_WORK work = ::CreateThreadpoolWork(func, &back, &m_env);
            ++m_currentTasks;
            ::SubmitThreadpoolWork(work);
            
            back.work = work;
#else
            appendTask(func, &list.back());
#endif
        }
    }

#if SIM_ENV_WINDOWS
    for (auto& args : list) {
        PTP_WORK work = args.work;
        ::WaitForThreadpoolWorkCallbacks(args.work, FALSE);
        --m_currentTasks;
        ::CloseThreadpoolWork(work);
    }
#else
    waitAll();
#endif
}