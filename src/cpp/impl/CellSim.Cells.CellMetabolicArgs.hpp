#ifndef CELLSIM_CELLS_CELLMETABOLICARGS_HPP
#define CELLSIM_CELLS_CELLMETABOLICARGS_HPP

#include "base.hpp"
#include "CellSim.Molecular.MoleculeInfo.hpp"

namespace CellSim::Cells
{
    struct CellMetabolicArgs {
        Molecular::MoleculeInfo MoleculeInfo;
    };
}

#endif //!CELLSIM_CELLS_CELLMETABOLICARGS_HPP