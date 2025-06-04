#include "CellSim.Threading.ThreadPool.hpp"

#if CELLSIM_ENV_WINDOWS
    #include <Windows.h>
#endif

namespace CellSim::Threading
{
#if !CELLSIM_ENV_WINDOWS
        StlThreadPool ThreadPool::s_pool;
#endif

    void ThreadPool::ParallelFor(uint32_t threadCount, size_t begin, size_t end, ::std::function<void(size_t)> const& f)
    {
        struct fArgs {
            size_t b;
            size_t e;
            ::std::function<void(size_t)> f;
#if CELLSIM_ENV_WINDOWS
            ::PTP_WORK work;
#endif
        };
#if CELLSIM_ENV_WINDOWS
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
                list.emplace_back(fArgs{ i, i += d, f });
#if CELLSIM_ENV_WINDOWS
                auto& back = list.back();
                ::PTP_WORK work = ::CreateThreadpoolWork(func, &back, nullptr);
                ::SubmitThreadpoolWork(work);
                
                back.work = work;
#else
                s_pool.AppendTask(func, &list.back());
#endif
            }
        }
        else {
            size_t n = d * (listCapacity * (d + 1) - count);
            size_t i = 0;

            while (i != n) {
                list.emplace_back(fArgs{ i, i += d, f });
#if CELLSIM_ENV_WINDOWS
                auto& back = list.back();
                ::PTP_WORK work = ::CreateThreadpoolWork(func, &back, nullptr);
                ::SubmitThreadpoolWork(work);
                
                back.work = work;
#else
                s_pool.AppendTask(func, &list.back());
#endif
            }

            d++;

            while (i != count) {
                list.emplace_back(fArgs{ i, i += d, f });
#if CELLSIM_ENV_WINDOWS
                auto& back = list.back();
                ::PTP_WORK work = ::CreateThreadpoolWork(func, &back, nullptr);
                ::SubmitThreadpoolWork(work);
                
                back.work = work;
#else
                s_pool.AppendTask(func, &list.back());
#endif
            }
        }

#if CELLSIM_ENV_WINDOWS
        for (auto& args : list) {
            ::PTP_WORK work = args.work;
            ::WaitForThreadpoolWorkCallbacks(work, FALSE);
            ::CloseThreadpoolWork(work);
        }
#else
        s_pool.WaitAll();
#endif
    }
}