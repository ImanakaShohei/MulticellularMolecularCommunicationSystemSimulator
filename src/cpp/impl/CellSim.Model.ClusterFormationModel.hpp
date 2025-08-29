#ifndef CELLSIM_MODEL_CLUSTERFORMATIONMODEL_HPP
#define CELLSIM_MODEL_CLUSTERFORMATIONMODEL_HPP

#include "base.hpp"
#include "CellSim.Model.CellSimulationModel.hpp"

namespace CellSim::Model
{
    class ClusterFormationModel : public CellSimulationModel {
        private:

        /// @brief 遠隔力を計算
        /// @param target ターゲットの細胞
        /// @param cell 
        /// @return 計算結果
        [[nodiscard]] Numerics::Vector3 m_computeRemoteForce(
            Numerics::Vector3 diff,
            double dist,
            double targetMass,
            double cellMass,
            double reverseLambda
        ) const noexcept;

        /// @brief くっついた細胞同士の反発力
        /// @param target ターゲットの細胞
        /// @param cell 
        /// @return 計算結果
        [[nodiscard]] Numerics::Vector3 m_computeVolumeExclusion(
            Numerics::Vector3 diff,
            double dist,
            double targetRadius,
            double cellRadius
        ) const noexcept;

        public:

        class Params : public CellSimulationModel::Params {
            public:

            [[nodiscard]] static Params* FromJson(::nlohmann::json const& j);

            double AdhesiveRepulsionFactor;
            double Lambda;
            double ReverseLambda; // 1/Lambda
            double RemoteForceFactor;

            Params();
            Params(
                double adhesiveRepulsionFactor,
                double lambda,
                double remoteForceFactor
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
    constexpr bool ClusterFormationModel::UseCellAlgorithm() const noexcept
    {
        return true;
    }
}

#endif //!CELLSIM_MODEL_CLUSTERFORMATIONMODEL_HPP