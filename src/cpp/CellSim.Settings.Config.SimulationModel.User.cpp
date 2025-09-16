#include "CellSim.Settings.Config.SimulationModel.User.hpp"
#include "CellSim.Users.UserSimulationModel.hpp"
#include "impl/CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

using namespace nlohmann;
using namespace CellSim;
using namespace CellSim::Model;
using namespace CellSim::Users;

namespace CellSim::Settings
{
    CellSimulationModel::Params* Config::SimulationModel::User::Params::FromJson(
        [[maybe_unused]] json const& j
    )
    {
        return new UserSimulationModel::Params();
    }

    void Config::SimulationModel::User::Load(
        json const& config
    )
    {
        if (config.is_null()) return;

        // TODO: ここに処理を追加します
    }
}