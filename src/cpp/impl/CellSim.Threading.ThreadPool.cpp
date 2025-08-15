#include "CellSim.Threading.ThreadPool.hpp"

namespace CellSim::Threading
{
#if !CELLSIM_ENV_WINDOWS
        StlThreadPool ThreadPool::s_pool{ ::std::thread::hardware_concurrency() > 32 ? ::std::thread::hardware_concurrency() : 32 };
#endif
}