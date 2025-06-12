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
            s = config["behaviorType"].get<::std::string>();
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.CellBehavior.Load.Error.JsonError"));
        }

        if (s == "Normal") s_behaviorType = Cells::CellBehaviorType::Normal;
        else if (s == "User") s_behaviorType = Cells::CellBehaviorType::User;
        else [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.CellBehavior.Load.Error.behaviorType"));

        switch (s_behaviorType) {
            case Cells::CellBehaviorType::MoleculeAware: MoleculeAware::Load(config["normal"]); break;
            case Cells::CellBehaviorType::Normal: Normal::Load(config["normal"]); break;
            case Cells::CellBehaviorType::User: User::Load(config["user"]); break;
        }
    }
}