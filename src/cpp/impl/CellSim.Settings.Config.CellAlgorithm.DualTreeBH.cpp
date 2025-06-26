#include "CellSim.Settings.Config.CellAlgorithm.DualTreeBH.hpp"
#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings {
    void Config::CellAlgorithm::DualTreeBH::Load(::nlohmann::json const& config)
    {
        // TODO: ここで設定を読み込みます
        s_theta = config["theta"];
    }
}