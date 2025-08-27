#ifndef CELLSIM_MODEL_CLUSTERROTATIONMODEL_HPP
#define CELLSIM_MODEL_CLUSTERROTATIONMODEL_HPP

#include "base.hpp"
#include "CellSim.Model.CellSimulationModel.hpp"

namespace CellSim::Model
{
    /// @brief クラスタ回転モデル
    class ClusterRotationModel : public CellSimulationModel {
        public:

        class Params : public CellSimulationModel::Params {
            public:
            double AdhesionDistanceThreshold; // 細胞同士がこの値より近いと接着力が働く
            double AdhesionForceFactor; // 接着力にかける係数
            double CentralForceFactor; // 中心力にかける係数
            double RepulsionFactor; // 反発力の係数
            double RepulsionMaxDistance; // 細胞同士がこの値より近いと反発する

            Params(
                double adhesionDistanceThreshold,
                double adhesionForceFactor,
                double centralForceFactor,
                double repulsionFactor,
                double repulsionMaxDistance
            );
        };

        void BeforeAdvanceStep(
            const Simulation* sender,
            SimulationModelStepArgs args
        ) override;

        Numerics::Vector3 ComputeForceOnCell(
            const Simulation* sender,
            SimulationModelForceComputationArgs args
        ) const override;

        void OnAdvanceStep(
            const Simulation* sender,
            SimulationModelStepArgs args
        ) override;

        constexpr bool UseCellAlgorithm() const noexcept override;
    };
}

namespace CellSim::Model
{
    constexpr bool ClusterRotationModel::UseCellAlgorithm() const noexcept
    {
        return true;
    }
}

#endif //!CELLSIM_MODEL_CLUSTERROTATIONMODEL_HPP