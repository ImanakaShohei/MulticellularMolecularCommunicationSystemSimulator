#ifndef CELLSIM_MODEL_CLUSTERSPROUTINGMODEL_HPP
#define CELLSIM_MODEL_CLUSTERSPROUTINGMODEL_HPP

#include "base.hpp"
#include "CellSim.Model.CellSimulationModel.hpp"

namespace CellSim::Model
{
    /// @brief クラスタスプラウトモデル
    class ClusterSproutingModel : public CellSimulationModel {
        private:
    
        size_t m_adhesionThreshold; //接着している細胞の数がこの値以下の時に反発力が働く
        double m_coefficientCd; //反発力にかける係数
        double m_contactDistance; //細胞同士がこの値より近づくと反発力が発生
        double m_followerAttractionFactor; //接着している細胞の数がadhesion_thresholdより多い時に受ける引力にかける係数
        double m_globalAttractionFactor; //すべての細胞間にかかる力の係数
        double m_lambda; //力の届く範囲を決める値
        double m_leaderRepulsionFactor; //接着している細胞の数がadhesion_thresholdの時に受ける反発力にかける係数
        double m_leaderRepulsionMaxDistance; //リーダーに届く反発力の最大距離
        double m_leaderRepulsionMinDistance; //リーダーに届く反発力の最小距離
        double m_leaderRepulsionRange; // m_leaderRepulsionMaxDistance - m_leaderRepulsionMinDistance
        double m_squareContactDistance; //

        public:

        ClusterSproutingModel();

        ClusterSproutingModel(
            size_t adhesionThreshold,
            double coefficientCd,
            double contactDistance,
            double followerAttractionFactor,
            double globalAttractionFactor,
            double lambda,
            double leaderRepulsionFactor,
            double leaderRepulsionMaxDistance,
            double leaderRepulsionMinDistance
        );

        void BeforeAdvanceStep(
            ::std::vector<Cells::Cell>& cells,
            ::std::vector<Molecular::MoleculeField> const& molecules
        ) override;

        Numerics::Vector3 ComputeForceOnCell(
            Cells::Cell const& target,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Molecular::MoleculeField> const& moleculeSpaces,
            const CellAlgorithms::CellAlgorithm* pCellAlgorithm
        ) const override;

        void OnAdvanceStep(
            ::std::vector<Cells::Cell>& cells,
            ::std::vector<Molecular::MoleculeField> const& molecules
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