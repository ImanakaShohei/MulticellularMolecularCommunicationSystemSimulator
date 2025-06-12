#ifndef CELLSIM_MOLECULE_MOLECULEDIFFUSIONBEAVIORKIND_HPP
#define CELLSIM_MOLECULE_MOLECULEDIFFUSIONBEAVIORKIND_HPP

#include "base.hpp"

namespace CellSim::Molecular
{
    enum class MoleculeBehaviorKind {
        Normal,
        Null,
        User
    };
}

#endif //!CELLSIM_MOLECULE_MOLECULEDIFFUSIONBEAVIORKIND_HPP