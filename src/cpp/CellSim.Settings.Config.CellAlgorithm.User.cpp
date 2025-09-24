#include "CellSim.Settings.Config.CellAlgorithm.User.hpp"

#include <nlohmann/json.hpp>

using namespace CellSim;
using namespace CellSim::Settings;

namespace CellSim::Settings
{
    void Config::CellAlgorithm::User::Load(
        ::nlohmann::json const& config
    )
    {
        if (config.is_null()) return;

        // TODO: ここに処理を追加します
    }
}