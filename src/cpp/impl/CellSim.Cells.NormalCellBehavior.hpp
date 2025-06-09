#ifndef CELLSIM_CELLS_NORMALCELLBEHAVIOR_HPP
#define CELLSIM_CELLS_NORMALCELLBEHAVIOR_HPP

#include "base.hpp"
#include "CellSim.Cells.CellBehavior.hpp"

namespace CellSim::Cells
{
    class NormalCellBehavior : public CellBehavior {
        public:

        CellDivisionResult ComputeDivisionOutcome(const Cell* sender) override;
        CellGrowthResult ComputeGrowth(Cell const& cell) override;
        double ComputeMetabolicChange(const Cell* sender, Molecular::MoleculeInfo args) override;
        double ComputeMoleculeEmitAmount(Cell const& cell, Molecular::MoleculeField const& field) override;
        
        CellBehavior* CreateClone() const override;
        
        constexpr bool HasState() const noexcept override;
        bool ShouldDivideThisStep() noexcept override;
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