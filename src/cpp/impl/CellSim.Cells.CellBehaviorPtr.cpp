#include "CellSim.Cells.CellBehaviorPtr.hpp"
#include "CellSim.Cells.CellBehaviorType.hpp"
#include "CellSim.Cells.NormalCellBehavior.hpp"
#include "../CellSim.Users.UserCellBehavior.hpp"
#include <stdexcept>

namespace CellSim::Cells
{
    CellBehaviorPtr CellBehaviorPtr::FromType(CellBehaviorType type)
    {
        switch (type) {
            case CellBehaviorType::Normal: return CellBehaviorPtr(new NormalCellBehavior());
            case CellBehaviorType::User: return CellBehaviorPtr(new Users::UserCellBehavior());

            default: [[unlikely]]
            {
                throw ::std::invalid_argument("Invalid CellSim::Cells::CellBehaviorType value.");
            }
        }
    }
}