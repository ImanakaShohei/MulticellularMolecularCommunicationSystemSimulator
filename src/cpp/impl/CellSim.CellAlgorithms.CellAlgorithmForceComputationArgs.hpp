#ifndef CELLSIM_CELLALGORITHMS_CELLALGORITHMFORCECOMPUTATIONARGS_HPP
#define CELLSIM_CELLALGORITHMS_CELLALGORITHMFORCECOMPUTATIONARGS_HPP

#include "base.hpp"

#include <vector>

namespace CellSim::CellAlgorithms
{
    struct CellAlgorithmForceComputationArgs {
        const ::std::vector<Cells::Cell>* Cells;
        const ::std::vector<Molecular::MoleculeField>* Fields;
        const Cells::Cell* Target;

        constexpr CellAlgorithmForceComputationArgs(
            const Cells::Cell* target,
            const ::std::vector<Cells::Cell>* cells,
            const ::std::vector<Molecular::MoleculeField>* fields
        ) noexcept;
    };
}

namespace CellSim::CellAlgorithms
{
    constexpr CellAlgorithmForceComputationArgs::CellAlgorithmForceComputationArgs(
        const Cells::Cell* target,
            const ::std::vector<Cells::Cell>* cells,
            const ::std::vector<Molecular::MoleculeField>* fields
    ) noexcept
        : Cells(cells)
        , Fields(fields)
        , Target(target)
    {
    }
}

#endif //!CELLSIM_CELLALGORITHMS_CELLALGORITHMFORCECOMPUTATIONARGS_HPP