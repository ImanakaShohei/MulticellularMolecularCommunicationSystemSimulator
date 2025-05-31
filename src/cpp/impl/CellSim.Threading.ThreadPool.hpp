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

        static void ParallelFor(ssize_t begin, ssize_t end, ::std::function<void(size_t)> const& f);
        static void ParallelFor(uint32_t threadCount, ssize_t begin, ssize_t end, ::std::function<void(size_t)> const& f);


    };
}

namespace CellSim::Threading
{
    void ThreadPool::ParallelFor(ssize_t begin, ssize_t end, ::std::function<void(size_t)> const& f)
    {
        ParallelFor(::std::thread::hardware_concurrency(), begin, end, f);
    }
}

#endif //!CELLSIM_THREADING_THREADPOOL_HPP