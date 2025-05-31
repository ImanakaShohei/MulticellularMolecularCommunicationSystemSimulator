#include <stdio.h>
#include "../src/cpp/impl/CellSim.Threading.ThreadPool.hpp"

using namespace CellSim::Threading;

int main(void)
{
    ThreadPool::ParallelFor(
        0,
        200,
        [] (size_t i) {
            printf("%zu\n", i);
        }
    );

    return 0;
}