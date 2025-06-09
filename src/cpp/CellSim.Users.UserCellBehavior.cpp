#include "CellSim.Users.UserCellBehavior.hpp"
#include "impl/CellSim.Cells.CellDivisionResult.hpp"
#include "impl/CellSim.Cells.CellGrowthResult.hpp"
#include "impl/CellSim.Molecular.MoleculeInfo.hpp"

using namespace CellSim;
using namespace CellSim::Cells;
using namespace CellSim::Molecular;

namespace CellSim::Users
{
    CellDivisionResult ComputeDivisionOutcome([[maybe_unused]] const Cell* sender)
    {
        CellDivisionResult result;

        // TODO: ここに処理を追加します

        return result;
    }

    CellGrowthResult UserCellBehavior::ComputeGrowth([[maybe_unused]] Cell const& cell)
    {
        CellGrowthResult result;

        // TODO: resultに値を格納します

        return result;
    }

    double UserCellBehavior::ComputeMetabolicChange(
        [[maybe_unused]] const Cells::Cell* sender,
        [[maybe_unused]] Molecular::MoleculeInfo args
    )
    {
        // TODO: ここに処理を追加します
        return 0.0;
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

    bool UserCellBehavior::ShouldDivideThisStep() noexcept
    {
        // TODO: ここに処理を追加します
        return false;
    }
}