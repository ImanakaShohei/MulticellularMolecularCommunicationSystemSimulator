#ifndef CELLSIM_MODEL_NETWORKFORMATIONMODEL_HPP
#define CELLSIM_MODEL_NETWORKFORMATIONMODEL_HPP

#include "base.hpp"
#include "CellSim.Model.CellSimulationModel.hpp"
#include "CellSim.CellAlgorithms.CellList.hpp"

namespace CellSim::Model
{
    class NetworkFormationModel : public CellSimulationModel {
        private:

        double m_adhesiveRepulsionFactor;
        double m_attractionFactor;
        double m_lambda;
        double m_maxAttractionDistance;
        double m_maxRepulsionDistance;
        double m_minAttractionDistance;
        double m_remoteForceFactor;
        double m_reverseLambda;
        double m_squareMaxAttractionDistance;

        CellAlgorithms::CellList m_cellList;

        public:

        NetworkFormationModel();

        NetworkFormationModel(
            double adhesiveRepulsionFactor,
            double attractionFactor,
            double lambda,
            double maxAttractionDistance,
            double maxRepulsionDistance,
            double minAttractionDistance,
            double remoteForceFactor
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