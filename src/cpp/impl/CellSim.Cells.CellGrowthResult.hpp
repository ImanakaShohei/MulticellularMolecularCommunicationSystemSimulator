#ifndef CELLSIM_CELLS_CELLGROWTHRESULT_HPP
#define CELLSIM_CELLS_CELLGROWTHRESULT_HPP

#include "base.hpp"

namespace CellSim::Cells
{
    /// @brief CellBehavior::ComputeGrowth()の戻り値
    struct CellGrowthResult {
        /// @brief 成長後の質量
        double NewMass;

        /// @brief 成長後の半径
        double NewRadius;
    };
}

#endif //!CELLSIM_CELLS_CELLGROWTHRESULT_HPP