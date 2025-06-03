#ifndef CELLSIM_MODEL_SIMULATIONTYPE_HPP
#define CELLSIM_MODEL_SIMULATIONTYPE_HPP

#include "base.hpp"

namespace CellSim::Model
{
    /// @brief モデルの種類
    enum class CellSimulationType {
        CellGrowth,
        ClusterFormation,
        ClusterRotation,
        ClusterSprouting,
        NetworkFormation,
        Null,
        User,
        WavePropagation,
    };
}

#endif //!CELLSIM_MODEL_SIMULATIONTYPE_HPP