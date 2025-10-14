#ifndef CELLSIM_MODEL_NULLMODEL_HPP
#define CELLSIM_MODEL_NULLMODEL_HPP

#include "base.hpp"
#include "CellSim.Model.CellSimulationModel.hpp"
#include "CellSim.Model.CellSimulationModelInteractionArgs.hpp"
#include "CellSim.Model.SimulationModelForceComputationArgs.hpp"
#include "CellSim.Model.SimulationModelStepArgs.hpp"
#include "CellSim.Numerics.Vector3T.hpp"

namespace CellSim::Model
{
    /// @brief 何もしない力学モデル
    class NullModel : public CellSimulationModel {
        public:

        class Params : public CellSimulationModel::Params {
            public:
        };

        constexpr void ApplyInteraction(
            const Simulation* sender,
            CellSimulationModelInteractionArgs args
        ) noexcept;

        constexpr void BeforeAdvanceStep(
            const Simulation* sender,
            SimulationModelStepArgs args
        ) override;

        constexpr Numerics::Vector3 ComputeForceOnCell(
            const Simulation* sender,
            SimulationModelForceComputationArgs args
        ) const override;

        constexpr void InitializeCells(
            const Simulation* sender,
            ::std::vector<Cells::Cell>& cells
        ) override;

        constexpr void OnAdvanceStep(
            const Simulation* sender,
            SimulationModelStepArgs args
        ) override;

        constexpr bool OverrideInteraction() const noexcept override;

        constexpr bool UseCellAlgorithm() const noexcept override;
    };
}

namespace CellSim::Model
{
    constexpr void NullModel::ApplyInteraction(
        const Simulation*,
        CellSimulationModelInteractionArgs
    ) noexcept
    {
    }

    constexpr void NullModel::BeforeAdvanceStep(
        const Simulation*,
        SimulationModelStepArgs
    )
    {
    }

    constexpr Numerics::Vector3 NullModel::ComputeForceOnCell(
        const Simulation*,
        SimulationModelForceComputationArgs
    ) const
    {
        return Numerics::Vector3();
    }

    constexpr void NullModel::InitializeCells(
        const Simulation*,
        ::std::vector<Cells::Cell>&
    )
    {
    }

    constexpr void NullModel::OnAdvanceStep(
        const Simulation*,
        SimulationModelStepArgs
    )
    {
    }

    constexpr bool NullModel::OverrideInteraction() const noexcept
    {
        return true;
    }

    constexpr bool NullModel::UseCellAlgorithm() const noexcept
    {
        return false;
    }
}

#endif //!CELLSIM_MODEL_NULLMODEL_HPP