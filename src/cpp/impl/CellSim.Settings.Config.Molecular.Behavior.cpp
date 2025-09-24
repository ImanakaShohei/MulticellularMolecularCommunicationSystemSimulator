#include "CellSim.Settings.Config.Molecular.Behavior.hpp"
#include "CellSim.Settings.Config.Molecular.Behavior.Normal.hpp"
#include "CellSim.Molecular.MoleculeBehavior.hpp"
#include "CellSim.Molecular.NormalMoleculeBehavior.hpp"
#include "CellSim.Molecular.NullMoleculeBehavior.hpp"
#include "../CellSim.Users.UserMoleculeBehavior.hpp"
#include "CellSim.Molecular.MoleculeBehaviorKind.hpp"
#include "CellSim.Messages.hpp"

#include <stdexcept>

#include <nlohmann/json.hpp>

namespace CellSim::Settings
{
    ::CellSim::Molecular::MoleculeBehavior* Config::Molecular::Behavior::FromJson(
        ::nlohmann::json& config,
        ::CellSim::Molecular::MoleculeBehaviorKind kind
    )
    {
        switch (kind) {
            case ::CellSim::Molecular::MoleculeBehaviorKind::Normal:
                return Config::Molecular::Behavior::Normal::FromJson(config["normalBehavior"]);

            case ::CellSim::Molecular::MoleculeBehaviorKind::Null:
                return new ::CellSim::Molecular::NullMoleculeBehavior();
                
            case ::CellSim::Molecular::MoleculeBehaviorKind::User:
                return new ::CellSim::Users::UserMoleculeBehavior();

            default: [[unlikely]] return nullptr;
        }
    }
}