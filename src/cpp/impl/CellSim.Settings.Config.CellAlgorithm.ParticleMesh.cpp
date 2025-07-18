#include "CellSim.Settings.Config.CellAlgorithm.ParticleMesh.hpp"
#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    void Config::CellAlgorithm::ParticleMesh::Load([[maybe_unused]] ::nlohmann::json const& config)
    {
        if (config.is_null()) return;
        
        // TODO: ここで設定を読み込みます
    }
}
