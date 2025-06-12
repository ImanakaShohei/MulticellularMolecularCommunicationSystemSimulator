#ifndef CELLSIM_MODEL_CELLGROWTHMODEL_HPP
#define CELLSIM_MODEL_CELLGROWTHMODEL_HPP

#include "base.hpp"
#include "CellSim.Model.CellSimulationModel.hpp"

namespace CellSim::Model
{
    class CellGrowthModel : public CellSimulationModel {
        private:

        double m_adhesiveRepulsionFactor;

        public:

        CellGrowthModel();

        CellGrowthModel(double adhesiveRepulsionFactor);

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
    constexpr bool CellGrowthModel::UseCellAlgorithm() const noexcept
    {
        return false;
    }
}

#endif //!CELLSIM_MODEL_CELLGROWTHMODEL_HPP