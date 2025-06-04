#ifndef CELLSIM_THREADING_STLTHREADPOOL_HPP
#define CELLSIM_THREADING_STLTHREADPOOL_HPP

// https://github.com/KongkongNT15/KongkongLibrary/blob/main/src/include/klib/Definitions/Kongkong.Std.StlThreadPool.h

#include "base.hpp"

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace CellSim::Threading
{
    /// @brief 標準ライブラリを用いたスレッドプール
    class StlThreadPool final {
        public:
        using TaskEntryPoint = void(*)(void*);

        private:

        struct s_task {
            TaskEntryPoint m_func;
            void* args;
        };

        static void s_workerEntryPoint(StlThreadPool* pStlThreadPool);

        ::std::vector<::std::thread> m_workers;
        ::std::queue<s_task> m_tasks;
        ::std::mutex m_mutex;
        ::std::condition_variable m_condition;
        bool m_isRunning;
        ::std::atomic<uint32_t> m_currentTasks;

        s_task m_getTask();
        public:

        explicit StlThreadPool();
        explicit StlThreadPool(uint32_t threadCount);

        StlThreadPool(StlThreadPool const&) = delete;
        StlThreadPool(StlThreadPool&&) = delete;

        ~StlThreadPool();

        StlThreadPool& operator=(StlThreadPool const&) = delete;
        StlThreadPool& operator=(StlThreadPool&&) = delete;

        /// @brief ふぁ！？っく
        void AppendTask(::std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        void AppendTask(::std::nullptr_t, ::std::nullptr_t) = delete;

        /// @brief ふぁ！？っく
        void AppendTask(::std::nullptr_t, void*) = delete;

        /// @brief タスクを追加
        /// @attention この関数はentryPointがnullptrであるかどうかを判定しないよ！
        /// @param entryPoint エントリーポイント
        void AppendTask(TaskEntryPoint entryPoint);

        /// @brief タスクを追加
        /// @attention この関数はentryPointがnullptrであるかどうかを判定しないよ！
        /// @param entryPoint エントリーポイント
        void AppendTask(TaskEntryPoint entryPoint, ::std::nullptr_t);

        /// @brief タスクを追加
        /// @attention この関数はentryPointがnullptrであるかどうかを判定しないよ！
        /// @param entryPoint エントリーポイント
        /// @param args パラメータ
        void AppendTask(TaskEntryPoint entryPoint, void* args);

        [[nodiscard]] uint32_t CurrentTasks() const noexcept;

        /// @brief ワーカースレッド数
        [[nodiscard]] constexpr uint32_t ThreadCount() const noexcept;

        /// @brief すべてのタスクが終了するまで待機
        void WaitAll() noexcept;
        
    };
}

namespace CellSim::Threading
{
    inline uint32_t StlThreadPool::CurrentTasks() const noexcept
    {
        return m_currentTasks.load();
    }

    constexpr uint32_t StlThreadPool::ThreadCount() const noexcept
    {
        return (uint32_t)m_workers.size();
    }
}

#endif //!CELLSIM_THREADING_STLTHREADPOOL_HPP