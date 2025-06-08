#include "CellSim.Model.CellGrowthModel.hpp"
#include "CellSim.Model.SimulationModelForceComputationArgs.hpp"
#include "CellSim.Model.SimulationModelStepArgs.hpp"
#include "CellSim.Numerics.Vector3T.hpp"

namespace CellSim::Model
{
    void CellGrowthModel::BeforeAdvanceStep(
        [[maybe_unused]] const Simulation* sender,
        [[maybe_unused]] SimulationModelStepArgs args
    )
    {
        // TODO: ここに処理を追加します
    }

    Numerics::Vector3 CellGrowthModel::ComputeForceOnCell(
        [[maybe_unused]] const Simulation* sender,
        [[maybe_unused]] SimulationModelForceComputationArgs args
    ) const
    {
        // TODO: ここに処理を追加します

        return Numerics::Vector3();
    }

    void CellGrowthModel::InitializeCells(
        [[maybe_unused]] const Simulation* sender,
        [[maybe_unused]] ::std::vector<Cells::Cell>& cells
    )
    {
        // TODO: ここに処理を追加します
    }

    void CellGrowthModel::OnAdvanceStep(
        [[maybe_unused]] const Simulation* sender,
        [[maybe_unused]] SimulationModelStepArgs args
    )
    {
        // TODO: ここに処理を追加します
    }
}