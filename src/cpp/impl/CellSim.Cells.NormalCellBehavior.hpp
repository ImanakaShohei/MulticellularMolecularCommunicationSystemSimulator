#ifndef CELLSIM_CELLS_NORMALCELLBEHAVIOR_HPP
#define CELLSIM_CELLS_NORMALCELLBEHAVIOR_HPP

#include "base.hpp"
#include "CellSim.Cells.CellBehavior.hpp"

namespace CellSim::Cells
{
    class NormalCellBehavior : public CellBehavior {
        public:

        CellDivisionResult ComputeDivisionOutcome(const Cell* sender) override;
        CellGrowthResult ComputeGrowth(const Cell* sender) override;
        double ComputeMetabolicChange(const Cell* sender, CellMetabolicArgs args) override;
        double ComputeMoleculeEmitAmount(const Cell* sender, CellMoleculeEmissionArgs args) override;
        
        CellBehavior* CreateClone() const override;
        
        constexpr bool HasState() const noexcept override;
        Numerics::Vector3 OnSenseMolecules(const Cell* sender, CellMoleculeSensingArgs args) override;
        bool ShouldDivideThisStep(const Cell* sender) noexcept override;
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