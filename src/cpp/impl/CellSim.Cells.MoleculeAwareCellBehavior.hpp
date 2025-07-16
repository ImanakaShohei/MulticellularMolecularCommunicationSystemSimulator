#ifndef CELLSIM_CELLS_MOLECULEAWARECELLBEHAVIOR_HPP
#define CELLSIM_CELLS_MOLECULEAWARECELLBEHAVIOR_HPP

#include "base.hpp"
#include "CellSim.Cells.NormalCellBehavior.hpp"

namespace CellSim::Cells
{
    /// @brief 分子の影響を考慮したクラス
    class MoleculeAwareCellBehavior : public NormalCellBehavior {
        private:

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

        MolecularProcessResult ComputeMolecularProcess(const Cell* sender, MolecularProcessArgs args) override;
        CellBehavior* CreateClone() const override;
        constexpr bool IsReusable() const noexcept override;
        Numerics::Vector3 OnSenseMolecules(const Cell* sender, CellMoleculeSensingArgs args) override;
    };
}

namespace CellSim::Cells
{
    inline CellBehavior* MoleculeAwareCellBehavior::CreateClone() const
    {
        return new MoleculeAwareCellBehavior(*this);
    }

    constexpr bool MoleculeAwareCellBehavior::IsReusable() const noexcept
    {
        return true;
    }
}

#endif //!CELLSIM_CELLS_MOLECULEAWARECELLBEHAVIOR_HPP