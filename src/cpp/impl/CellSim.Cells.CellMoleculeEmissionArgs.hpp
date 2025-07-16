#ifndef CELLSIM_CELLS_CELLMOLECULEEMISSIONARGS_HPP
#define CELLSIM_CELLS_CELLMOLECULEEMISSIONARGS_HPP

#include "base.hpp"
#include "CellSim.Numerics.Vector3T.hpp"

namespace CellSim::Cells
{
    struct CellMoleculeEmissionArgs {
        const Molecular::MoleculeField* Field;
        Numerics::GridPosition3 Position;

        constexpr CellMoleculeEmissionArgs(
            const Molecular::MoleculeField* field,
            Numerics::GridPosition3 position
        ) noexcept;
    };
}

namespace CellSim::Cells
{
        constexpr CellMoleculeEmissionArgs::CellMoleculeEmissionArgs(
            const Molecular::MoleculeField* field,
            Numerics::GridPosition3 position
        ) noexcept
            : Field(field)
            , Position(position)
        {
        }
}

#endif //!CELLSIM_CELLS_CELLMOLECULEEMISSIONARGS_HPP