#include "CellSim.Settings.Config.CellBehavior.WavePropagation.hpp"

#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    void Config::CellBehavior::WavePropagation::Load(::nlohmann::json const& config)
    {
        if (config.is_null()) return;

        
    }
}