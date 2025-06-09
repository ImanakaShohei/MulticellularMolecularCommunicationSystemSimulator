#ifndef CELLSIM_CELLS_DAUGHTERCELLINFO_HPP
#define CELLSIM_CELLS_DAUGHTERCELLINFO_HPP

#include "base.hpp"
#include "CellSim.Numerics.Vector3T.hpp"

namespace CellSim::Cells
{
    /// @brief 細胞分裂で使う
    struct DaughterCellInfo {
        double NewMass;
        double NewRadius;
        Numerics::Vector3 NewPosition;
    };
}

#endif //!CELLSIM_CELLS_DAUGHTERCELLINFO_HPP