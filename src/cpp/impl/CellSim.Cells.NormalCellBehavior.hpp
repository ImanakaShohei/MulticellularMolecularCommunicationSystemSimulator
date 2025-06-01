#ifndef CELLSIM_CELLS_NORMALCELLBEHAVIOR_HPP
#define CELLSIM_CELLS_NORMALCELLBEHAVIOR_HPP

#include "base.hpp"
#include "CellSim.Cells.CellBehavior.hpp"

namespace CellSim::Cells
{
    class NormalCellBehavior : public CellBehavior {
        public:

        CellGrowthResult ComputeGrowth(Cell const& cell) const override;
        CellBehavior* CreateClone() const override;
        constexpr bool HasState() const noexcept override;
    };
}

namespace CellSim::Cells
{
    inline CellBehavior* NormalCellBehavior::CreateClone() const
    {
        return new NormalCellBehavior();
    }

    constexpr bool NormalCellBehavior::HasState() const noexcept
    {
        return false;
    }
}

#endif //!CELLSIM_CELLS_NORMALCELLBEHAVIOR_HPP