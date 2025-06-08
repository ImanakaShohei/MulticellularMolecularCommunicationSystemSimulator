#ifndef CELLSIM_MOLECULE_MOLECULEINFO_HPP
#define CELLSIM_MOLECULE_MOLECULEINFO_HPP

#include "base.hpp"
#include "CellSim.Molecular.MoleculeKind.hpp"

namespace CellSim::Molecular
{
    struct MoleculeInfo {
        double Amount;
        MoleculeKind Kind;

        constexpr MoleculeInfo(double amount, MoleculeKind kind) noexcept;
    };
}

namespace CellSim::Molecular
{
    constexpr MoleculeInfo::MoleculeInfo(double amount, MoleculeKind kind) noexcept
        : Amount(amount)
        , Kind(kind)
    {
    }
}

#endif //!CELLSIM_MOLECULE_MOLECULEINFO_HPP