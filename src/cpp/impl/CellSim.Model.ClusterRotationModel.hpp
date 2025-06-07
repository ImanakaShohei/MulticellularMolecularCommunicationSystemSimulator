#ifndef CELLSIM_MODEL_CLUSTERROTATIONMODEL_HPP
#define CELLSIM_MODEL_CLUSTERROTATIONMODEL_HPP

#include "base.hpp"
#include "CellSim.Model.CellSimulationModel.hpp"

namespace CellSim::Model
{
    /// @brief クラスタ回転モデル
    class ClusterRotationModel : public CellSimulationModel {
        private:

        double m_adhesionDistanceThreshold; // 細胞同士がこの値より近いと接着力が働く
        double m_adhesionForceFactor; // 接着力にかける係数
        double m_centralForceFactor; // 中心力にかける係数
        double m_repulsionFactor; // 反発力の係数
        double m_repulsionMaxDistance; // 細胞同士がこの値より近いと反発する

        public:

        ClusterRotationModel();
        ClusterRotationModel(
            double adhesionDistanceThreshold,
            double adhesionForceFactor,
            double centralForceFactor,
            double repulsionFactor,
            double repulsionMaxDistance
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
    constexpr bool ClusterRotationModel::UseCellAlgorithm() const noexcept
    {
        return true;
    }
}

#endif //!CELLSIM_MODEL_CLUSTERROTATIONMODEL_HPP