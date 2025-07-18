#include "CellSim.Settings.Config.CellBehavior.hpp"
#include "CellSim.Settings.Config.CellBehavior.MoleculeAware.hpp"
#include "CellSim.Settings.Config.CellBehavior.Normal.hpp"
#include "../CellSim.Settings.Config.CellBehavior.User.hpp"

#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    void Config::CellBehavior::Load(::nlohmann::json const& config)
    {
        ::std::string s;

        try {
            s = config.at("behaviorType").get<::std::string>();
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.CellBehavior.Load.Error.JsonError"));
        }

        if (s == "MoleculeAware") s_behaviorType = Cells::CellBehaviorType::MoleculeAware;
        else if (s == "Normal") s_behaviorType = Cells::CellBehaviorType::Normal;
        else if (s == "User") s_behaviorType = Cells::CellBehaviorType::User;
        else if (s == "WavePropagation") s_behaviorType = Cells::CellBehaviorType::WavePropagation;
        else [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.CellBehavior.Load.Error.behaviorType"));

        MoleculeAware::Load(config["moleculeAware"]);
        Normal::Load(config["normal"]);
        User::Load(config["user"]);
        
    }
}