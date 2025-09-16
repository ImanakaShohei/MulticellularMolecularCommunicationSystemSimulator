#include "CellSim.Settings.Config.SimulationModel.ClusterRotation.hpp"
#include "CellSim.Model.ClusterRotationModel.hpp"
#include "CellSim.Messages.hpp"

#include <stdexcept>
#include <nlohmann/json.hpp>

namespace CellSim::Settings
{
    Model::CellSimulationModel::Params* Config::SimulationModel::ClusterRotation::Params::FromJson(
        ::nlohmann::json const& j
    )
    {
        if (j.is_null()) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Model.ClusterRotationModel.Params.FromJson.JsonError"
                )
            );
        }

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
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.SimulationModel.ClusterRotation.Load.Error.JsonError"
                )
            );
        }

        if (adhesionDistanceThreshold < 0.0) [[unlikely]] {
            throw ::std::invalid_argument(
                Messages::Get(
                    "Settings.Config.SimulationModel.ClusterRotation.Load.Error.adhesionDistanceThreshold"
                )
            );
        }
        if (adhesionForceFactor < 0.0) [[unlikely]] {
            throw ::std::invalid_argument(
                Messages::Get(
                    "Settings.Config.SimulationModel.ClusterRotation.Load.Error.adhesionForceFactor"
                )
            );
        }
        if (centralForceFactor < 0.0) [[unlikely]] {
            throw ::std::invalid_argument(
                Messages::Get(
                    "Settings.Config.SimulationModel.ClusterRotation.Load.Error.centralForceFactor"
                )
            );
        }
        if (repulsionFactor < 0.0) [[unlikely]] {
            throw ::std::invalid_argument(
                Messages::Get(
                    "Settings.Config.SimulationModel.ClusterRotation.Load.Error.repulsionFactor"
                )
            );
        }
        if (repulsionMaxDistance < 0.0) [[unlikely]] {
            throw ::std::invalid_argument(
                Messages::Get(
                    "Settings.Config.SimulationModel.ClusterRotation.Load.Error."
                )
            );
        }

        if (repulsionMaxDistance >= adhesionDistanceThreshold) [[unlikely]] {
            throw ::std::invalid_argument(
                Messages::Get(
                    "Settings.Config.SimulationModel.ClusterRotation.Load.Error."
                )
            );
        }
        return new Model::ClusterRotationModel::Params(
            adhesionDistanceThreshold,
            adhesionForceFactor,
            centralForceFactor,
            repulsionFactor,
            repulsionMaxDistance
        );
    }
}