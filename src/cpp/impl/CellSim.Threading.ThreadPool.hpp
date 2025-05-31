#ifndef CELLSIM_THREADING_THREADPOOL_HPP
#define CELLSIM_THREADING_THREADPOOL_HPP

// https://github.com/KongkongNT15/KongkongLibrary/blob/main/src/include/klib/Definitions/Kongkong.Threading.ThreadPool.h

#include "base.hpp"

#if !CELLSIM_ENV_WINDOWS
    #include "CellSim.Threading.StlThreadPool.hpp"
#endif

#include <functional>
#include <thread>

namespace CellSim::Threading
{
    class ThreadPool final {
        private:

#if !CELLSIM_ENV_WINDOWS
        static StlThreadPool s_pool;
#endif

        public:

        CELLSIM_STATIC_CLASS(ThreadPool);

        // for (size_t i = begin; i != end; ++i) {
        //     f(i);
        // }

        /// @brief 範囲を並列処理
        /// @param begin 範囲のはじめの要素
        /// @param end 範囲の最後の次の要素
        /// @param f 実行する関数
        static void ParallelFor(size_t begin, size_t end, ::std::function<void(size_t)> const& f);

        /// @brief 範囲を並列処理
        /// @param threadCount スレッド数を指定
        /// @param begin 範囲のはじめの要素
        /// @param end 範囲の最後の次の要素
        /// @param f 実行する関数
        static void ParallelFor(uint32_t threadCount, size_t begin, size_t end, ::std::function<void(size_t)> const& f);


    };
}

namespace CellSim::Threading
{
    void ThreadPool::ParallelFor(size_t begin, size_t end, ::std::function<void(size_t)> const& f)
    {
        ParallelFor(::std::thread::hardware_concurrency(), begin, end, f);
    }
}

#endif //!CELLSIM_THREADING_THREADPOOL_HPP