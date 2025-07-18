#include "CellSim.Settings.Config.SimulationModel.CellGrowth.hpp"
#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    void Config::SimulationModel::CellGrowth::Load(::nlohmann::json const& config)
    {
        if (config.is_null()) return;
        
        try {
            s_adhesiveRepulsionFactor = config.at("adhesiveRepulsionFactor").get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.CellGrowth.Load.Error.JsonError"));
        }

        if (s_adhesiveRepulsionFactor < 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.CellGrowth.Load.Error.adhesiveRepulsionFactor"));
    }
}