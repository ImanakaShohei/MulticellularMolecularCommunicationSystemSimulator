#include "CellSim.Settings.Config.UserSettings.hpp"

#include <nlohmann/json.hpp>

using namespace CellSim;

namespace CellSim::Settings
{
    void Config::UserSettings::Load(::nlohmann::json& config)
    {
        if (config.is_null()) return;

        // TODO: ここに処理を追加します
    }
}