#include "CellSim.Model.CellGrowthModel.hpp"
#include "CellSim.Model.SimulationModelForceComputationArgs.hpp"
#include "CellSim.Model.SimulationModelStepArgs.hpp"
#include "CellSim.Numerics.Vector3T.hpp"
#include "CellSim.Messages.hpp"
#include "CellSim.Settings.Config.SimulationModel.CellGrowth.hpp"
#include "CellSim.Cells.CellInfo.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmAffectableCellQueryArgs.hpp"

#include <stdexcept>

namespace CellSim::Model
{
    CellGrowthModel::CellGrowthModel()
        : CellGrowthModel(Settings::Config::SimulationModel::CellGrowth::AdhesiveRepulsionFactor())
    {
    }

    CellGrowthModel::CellGrowthModel(double adhesiveRepulsionFactor)
        : m_adhesiveRepulsionFactor(adhesiveRepulsionFactor)
    {
        if (adhesiveRepulsionFactor < 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Model.CellGrowthModel.CellGrowthModel.Error.adhesiveRepulsionFactor"));
    }

    void CellGrowthModel::BeforeAdvanceStep(
        const Simulation*,
        SimulationModelStepArgs
    )
    {
    }

    Numerics::Vector3 CellGrowthModel::ComputeForceOnCell(
        const Simulation*,
        SimulationModelForceComputationArgs args
    ) const
    {
        Cells::CellInfo info{ *args.Target };

        Numerics::Vector3 vec;

        CELLSIM_CELLALGORITHMS_CELLALGORITHM_ITERATE(
            cellInfo,
            args.CellAlgorithm,
            args.Target,
            args.AffectedCells,
            args.Fields,
            {
                const Numerics::Vector3 diff = info.Position - cellInfo.Position;
                const double dist = diff.Length();
                const double sumRadius = info.Radius + cellInfo.Radius;

                if (dist < sumRadius) {

                    double tmp = 1.0 - dist / sumRadius;

                    vec += diff * (tmp * tmp);
                }
            }
        )

        return m_adhesiveRepulsionFactor * vec;
    }

    void CellGrowthModel::OnAdvanceStep(
        const Simulation*,
        SimulationModelStepArgs
    )
    {
    }
}