#include "CellSim.Users.UserCellBehavior.hpp"
#include "impl/CellSim.Cells.CellGrowthResult.hpp"

using namespace CellSim;
using namespace CellSim::Cells;

namespace CellSim::Users
{
    CellGrowthResult UserCellBehavior::ComputeGrowth(Cell const& cell) const
    {
        CellGrowthResult result;

        // TODO: resultに値を格納します

        return result;
    }

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