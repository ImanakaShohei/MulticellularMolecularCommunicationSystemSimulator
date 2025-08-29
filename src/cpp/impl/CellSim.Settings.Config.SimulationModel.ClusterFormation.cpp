#include "CellSim.Settings.Config.SimulationModel.ClusterFormation.hpp"
#include "CellSim.Messages.hpp"

#include <stdexcept>
#include <nlohmann/json.hpp>

namespace CellSim::Settings
{
    void Config::SimulationModel::ClusterFormation::Load(::nlohmann::json const&)
    {
        return;
    }
}