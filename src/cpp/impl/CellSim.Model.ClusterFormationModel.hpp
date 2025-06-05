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
            Cells::CellInfo target,
            Cells::CellInfo cell
        ) const noexcept;

        /// @brief くっついた細胞同士の反発力
        /// @param target ターゲットの細胞
        /// @param cell 
        /// @return 計算結果
        [[nodiscard]] Numerics::Vector3 m_computeVolumeExclusion(
            Cells::CellInfo target,
            Cells::CellInfo cell
        ) const noexcept;

        double m_adhesiveRepulsionFactor;
        double m_lambda;
        double m_reverseLambda;
        double m_remoteForceFactor;

        public:

        ClusterFormationModel();
        ClusterFormationModel(
            double adhesiveRepulsionFactor,
            double lambda,
            double remoteForceFactor
        );

        void BeforeAdvanceStep(
            ::std::vector<Cells::Cell>& cells,
            ::std::vector<Molecular::MoleculeDiffusion> const& molecules
        ) override;

        Numerics::Vector3 ComputeForceOnCell(
            Cells::Cell const& target,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Molecular::MoleculeDiffusion> const& moleculeSpaces,
            const CellAlgorithms::CellAlgorithm* pCellAlgorithm
        ) const override;

        void OnAdvanceStep(
            ::std::vector<Cells::Cell>& cells,
            ::std::vector<Molecular::MoleculeDiffusion> const& molecules
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