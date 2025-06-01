#ifndef CELLSIM_CELLS_CELLBEHAVIORTYPE_HPP
#define CELLSIM_CELLS_CELLBEHAVIORTYPE_HPP

#include "base.hpp"

namespace CellSim::Cells
{
    /// @brief CellBehaviorの種類
    enum class CellBehaviorType {
        Normal,
        User
    };
}

#endif //!CELLSIM_CELLS_CELLBEHAVIORTYPE_HPP