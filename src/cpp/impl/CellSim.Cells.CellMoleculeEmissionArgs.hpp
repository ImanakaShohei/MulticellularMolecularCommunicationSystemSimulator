#ifndef CELLSIM_CELLS_CELLMOLECULEEMISSIONARGS_HPP
#define CELLSIM_CELLS_CELLMOLECULEEMISSIONARGS_HPP

#include "base.hpp"

namespace CellSim::Cells
{
    struct CellMoleculeEmissionArgs {
        const Molecular::MoleculeField* Field;
    };
}

#endif //!CELLSIM_CELLS_CELLMOLECULEEMISSIONARGS_HPP