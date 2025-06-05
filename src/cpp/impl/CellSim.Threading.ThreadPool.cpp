#include "CellSim.Threading.ThreadPool.hpp"

namespace CellSim::Threading
{
#if !CELLSIM_ENV_WINDOWS
        StlThreadPool ThreadPool::s_pool;
#endif
}