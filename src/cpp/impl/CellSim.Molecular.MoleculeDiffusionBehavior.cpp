#include "CellSim.Molecular.MoleculeDiffusionBehavior.hpp"
#include "CellSim.Molecular.MoleculeDiffusionBehaviorKind.hpp"
#include "CellSim.Molecular.NormalMoleculeDiffusionBehavior.hpp"
#include "CellSim.Molecular.NullMoleculeDiffusionBehavior.hpp"
#include "../CellSim.Users.UserMoleculeDiffusionBehavior.hpp"
#include <stdexcept>

namespace CellSim::Molecular
{
    MoleculeDiffusionBehavior* MoleculeDiffusionBehavior::FromKind(MoleculeDiffusionBehaviorKind kind)
    {
        switch (kind) {
            case MoleculeDiffusionBehaviorKind::Normal: return new NormalMoleculeDiffusionBehavior();
            case MoleculeDiffusionBehaviorKind::Null:   return new NullMoleculeDiffusionBehavior();
            case MoleculeDiffusionBehaviorKind::User:   return new Users::UserMoleculeDiffusionBehavior();
            default: [[unlikely]]
            {
                throw ::std::invalid_argument("Invalid MoleculeDiffusionBehaviorKind argument.");
            }
        }
    }
}