#ifndef CELLSIM_MODEL_NETWORKFORMATIONMODEL_HPP
#define CELLSIM_MODEL_NETWORKFORMATIONMODEL_HPP

#include "base.hpp"
#include "CellSim.Model.CellSimulationModel.hpp"
#include "CellSim.CellAlgorithms.CellList.hpp"

namespace CellSim::Model
{
    class NetworkFormationModel : public CellSimulationModel {
        private:
        double m_maxAttractionDistance; //引力が届く最大距離
        double m_squareMaxAttractionDistance;

        CellAlgorithms::CellList m_cellList;

        public:

        class Params : public CellSimulationModel::Params {
            public:
            double AdhesiveRepulsionFactor; //接着している細胞間に働く反発力にかける係数
            double AttractionFactor; //接着している細胞間に働く引力にかける係数
            double Lambda; //力の届く範囲を決める値
            double MaxRepulsionDistance; //反発力が届く最大距離
            double MinAttractionDistance; //引力が働き始める最小距離
            double RemoteForceFactor; //すべての細胞間にかかる力の係数
            double ReverseLambda; //1.0 / Lambda

            Params(
                double adhesiveRepulsionFactor,
                double attractionFactor,
                double lambda,
                double maxRepulsionDistance,
                double minAttractionDistance,
                double remoteForceFactor
            );
        };

        NetworkFormationModel();

        NetworkFormationModel(
            double maxAttractionDistance
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
    constexpr bool NetworkFormationModel::UseCellAlgorithm() const noexcept
    {
        return true;
    }
}

#endif //!CELLSIM_MODEL_NETWORKFORMATIONMODEL_HPP