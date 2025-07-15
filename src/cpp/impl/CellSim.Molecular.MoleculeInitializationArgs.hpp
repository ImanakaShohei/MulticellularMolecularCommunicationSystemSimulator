#ifndef CELLSIM_MOLECULAR_MOLECULEINITIALIZATIONARGS_HPP
#define CELLSIM_MOLECULAR_MOLECULEINITIALIZATIONARGS_HPP

#include "base.hpp"
#include "CellSim.Containers.Span3.hpp"
#include "CellSim.Molecular.InitialMoleculeDistribution.hpp"

namespace CellSim::Molecular
{
    struct MoleculeInitializationArgs {
        /// @brief 分子の量
        double MoleculeAmount;

        /// @brief 
        Containers::Span3<double> Concentrations;

        /// @brief 境界条件
        InitialMoleculeDistribution DistributionType;

        /// @brief シード値
        uint32_t Seed;
        
        constexpr MoleculeInitializationArgs(
            Containers::Span3<double> concentrations,
            InitialMoleculeDistribution distributionType,
            double moleculeAmount,
            uint32_t seed
        ) noexcept;
    };
}

namespace CellSim::Molecular
{
    constexpr MoleculeInitializationArgs::MoleculeInitializationArgs(
        Containers::Span3<double> concentrations,
        InitialMoleculeDistribution distributionType,
        double moleculeAmount,
        uint32_t seed
    ) noexcept
        : MoleculeAmount(moleculeAmount)
        , Concentrations(concentrations)
        , DistributionType(distributionType)
        , Seed(seed)
    {
    }
}

#endif //!CELLSIM_MOLECULAR_MOLECULEINITIALIZATIONARGS_HPP