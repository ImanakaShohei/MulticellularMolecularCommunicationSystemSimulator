#ifndef CELLSIM_CELLS_CELLMOLECULESENSINGARGS_HPP
#define CELLSIM_CELLS_CELLMOLECULESENSINGARGS_HPP

#include "base.hpp"

namespace CellSim::Cells
{
    struct CellMoleculeSensingArgs {
        const Molecular::MoleculeField* Field;

        constexpr CellMoleculeSensingArgs(
            const Molecular::MoleculeField* field
        ) noexcept;
    };
}

namespace CellSim::Cells
{
    constexpr CellMoleculeSensingArgs::CellMoleculeSensingArgs(
        const Molecular::MoleculeField* field
    ) noexcept
        : Field(field)
    {
    }
}

#endif //!CELLSIM_CELLS_CELLMOLECULESENSINGARGS_HPP