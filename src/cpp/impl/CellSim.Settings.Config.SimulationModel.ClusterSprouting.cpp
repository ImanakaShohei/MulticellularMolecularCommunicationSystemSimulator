#include "CellSim.Settings.Config.SimulationModel.ClusterSprouting.hpp"
#include "CellSim.Messages.hpp"

#include <stdexcept>
#include <nlohmann/json.hpp>

namespace CellSim::Settings
{
    void Config::SimulationModel::ClusterSprouting::Load(::nlohmann::json const& config)
    {
        if (config.is_null()) return;
        
        try {
            s_contactDistance = config.at("contactDistance").get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.SimulationModel.ClusterSprouting.Load.Error.JsonError"));
        }

        if (s_contactDistance < 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Settings.Config.SimulationModel.ClusterSprouting.Load.Error.contactDistance"));
    }
}