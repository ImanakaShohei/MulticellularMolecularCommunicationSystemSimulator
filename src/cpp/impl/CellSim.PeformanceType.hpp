#ifndef CELLSIM_PERFORMANCETYPE_HPP
#define CELLSIM_PERFORMANCETYPE_HPP

#include "base.hpp"

namespace CellSim
{
    /// @brief 最適化設定
    enum class PeformanceType {
        Fast,
        LowMemory,
    };
}

#endif //!CELLSIM_PERFORMANCETYPE_HPP