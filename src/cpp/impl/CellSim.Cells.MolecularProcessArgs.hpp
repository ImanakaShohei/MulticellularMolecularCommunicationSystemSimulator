#ifndef CELLSIM_CELLS_MOLECULARPROCESSARGS_HPP
#define CELLSIM_CELLS_MOLECULARPROCESSARGS_HPP

#include "base.hpp"
#include "CellSim.Molecular.MoleculeKind.hpp"
#include "CellSim.Numerics.Vector3T.hpp"

namespace CellSim::Cells
{
    struct MolecularProcessArgs {
        /// @brief 細胞外の分子の量
        double ExtracellularAmount;

        /// @brief 分子空間
        const Molecular::MoleculeField* Field;

        /// @brief 細胞内の分子の量
        double IntracellularAmount;

        /// @brief 分子の種類
        Molecular::MoleculeKind Kind;

        /// @brief 分子空間上の細胞の位置
        Numerics::GridPosition3 Position;

        constexpr MolecularProcessArgs(
            double extracellularAmount,
            const Molecular::MoleculeField* field,
            double intracellularAmount,
            Molecular::MoleculeKind kind,
            Numerics::GridPosition3 position
        ) noexcept;
    };
}

namespace CellSim::Cells
{
    constexpr MolecularProcessArgs::MolecularProcessArgs(
        double extracellularAmount,
        const Molecular::MoleculeField* field,
        double intracellularAmount,
        Molecular::MoleculeKind kind,
        Numerics::GridPosition3 position
    ) noexcept
        : ExtracellularAmount(extracellularAmount)
        , Field(field)
        , IntracellularAmount(intracellularAmount)
        , Kind(kind)
        , Position(position)
    {
    }
}

#endif //!CELLSIM_CELLS_MOLECULARPROCESSARGS_HPP