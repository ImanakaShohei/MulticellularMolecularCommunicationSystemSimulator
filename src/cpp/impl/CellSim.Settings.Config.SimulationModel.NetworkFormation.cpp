#include "CellSim.Settings.Config.SimulationModel.NetworkFormation.hpp"
#include "CellSim.Messages.hpp"
#include "CellSim.Text.CString.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    void Config::SimulationModel::NetworkFormation::Load(::nlohmann::json const& config)
    {
        if (config.is_null()) return;
        
        try {
            s_maxAttractionDistance = config.at("maxAttractionDistance").get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.NetworkFormation.Load.Error.JsonError"));
        }

        
        if (s_maxAttractionDistance <= 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.NetworkFormation.Load.Error.maxAttractionDistance"));
        
    }
}