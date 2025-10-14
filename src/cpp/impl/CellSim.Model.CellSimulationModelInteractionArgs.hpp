#ifndef CELLSIM_MODEL_CELLSIMULATIONMODELINTERACTIONARGS_HPP
#define CELLSIM_MODEL_CELLSIMULATIONMODELINTERACTIONARGS_HPP

#include "base.hpp"

#include <vector>

namespace CellSim::Model
{
    struct CellSimulationModelInteractionArgs {
        ::std::vector<Cells::Cell>* Cells;
        ::std::vector<Molecular::MoleculeField>* Fields;

        constexpr CellSimulationModelInteractionArgs(
            ::std::vector<Cells::Cell>* cells,
            ::std::vector<Molecular::MoleculeField>* fields
        ) noexcept;
    };
}

namespace CellSim::Model
{
    constexpr CellSimulationModelInteractionArgs::CellSimulationModelInteractionArgs(
        ::std::vector<Cells::Cell>* cells,
        ::std::vector<Molecular::MoleculeField>* fields
    ) noexcept
        : Cells(cells)
        , Fields(fields)
    {
    }
}

#endif //!CELLSIM_MODEL_CELLSIMULATIONMODELINTERACTIONARGS_HPP