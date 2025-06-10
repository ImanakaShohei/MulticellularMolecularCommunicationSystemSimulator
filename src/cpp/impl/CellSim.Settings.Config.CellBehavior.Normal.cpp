#include "CellSim.Settings.Config.CellBehavior.Normal.hpp"

#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    void Config::CellBehavior::Normal::Load(::nlohmann::json const&)
    {
        // 今のところ何もしない
    }
}