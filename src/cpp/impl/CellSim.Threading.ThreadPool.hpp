#ifndef CELLSIM_THREADING_THREADPOOL_HPP
#define CELLSIM_THREADING_THREADPOOL_HPP

// https://github.com/KongkongNT15/KongkongLibrary/blob/main/src/include/klib/Definitions/Kongkong.Threading.ThreadPool.h

#include "base.hpp"

#include <xutility>

#if CELLSIM_ENV_WINDOWS
    #include <Windows.h>
#else
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

        template <class TIterator, class TFunction>
        static void ParallelFor(TIterator begin, TIterator end, TFunction f);

        /// @brief 範囲を並列処理
        /// @param threadCount スレッド数を指定
        /// @param begin 範囲のはじめの要素
        /// @param end 範囲の最後の次の要素
        /// @param f 実行する関数
        template <class TIterator, class TFunction>
        static void ParallelFor(uint32_t threadCount, TIterator begin, TIterator end, TFunction f);


    };
}

namespace CellSim::Threading
{
    template <class TIterator, class TFunction>
    void ThreadPool::ParallelFor(TIterator begin, TIterator end, TFunction f)
    {
        ParallelFor(::std::thread::hardware_concurrency(), begin, end, f);
    }

    template <class TIterator, class TFunction>
    void ThreadPool::ParallelFor(uint32_t threadCount, TIterator begin, TIterator end, TFunction f)
    {
        struct fArgs {
            TIterator b;
            TIterator e;
            TFunction f;
#if CELLSIM_ENV_WINDOWS
            ::PTP_WORK work;
#endif
        };
#if CELLSIM_ENV_WINDOWS
        void(*func)(::PTP_CALLBACK_INSTANCE, ::PVOID, ::PTP_WORK) = [](::PTP_CALLBACK_INSTANCE, ::PVOID context, ::PTP_WORK) {
            fArgs& fargs = *static_cast<fArgs*>(context);
            while (fargs.b != fargs.e) {
                if constexpr (::std::random_access_iterator<TIterator>) {
                    fargs.f(*fargs.b);
                }
                else {
                    fargs.f(fargs.b);
                }
                
                ++fargs.b;
            }
        };
    #else
        void(*func)(void*) = [](void* args) {
            fArgs& fargs = *static_cast<fArgs*>(args);
            while (fargs.b != fargs.e) {
                if constexpr (::std::random_access_iterator<TIterator>) {
                    fargs.f(*fargs.b);
                }
                else {
                    fargs.f(fargs.b);
                }

                ++fargs.b;
            }
        };
    #endif
        auto count = end - begin;

        if (count == 0) [[unlikely]] return;

        decltype(count) listCapacity;

        if ((decltype(count))threadCount > count) listCapacity = count;
        else listCapacity = threadCount;

        ::std::vector<fArgs> list;

        if ((decltype(count))list.capacity() < listCapacity) {
            list.reserve(listCapacity);
        }

        decltype(count) c = count % listCapacity;
        decltype(count) d = count / listCapacity;

        if (c == 0) {
            for (size_t i = 0; (begin + i) != end;) {
                list.emplace_back(fArgs{ begin + i, begin + (i += d), f });
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
                list.emplace_back(fArgs{ begin + i, begin + (i += d), f });
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
                list.emplace_back(fArgs{ begin + i, begin + (i += d), f });
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

#endif //!CELLSIM_THREADING_THREADPOOL_HPP