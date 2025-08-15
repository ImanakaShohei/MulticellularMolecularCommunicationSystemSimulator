#include "CellSim.Threading.StlThreadPool.hpp"
#include <chrono>

namespace CellSim::Threading
{
    void StlThreadPool::s_workerEntryPoint(StlThreadPool* pStlThreadPool)
    {
        StlThreadPool& StlThreadPool = *pStlThreadPool;

        while (StlThreadPool.m_isRunning) {
            s_task task = StlThreadPool.m_getTask();

            if (task.m_func != nullptr) {
                task.m_func(task.args);
                --StlThreadPool.m_currentTasks;
            }
        }
    }

    void StlThreadPool::m_appendThread()
    {
        m_workers.emplace_back(s_workerEntryPoint, this);
    }

    StlThreadPool::s_task StlThreadPool::m_getTask()
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
    
    StlThreadPool::StlThreadPool() : StlThreadPool(::std::thread::hardware_concurrency())
    {
    }

    StlThreadPool::StlThreadPool(uint32_t threadCount)
        : m_workers()
        , m_tasks()
        , m_mutex()
        , m_condition()
        , m_isRunning(true)
        , m_currentTasks(0)
    {
        try {
            for (size_t count = 0; count != threadCount; count++) {
                m_appendThread();
            }
        }
        catch (...) {
            StlThreadPool::~StlThreadPool();
            ::std::rethrow_exception(::std::current_exception());
        }
    }

    StlThreadPool::~StlThreadPool()
    {
        m_isRunning = false;

        m_condition.notify_all();

        for (::std::thread& t : m_workers) {
            t.join();
        }
    }

    void StlThreadPool::AppendTask(TaskEntryPoint entryPoint)
    {
        {
            ::std::unique_lock<::std::mutex> lock(m_mutex);
            m_tasks.push(s_task{ entryPoint, nullptr });
            ++m_currentTasks;
        }
        
        m_condition.notify_one();
    }

    void StlThreadPool::AppendTask(TaskEntryPoint entryPoint, ::std::nullptr_t)
    {
        {
            ::std::unique_lock<::std::mutex> lock(m_mutex);
            m_tasks.push(s_task{ entryPoint, nullptr });
            ++m_currentTasks;
        }
        
        m_condition.notify_one();
    }

    void StlThreadPool::AppendTask(TaskEntryPoint entryPoint, void* args)
    {
        {
            ::std::unique_lock<::std::mutex> lock(m_mutex);
            m_tasks.push(s_task{ entryPoint, args });
            ++m_currentTasks;
        }

        m_condition.notify_one();
    }

    bool StlThreadPool::SetMaxThreadCount(uint32_t threadCount)
    {
        auto currentThreadCount = ThreadCount();

        if (currentThreadCount < threadCount) {
            for (auto count = currentThreadCount; count < threadCount; count++) {
                m_appendThread();
            }

            return true;
        }

        return false;
    }

    void StlThreadPool::WaitAll() noexcept
    {
        using namespace std::chrono;

        while (CurrentTasks() != 0) {
            ::std::this_thread::sleep_for(1ms);
        }
    }

}