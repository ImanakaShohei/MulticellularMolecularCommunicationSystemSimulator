#ifndef CELLSIM_CELLALGORITHMS_CELLALGORITHMTYPE_HPP
#define CELLSIM_CELLALGORITHMS_CELLALGORITHMTYPE_HPP

#include "base.hpp"

namespace CellSim::CellAlgorithms
{
    /// @brief CellAlgorithmの種類
    enum class CellAlgorithmType {
        BarnesHut,
        CellList,
        Naive,
        Null,
        ParticleMesh,
        User,
    };
}

#endif //!CELLSIM_CELLALGORITHMS_CELLALGORITHMTYPE_HPP