#include "CellSim.Settings.Config.CellBehavior.hpp"
#include "CellSim.Settings.Config.CellBehavior.MoleculeAware.hpp"
#include "CellSim.Settings.Config.CellBehavior.Normal.hpp"
#include "CellSim.Settings.Config.CellBehavior.WavePropagation.hpp"
#include "../CellSim.Settings.Config.CellBehavior.User.hpp"

#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    void Config::CellBehavior::Load(::nlohmann::json const& config)
    {
        MoleculeAware::Load(config["moleculeAware"]);
        Normal::Load(config["normal"]);
        User::Load(config["user"]);
        WavePropagation::Load(config["wavePropagation"]);
    }
}