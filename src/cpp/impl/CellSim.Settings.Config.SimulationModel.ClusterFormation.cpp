#include "CellSim.Settings.Config.SimulationModel.ClusterFormation.hpp"
#include "CellSim.Messages.hpp"

#include <stdexcept>
#include <nlohmann/json.hpp>

namespace CellSim::Settings
{
    void Config::SimulationModel::ClusterFormation::Load(::nlohmann::json const& config)
    {
        if (config.is_null()) return;
        
        try {
            s_adhesiveRepulsionFactor = config.at("adhesiveRepulsionFactor").get<double>();
            s_lambda = config.at("lambda").get<double>();
            s_remoteForceFactor = config.at("remoteForceFactor").get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.ClusterFormation.Load.Error.JsonError"));
        }

        if (s_adhesiveRepulsionFactor < 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.ClusterFormation.Load.Error.adhesiveRepulsionFactor"));
        if (s_lambda == 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.ClusterFormation.Load.Error.lambda"));
        if (s_remoteForceFactor < 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.ClusterFormation.Load.Error.remoteForceFactor"));
    }
}