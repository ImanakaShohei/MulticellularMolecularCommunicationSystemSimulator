#ifndef CELLSIM_CELLS_NORMALCELLBEHAVIOR_HPP
#define CELLSIM_CELLS_NORMALCELLBEHAVIOR_HPP

#include "base.hpp"
#include "CellSim.Cells.CellBehavior.hpp"

namespace CellSim::Cells
{
    class NormalCellBehavior : public CellBehavior {
        private:
        /// @brief 細胞の半径がこの値を超えると分裂する
        double m_cellDivisionRadius;

        public:

        NormalCellBehavior();

        NormalCellBehavior(double cellDivisionRadius);

        CellDivisionResult ComputeDivisionOutcome(const Cell* sender) override;
        CellGrowthResult ComputeGrowth(const Cell* sender) override;
        MolecularProcessResult ComputeMolecularProcess(const Cell* sender, MolecularProcessArgs args) override;
        
        CellBehavior* CreateClone() const override;
        
        constexpr bool IsReusable() const noexcept override;
        Numerics::Vector3 OnSenseMolecules(const Cell* sender, CellMoleculeSensingArgs args) override;
        bool ShouldDivideThisStep(const Cell* sender) noexcept override;
    };
}

namespace CellSim::Cells
{
    inline CellBehavior* NormalCellBehavior::CreateClone() const
    {
        return new NormalCellBehavior(*this);
    }

    constexpr bool NormalCellBehavior::IsReusable() const noexcept
    {
        return true;
    }
}

#endif //!CELLSIM_CELLS_NORMALCELLBEHAVIOR_HPP