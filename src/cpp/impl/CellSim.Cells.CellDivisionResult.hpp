#ifndef CELLSIM_CELLS_CELLDIVISIONRESULT_HPP
#define CELLSIM_CELLS_CELLDIVISIONRESULT_HPP

#include "base.hpp"
#include "CellSim.Cells.DaughterCellInfo.hpp"

namespace CellSim::Cells
{
    struct CellDivisionResult {
        DaughterCellInfo OriginalDaughter;
        DaughterCellInfo NewDaughter;
    };
}

#endif //!CELLSIM_CELLS_CELLDIVISIONRESULT_HPP