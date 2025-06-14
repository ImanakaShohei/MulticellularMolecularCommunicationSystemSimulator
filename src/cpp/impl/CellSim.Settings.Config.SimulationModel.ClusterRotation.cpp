#include "CellSim.Settings.Config.SimulationModel.ClusterRotation.hpp"
#include "CellSim.Messages.hpp"

#include <stdexcept>
#include <nlohmann/json.hpp>

namespace CellSim::Settings
{
    void Config::SimulationModel::ClusterRotation::Load(::nlohmann::json const& config)
    {
        try {
            s_adhesionDistanceThreshold = config.at("adhesionDistanceThreshold").get<double>();
            s_adhesionForceFactor =  config.at("adhesionForceFactor").get<double>();
            s_centralForceFactor = config.at("centralForceFactor").get<double>();
            s_repulsionFactor = config.at("repulsionFactor").get<double>();
            s_repulsionMaxDistance = config.at("repulsionMaxDistance").get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.ClusterRotation.Load.Error.JsonError"));
        }

        if (s_adhesionDistanceThreshold < 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Settings.Config.SimulationModel.ClusterRotation.Load.Error.adhesionDistanceThreshold"));
        if (s_adhesionForceFactor < 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Settings.Config.SimulationModel.ClusterRotation.Load.Error.adhesionForceFactor"));
        if (s_centralForceFactor < 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Settings.Config.SimulationModel.ClusterRotation.Load.Error.centralForceFactor"));
        if (s_repulsionFactor < 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Settings.Config.SimulationModel.ClusterRotation.Load.Error.repulsionFactor"));
        if (s_repulsionMaxDistance < 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Settings.Config.SimulationModel.ClusterRotation.Load.Error."));

        if (s_repulsionMaxDistance >= s_adhesionDistanceThreshold) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Settings.Config.SimulationModel.ClusterRotation.Load.Error."));
    }
}