#ifndef CELLSIM_MOLECULAR_MOLECULEINITIALIZATIONARGS_HPP
#define CELLSIM_MOLECULAR_MOLECULEINITIALIZATIONARGS_HPP

#include "base.hpp"
#include "CellSim.Containers.Span3.hpp"
#include "CellSim.Molecular.InitialMoleculeDistribution.hpp"

namespace CellSim::Molecular
{
    struct MoleculeInitializationArgs {
        Containers::Span3<double> Concentrations;
        InitialMoleculeDistribution DistributionType;

        constexpr MoleculeInitializationArgs(
            Containers::Span3<double> concentrations,
            InitialMoleculeDistribution distributionType
        ) noexcept;
    };
}

namespace CellSim::Molecular
{
    constexpr MoleculeInitializationArgs::MoleculeInitializationArgs(
        Containers::Span3<double> concentrations,
        InitialMoleculeDistribution distributionType
    ) noexcept
        : Concentrations(concentrations)
        , DistributionType(distributionType)
    {
    }
}

#endif //!CELLSIM_MOLECULAR_MOLECULEINITIALIZATIONARGS_HPP