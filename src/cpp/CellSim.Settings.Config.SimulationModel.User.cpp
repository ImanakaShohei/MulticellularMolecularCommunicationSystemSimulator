#include "CellSim.Settings.Config.SimulationModel.User.hpp"

#include "impl/CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    void Config::SimulationModel::User::Load(::nlohmann::json const& config)
    {
        if (config.is_null()) return;

        // TODO: ここに処理を追加します
    }
}