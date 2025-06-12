#include "CellSim.Molecular.MoleculeBehavior.hpp"
#include "CellSim.Molecular.MoleculeBehaviorKind.hpp"
#include "CellSim.Molecular.NormalMoleculeBehavior.hpp"
#include "CellSim.Molecular.NullMoleculeBehavior.hpp"
#include "CellSim.Settings.Config.Molecular.hpp"
#include "../CellSim.Users.UserMoleculeBehavior.hpp"
#include <stdexcept>

namespace CellSim::Molecular
{
    MoleculeBehavior* MoleculeBehavior::FromKind(MoleculeBehaviorKind kind)
    {
        return FromKind(kind, Settings::Config::Molecular::BoundaryCondition());
    }

    MoleculeBehavior* MoleculeBehavior::FromKind(MoleculeBehaviorKind kind, ::CellSim::Molecular::BoundaryCondition condition)
    {
        switch (kind) {
            case MoleculeBehaviorKind::Normal: return new NormalMoleculeBehavior(condition);
            case MoleculeBehaviorKind::Null:   return new NullMoleculeBehavior(condition);
            case MoleculeBehaviorKind::User:   return new Users::UserMoleculeBehavior(condition);
            default: [[unlikely]]
            {
                throw ::std::invalid_argument("Invalid MoleculeBehaviorKind argument.");
            }
        }
    }

    MoleculeBehavior::MoleculeBehavior() noexcept
        : m_boundaryCondition(Settings::Config::Molecular::BoundaryCondition())
    {
    }

}