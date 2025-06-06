#include "CellSim.Users.UserCellBehavior.hpp"
#include "impl/CellSim.Cells.CellGrowthResult.hpp"

using namespace CellSim;
using namespace CellSim::Cells;
using namespace CellSim::Molecular;

namespace CellSim::Users
{
    CellGrowthResult UserCellBehavior::ComputeGrowth([[maybe_unused]] Cell const& cell)
    {
        CellGrowthResult result;

        // TODO: resultに値を格納します

        return result;
    }

    double UserCellBehavior::ComputeMoleculeEmitAmount(
        [[maybe_unused]] Cell const& cell,
        [[maybe_unused]] MoleculeField const& field
    )
    {
        // TODO: 放出量を計算します
        return 0.0;
    }

    CellBehavior* UserCellBehavior::CreateClone() const
    {
        // ここはいじらない
        return new UserCellBehavior();
    }

    bool UserCellBehavior::HasState() const noexcept
    {
        // このクラスにフィールドを追加した場合は'true'に変える
        return false;
    }
}