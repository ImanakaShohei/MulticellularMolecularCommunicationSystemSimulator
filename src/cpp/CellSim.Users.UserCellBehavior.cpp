#include "CellSim.Users.UserCellBehavior.hpp"
#include "impl/CellSim.Cells.CellDivisionResult.hpp"
#include "impl/CellSim.Cells.CellGrowthResult.hpp"
#include "impl/CellSim.Cells.MolecularProcessArgs.hpp"
#include "impl/CellSim.Cells.MolecularProcessResult.hpp"
#include "impl/CellSim.Cells.CellMoleculeSensingArgs.hpp"
#include "impl/CellSim.Molecular.MoleculeInfo.hpp"

using namespace CellSim;
using namespace CellSim::Cells;
using namespace CellSim::Molecular;

namespace CellSim::Users
{
    CellDivisionResult UserCellBehavior::ComputeDivisionOutcome([[maybe_unused]] const Cell* sender)
    {
        CellDivisionResult result;

        // TODO: ここに処理を追加します

        return result;
    }

    CellGrowthResult UserCellBehavior::ComputeGrowth([[maybe_unused]] const Cell* sender)
    {
        CellGrowthResult result;

        // TODO: resultに値を格納します

        return result;
    }

    MolecularProcessResult UserCellBehavior::ComputeMolecularProcess(const Cell* sender, MolecularProcessArgs args)
    {
        MolecularProcessResult result;

        // TODO: resultに値を格納します

        return result;
    }

    CellBehavior* UserCellBehavior::CreateClone() const
    {
        // ここはいじらない
        return new UserCellBehavior();
    }

    bool UserCellBehavior::IsReusable() const noexcept
    {
        // このクラスの院スタンが使いまわせない場合は'false'に変える
        return true;
    }

    Numerics::Vector3 UserCellBehavior::OnSenseMolecules(
        [[maybe_unused]] const Cells::Cell* sender,
        [[maybe_unused]] Cells::CellMoleculeSensingArgs args
    )
    {
        // TODO: ここに処理を追加します
        return Numerics::Vector3();
    }

    bool UserCellBehavior::ShouldDivideThisStep([[maybe_unused]] const Cell* sender) noexcept
    {
        // TODO: ここに処理を追加します
        return false;
    }
}