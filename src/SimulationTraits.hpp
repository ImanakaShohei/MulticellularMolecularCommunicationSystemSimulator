#include "core/base.hpp"
#include "SimulationType.hpp"

template <SimulationType SType>
struct SimulationTraits final {
    static_assert(false, "SimulationTraits<SimulationType>: 不正な特殊化です");
};

template <>
struct SimulationTraits<SimulationType::ClusterFormation> final {
    using CellType = NormalCell;
    using Model = ClusterFormationModel;
};

template <>
struct SimulationTraits<SimulationType::MassGrowth> final {
    using CellType = NormalCell;
    using Model = MassGrowthModel;
};

template <>
struct SimulationTraits<SimulationType::MassRotation> final {
    using CellType = NormalCell;
    using Model = MassGrowthModel;
};

template <>
struct SimulationTraits<SimulationType::NetworkFormation> final {
    using CellType = NormalCell;
    using Model = NetworkFormationModel;
};

template <>
struct SimulationTraits<SimulationType::UserSimulation> final {
    using CellType = UserCell;
    using Model = UserSimulationModel;
};