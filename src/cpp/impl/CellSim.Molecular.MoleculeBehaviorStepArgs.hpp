#ifndef CELLSIM_MOLECULAR_MOLECULEBEHAVIORSTEPARGS_HPP
#define CELLSIM_MOLECULAR_MOLECULEBEHAVIORSTEPARGS_HPP

#include "base.hpp"

#include <vector>

namespace CellSim::Molecular
{
    struct MoleculeBehaviorStepArgs {
        const ::std::vector<Cells::Cell>* Cells;

        constexpr MoleculeBehaviorStepArgs(const ::std::vector<Cells::Cell>* cells) noexcept;
    };
}

namespace CellSim::Molecular
{
    constexpr MoleculeBehaviorStepArgs::MoleculeBehaviorStepArgs(const ::std::vector<Cells::Cell>* cells) noexcept
        : Cells(cells)
    {
    }
}

#endif //!CELLSIM_MOLECULAR_MOLECULEBEHAVIORSTEPARGS_HPP