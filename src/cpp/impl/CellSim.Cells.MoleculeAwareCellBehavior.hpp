#ifndef CELLSIM_CELLS_MOLECULEAWARECELLBEHAVIOR_HPP
#define CELLSIM_CELLS_MOLECULEAWARECELLBEHAVIOR_HPP

#include "base.hpp"
#include "CellSim.Cells.NormalCellBehavior.hpp"

namespace CellSim::Cells
{
    /// @brief 分子の影響を考慮したクラス
    class MoleculeAwareCellBehavior : public NormalCellBehavior {
        private:

        /// @brief 細胞の半径がこの値を超えると分裂する
        double m_cellDivisionRadius;

        /// @brief 生成係数 k1
        double m_synthesisRate;

        /// @brief 分解係数 k2
        double m_degradationRate;

        public:

        MoleculeAwareCellBehavior();

        MoleculeAwareCellBehavior(
            double cellDivisionRadius,
            double synthesisRate,
            double degradationRate
        );

        double ComputeMetabolicChange(const Cell* sender, CellMetabolicArgs args) override;
        CellBehavior* CreateClone() const override;
        constexpr bool HasState() const noexcept override;
        Numerics::Vector3 OnSenseMolecules(const Cell* sender, CellMoleculeSensingArgs args) override;
        bool ShouldDivideThisStep(const Cell* sender) noexcept override;
    };
}

namespace CellSim::Cells
{
    inline CellBehavior* MoleculeAwareCellBehavior::CreateClone() const
    {
        return new MoleculeAwareCellBehavior(*this);
    }

    constexpr bool MoleculeAwareCellBehavior::HasState() const noexcept
    {
        return true;
    }
}

#endif //!CELLSIM_CELLS_MOLECULEAWARECELLBEHAVIOR_HPP