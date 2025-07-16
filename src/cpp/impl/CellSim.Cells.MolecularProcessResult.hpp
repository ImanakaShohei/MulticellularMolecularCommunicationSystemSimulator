#ifndef CELLSIM_CELLS_MOLECULARPROCESSRESULT_HPP
#define CELLSIM_CELLS_MOLECULARPROCESSRESULT_HPP

#include "base.hpp"

namespace CellSim::Cells
{
    struct MolecularProcessResult {
        /// @brief 細胞外の分子の変化量
        double ExtracellularChange;

        /// @brief 細胞内の分子の変化量
        double IntracellularChange;

        MolecularProcessResult() = default;

        constexpr MolecularProcessResult(
            double extracellularChange,
            double intracellularChange
        ) noexcept;
    };
}

namespace CellSim::Cells
{
    constexpr MolecularProcessResult::MolecularProcessResult(
        double extracellularChange,
        double intracellularChange
    ) noexcept
        : ExtracellularChange(extracellularChange)
        , IntracellularChange(intracellularChange)
    {
    }
}

#endif // !CELLSIM_CELLS_MOLECULARPROCESSRESULT_HPP