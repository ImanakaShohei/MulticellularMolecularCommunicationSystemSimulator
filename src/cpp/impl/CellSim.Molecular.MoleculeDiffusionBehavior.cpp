#include "CellSim.Molecular.MoleculeDiffusionBehavior.hpp"
#include "CellSim.Molecular.MoleculeDiffusionBehaviorKind.hpp"
#include "CellSim.Molecular.NormalMoleculeDiffusionBehavior.hpp"
#include "CellSim.Molecular.NullMoleculeDiffusionBehavior.hpp"
#include "CellSim.Settings.Config.Molecular.hpp"
#include "../CellSim.Users.UserMoleculeDiffusionBehavior.hpp"
#include <stdexcept>

namespace CellSim::Molecular
{
    MoleculeDiffusionBehavior* MoleculeDiffusionBehavior::FromKind(MoleculeDiffusionBehaviorKind kind, ::CellSim::Molecular::BoundaryCondition condition)
    {
        switch (kind) {
            case MoleculeDiffusionBehaviorKind::Normal: return new NormalMoleculeDiffusionBehavior(condition);
            case MoleculeDiffusionBehaviorKind::Null:   return new NullMoleculeDiffusionBehavior(condition);
            case MoleculeDiffusionBehaviorKind::User:   return new Users::UserMoleculeDiffusionBehavior(condition);
            default: [[unlikely]]
            {
                throw ::std::invalid_argument("Invalid MoleculeDiffusionBehaviorKind argument.");
            }
        }
    }

    MoleculeDiffusionBehavior::MoleculeDiffusionBehavior() noexcept
        : m_boundaryCondition(Settings::Config::Molecular::BoundaryCondition())
    {
    }

}