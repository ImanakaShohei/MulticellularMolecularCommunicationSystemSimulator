#include "CellSim.Settings.Config.CellBehavior.Normal.hpp"

#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    void Config::CellBehavior::Normal::Load(::nlohmann::json const& config)
    {
        try {
            s_cellDivisionRadius = config["behaviorType"].get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.CellBehavior.Normal.Load.Error.JsonError"));
        }

        if (s_cellDivisionRadius <= 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.CellBehavior.Normal.Load.Error.cellDivisionRadius"));
    }
}