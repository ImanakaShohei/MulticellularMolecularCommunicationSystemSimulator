#ifndef CELLSIM_MOLECULAR_MOLECULECREATEINFO_HPP
#define CELLSIM_MOLECULAR_MOLECULECREATEINFO_HPP

#include "base.hpp"
#include "CellSim.Molecular.BoundaryCondition.hpp"
#include "CellSim.Molecular.InitialMoleculeDistribution.hpp"
#include "CellSim.Molecular.MoleculeBehavior.hpp"
#include "CellSim.Molecular.MoleculeKind.hpp"
#include <memory>

namespace CellSim::Molecular
{
    struct MoleculeCreateInfo {
        ::std::unique_ptr<MoleculeBehavior> Behavior;
        size_t GridCount;
        double MoleculeAmount;
        MoleculeKind Kind;
        ::CellSim::Molecular::BoundaryCondition BoundaryCondition;
        InitialMoleculeDistribution InitialDistribution;
    };
}

#endif //!CELLSIM_MOLECULAR_MOLECULECREATEINFO_HPP