#ifndef CELLSIM_CELLALGORITHMS_CELLALGORITHMINTERACTIONARGS_HPP
#define CELLSIM_CELLALGORITHMS_CELLALGORITHMINTERACTIONARGS_HPP

#include "base.hpp"

#include <vector>

namespace CellSim::CellAlgorithms
{
    struct CellAlgorithmInteractionArgs {
        ::std::vector<Cells::Cell>* Cells;
        ::std::vector<Molecular::MoleculeField>* MoleculeFields;
        const Model::CellSimulationModel* SimulationModel;

        constexpr CellAlgorithmInteractionArgs(
            ::std::vector<Cells::Cell>* cells,
            ::std::vector<Molecular::MoleculeField>* moleculeFields,
            const Model::CellSimulationModel* simulationModel
        ) noexcept;
    };
}

namespace CellSim::CellAlgorithms
{
    constexpr CellAlgorithmInteractionArgs::CellAlgorithmInteractionArgs(
        ::std::vector<Cells::Cell>* cells,
        ::std::vector<Molecular::MoleculeField>* moleculeFields,
        const Model::CellSimulationModel* simulationModel
    ) noexcept
        : Cells(cells)
        , MoleculeFields(moleculeFields)
        , SimulationModel(simulationModel)
    {
    }
}

#endif //!CELLSIM_CELLALGORITHMS_CELLALGORITHMINTERACTIONARGS_HPP