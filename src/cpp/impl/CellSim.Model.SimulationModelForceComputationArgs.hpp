#ifndef CELLSIM_MODEL_SIMULATIONMODELFORCECOMPUTATIONARGS_HPP
#define CELLSIM_MODEL_SIMULATIONMODELFORCECOMPUTATIONARGS_HPP

#include "base.hpp"

#include <vector>

namespace CellSim::Model
{
    struct SimulationModelForceComputationArgs {
        const ::std::vector<Cells::Cell>* AffectedCells;
        const CellAlgorithms::CellAlgorithm* CellAlgorithm;
        const ::std::vector<Cells::Cell>* Cells;
        const ::std::vector<Molecular::MoleculeField>* Fields;
        const Cells::Cell* Target;

        constexpr SimulationModelForceComputationArgs(
            const Cells::Cell* target,
            const ::std::vector<Cells::Cell>* cells,
            const ::std::vector<Cells::Cell>* affectedCells,
            const ::std::vector<Molecular::MoleculeField>* fields,
            const CellAlgorithms::CellAlgorithm* cellAlgorithm
        ) noexcept;
    };
}

namespace CellSim::Model
{
    constexpr SimulationModelForceComputationArgs::SimulationModelForceComputationArgs(
        const Cells::Cell* target,
        const ::std::vector<Cells::Cell>* cells,
        const ::std::vector<Cells::Cell>* affectedCells,
        const ::std::vector<Molecular::MoleculeField>* fields,
        const CellAlgorithms::CellAlgorithm* cellAlgorithm
    ) noexcept
        : AffectedCells(affectedCells)
        , CellAlgorithm(cellAlgorithm)
        , Cells(cells)
        , Fields(fields)
        , Target(target)
    {
    }
}

#endif //!CELLSIM_MODEL_SIMULATIONMODELFORCECOMPUTATIONARGS_HPP