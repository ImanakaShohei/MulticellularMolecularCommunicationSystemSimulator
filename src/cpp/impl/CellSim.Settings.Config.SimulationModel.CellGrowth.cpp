#include "CellSim.Settings.Config.SimulationModel.CellGrowth.hpp"
#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    void Config::SimulationModel::CellGrowth::Load(::nlohmann::json const&)
    {
        return;
    }
}