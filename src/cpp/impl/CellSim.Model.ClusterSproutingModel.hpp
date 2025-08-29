#ifndef CELLSIM_MODEL_CLUSTERSPROUTINGMODEL_HPP
#define CELLSIM_MODEL_CLUSTERSPROUTINGMODEL_HPP

#include "base.hpp"
#include "CellSim.Model.CellSimulationModel.hpp"

namespace CellSim::Model
{
    /// @brief クラスタスプラウトモデル
    class ClusterSproutingModel : public CellSimulationModel {
        private:
        double m_contactDistance; //細胞同士がこの値より近づくと反発力が発生
        double m_squareContactDistance;
        public:

        class Params : public CellSimulationModel::Params {
            public:

            [[nodiscard]] static Params* FromJson(::nlohmann::json const& j);
            
            size_t AdhesionThreshold; //接着している細胞の数がこの値以下の時に反発力が働く
            double CoefficientCd; //反発力にかける係数
            double FollowerAttractionFactor; //接着している細胞の数がadhesion_thresholdより多い時に受ける引力にかける係数
            double GlobalAttractionFactor; //すべての細胞間にかかる力の係数
            double Lambda; //力の届く範囲を決める値
            double LeaderRepulsionFactor; //接着している細胞の数がadhesion_thresholdの時に受ける反発力にかける係数
            double LeaderRepulsionMaxDistance; //リーダーに届く反発力の最大距離
            double LeaderRepulsionMinDistance; //リーダーに届く反発力の最小距離
            double LeaderRepulsionRange; // LeaderRepulsionMaxDistance - LeaderRepulsionMinDistance

            Params(
                size_t adhesionThreshold,
                double coefficientCd,
                double followerAttractionFactor,
                double globalAttractionFactor,
                double lambda,
                double leaderRepulsionFactor,
                double leaderRepulsionMaxDistance,
                double leaderRepulsionMinDistance
            );
        };

        ClusterSproutingModel();
        ClusterSproutingModel(
            double contactDistance
        );

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
    constexpr bool ClusterSproutingModel::UseCellAlgorithm() const noexcept
    {
        return false;
    }
}

#endif //!CELLSIM_MODEL_CLUSTERSPROUTINGMODEL_HPP