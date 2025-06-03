#include "CellSim.Settings.Config.SimulationModel.hpp"
#include "CellSim.Settings.Config.SimulationModel.ClusterFormation.hpp"
#include "CellSim.Settings.Config.SimulationModel.NetworkFormation.hpp"

#include <nlohmann/json.hpp>

namespace CellSim::Settings
{
    void Config::SimulationModel::Load(::nlohmann::json const& config)
    {
        ClusterFormation::Load(config["cluster_formation"]);
        NetworkFormation::Load(config["network_formation"]);
    }
}