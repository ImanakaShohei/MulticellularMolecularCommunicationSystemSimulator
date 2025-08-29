#include "CellSim.Model.ClusterRotationModel.hpp"
#include "CellSim.Model.SimulationModelForceComputationArgs.hpp"
#include "CellSim.Model.SimulationModelStepArgs.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmAffectableCellQueryArgs.hpp"
#include "CellSim.Cells.CellInfo.hpp"
#include "CellSim.Numerics.Vector3T.hpp"
#include "CellSim.Settings.Config.SimulationModel.ClusterRotation.hpp"

#include <stdexcept>
#include <nlohmann/json.hpp>
#include "CellSim.Messages.hpp"

namespace CellSim::Model
{
    ClusterRotationModel::Params* ClusterRotationModel::Params::FromJson(::nlohmann::json const& j)
    {
        if (j.is_null()) [[unlikely]] throw ::std::runtime_error(Messages::Get("Model.ClusterRotationModel.Params.FromJson.JsonError"));

        double adhesionDistanceThreshold;
        double adhesionForceFactor;
        double centralForceFactor;
        double repulsionFactor;
        double repulsionMaxDistance;

        try {
            adhesionDistanceThreshold = j.at("adhesionDistanceThreshold").get<double>();
            adhesionForceFactor =  j.at("adhesionForceFactor").get<double>();
            centralForceFactor = j.at("centralForceFactor").get<double>();
            repulsionFactor = j.at("repulsionFactor").get<double>();
            repulsionMaxDistance = j.at("repulsionMaxDistance").get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.ClusterRotation.Load.Error.JsonError"));
        }

        if (adhesionDistanceThreshold < 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Settings.Config.SimulationModel.ClusterRotation.Load.Error.adhesionDistanceThreshold"));
        if (adhesionForceFactor < 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Settings.Config.SimulationModel.ClusterRotation.Load.Error.adhesionForceFactor"));
        if (centralForceFactor < 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Settings.Config.SimulationModel.ClusterRotation.Load.Error.centralForceFactor"));
        if (repulsionFactor < 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Settings.Config.SimulationModel.ClusterRotation.Load.Error.repulsionFactor"));
        if (repulsionMaxDistance < 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Settings.Config.SimulationModel.ClusterRotation.Load.Error."));

        if (repulsionMaxDistance >= adhesionDistanceThreshold) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Settings.Config.SimulationModel.ClusterRotation.Load.Error."));

        return new Params(
            adhesionDistanceThreshold,
            adhesionForceFactor,
            centralForceFactor,
            repulsionFactor,
            repulsionMaxDistance
        );
    }

    ClusterRotationModel::Params::Params(
        double adhesionDistanceThreshold,
        double adhesionForceFactor,
        double centralForceFactor,
        double repulsionFactor,
        double repulsionMaxDistance
    )
        : AdhesionDistanceThreshold(adhesionDistanceThreshold)
        , AdhesionForceFactor(adhesionForceFactor)
        , CentralForceFactor(centralForceFactor)
        , RepulsionFactor(repulsionFactor)
        , RepulsionMaxDistance(repulsionMaxDistance)
    {
        if (adhesionDistanceThreshold < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'adhesionDistanceThreshold' must be greater than or equal to zero.");
        if (adhesionForceFactor < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'adhesionForceFactor' must be greater than or equal to zero.");
        if (centralForceFactor < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'centralForceFactor' must be greater than or equal to zero.");
        if (repulsionFactor < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'repulsionFactor' must be greater than or equal to zero.");
        if (repulsionMaxDistance < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'repulsionMaxDistance' must be greater than or equal to zero.");

        if (repulsionMaxDistance >= adhesionDistanceThreshold) [[unlikely]] throw ::std::invalid_argument("'repulsionMaxDistance' must be less than 'adhesionDistanceThreshold'.");
    }

    void ClusterRotationModel::BeforeAdvanceStep(
        const Simulation*,
        SimulationModelStepArgs
    )
    {
    }

    Numerics::Vector3 ClusterRotationModel::ComputeForceOnCell(
        const Simulation*,
        SimulationModelForceComputationArgs args
    ) const
    {
        Numerics::Vector3 force;
        Numerics::Vector3 forceCenter;
        Numerics::Vector3 forceCont;
        Cells::CellInfo info{ *args.Target };
        Params params = *static_cast<Params*>(info.Type.Params());

        forceCenter = info.Position * (-params.CentralForceFactor / info.Position.Length());

        CELLSIM_CELLALGORITHMS_CELLALGORITHM_ITERATE(
            cellInfo,
            args.CellAlgorithm,
            args.Target,
            args.AffectedCells,
            args.Fields,
            {
                Numerics::Vector3 diff = info.Position - cellInfo.Position;
                double dist = diff.Length();

                if (dist < params.RepulsionMaxDistance) {
                    force += diff * ((params.RepulsionMaxDistance - dist) / (params.RepulsionMaxDistance * dist));
                }

                if (dist < params.AdhesionDistanceThreshold) {
                    forceCont += cellInfo.PreviusForce;
                }
            }
        )

        return params.RepulsionFactor * force + params.AdhesionForceFactor * forceCont + forceCenter;
    }

    void ClusterRotationModel::OnAdvanceStep(
        const Simulation*,
        SimulationModelStepArgs
    )
    {
    }
}