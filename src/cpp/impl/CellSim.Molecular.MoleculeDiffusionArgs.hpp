#ifndef CELLSIM_MOLECULAR_MOLECULEDIFFUSIONARGS_HPP
#define CELLSIM_MOLECULAR_MOLECULEDIFFUSIONARGS_HPP

#include "base.hpp"
#include "CellSim.Containers.Span3.hpp"

namespace CellSim::Molecular
{
    struct MoleculeDiffusionArgs {
        Containers::Span3<double> Concentrations;

        constexpr MoleculeDiffusionArgs(Containers::Span3<double> span) noexcept;
    };
}

namespace CellSim::Molecular
{
    constexpr MoleculeDiffusionArgs::MoleculeDiffusionArgs(Containers::Span3<double> span) noexcept
        : Concentrations(span)
    {
    }
}

#endif //!CELLSIM_MOLECULAR_MOLECULEDIFFUSIONARGS_HPP