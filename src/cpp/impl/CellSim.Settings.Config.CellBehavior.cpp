#include "CellSim.Settings.Config.CellBehavior.hpp"
#include "CellSim.Settings.Config.CellBehavior.MoleculeAware.hpp"
#include "CellSim.Settings.Config.CellBehavior.Normal.hpp"
#include "CellSim.Settings.Config.CellBehavior.WavePropagation.hpp"
#include "CellSim.Cells.CellBehaviorPtr.hpp"
#include "../CellSim.Settings.Config.CellBehavior.User.hpp"

#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    Cells::CellBehaviorPtr Config::CellBehavior::FromJson(
        ::nlohmann::json& config,
        Cells::CellBehaviorType type
    )
    {
        switch (type) {
            case Cells::CellBehaviorType::MoleculeAware: return MoleculeAware::FromJson(config["moleculeAware"]);
            case Cells::CellBehaviorType::Normal: return Normal::FromJson(config["normal"]);
            case Cells::CellBehaviorType::User: return User::FromJson(config["user"]);
            case Cells::CellBehaviorType::WavePropagation: return WavePropagation::FromJson(config["wavePropagation"]);

            default: [[unlikely]] return nullptr;
        }
    }
    
}