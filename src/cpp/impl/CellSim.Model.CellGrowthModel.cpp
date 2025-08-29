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
#include <nlohmann/json.hpp>

namespace CellSim::Model
{
    CellGrowthModel::Params* CellGrowthModel::Params::FromJson(::nlohmann::json const& j)
    {
        if (j.is_null()) [[unlikely]] throw ::std::runtime_error(Messages::Get("Model.CellGrowthModel.Params.FromJson.JsonError"));

        double adhesiveRepulsionFactor;

        try {
            adhesiveRepulsionFactor = j.at("adhesiveRepulsionFactor").get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Model.CellGrowthModel.Params.FromJson.JsonError"));
        }

        if (adhesiveRepulsionFactor < 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.CellGrowth.Load.Error.adhesiveRepulsionFactor"));

        return new Params(
            adhesiveRepulsionFactor
        );
    }

    CellGrowthModel::Params::Params(
        double adhesiveRepulsionFactor
    )
        : AdhesiveRepulsionFactor(adhesiveRepulsionFactor)
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
        Params params = *static_cast<Params*>(info.Type.Params());

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

        return params.AdhesiveRepulsionFactor * vec;
    }

    void CellGrowthModel::OnAdvanceStep(
        const Simulation*,
        SimulationModelStepArgs
    )
    {
    }
}