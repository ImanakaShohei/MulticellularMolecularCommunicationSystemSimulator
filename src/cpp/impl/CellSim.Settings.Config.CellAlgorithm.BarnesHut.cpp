#include "CellSim.Settings.Config.CellAlgorithm.BarnesHut.hpp"
#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    void Config::CellAlgorithm::BarnesHut::Load(
        ::nlohmann::json const& config
    )
    {
        if (config.is_null()) return;

        // TODO: ここで設定を読み込みます
        s_theta = config["theta"];
    }
}