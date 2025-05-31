#ifndef CELLSIM_CELLS_CELLBEHAVIOR_HPP
#define CELLSIM_CELLS_CELLBEHAVIOR_HPP

#include "base.hpp"

namespace CellSim::Cells
{
    /// @brief 細胞のふるまい
    class CellBehavior {
        public:

        /// @brief 細胞分裂
        /// @param target 分裂させる細胞
        /// @return 新しくできた細胞
        [[nodiscard]] virtual Cell Devide(Cell& target) = 0;
    };
}

#endif //!CELLSIM_CELLS_CELLBEHAVIOR_HPP