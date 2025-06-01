#include "CellSim.Users.UserCellBehavior.hpp"

using namespace CellSim;
using namespace CellSim::Cells;

namespace CellSim::Users
{
    CellBehavior* UserCellBehavior::CreateClone() const
    {
        // ここはいじらない
        return new UserCellBehavior(*this);
    }

    bool UserCellBehavior::HasState() const noexcept
    {
        // このクラスにフィールドを追加した場合は'true'に変える
        return false;
    }
}