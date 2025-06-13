#include "CellSim.Users.UserCellBehavior.hpp"
#include "impl/CellSim.Cells.CellDivisionResult.hpp"
#include "impl/CellSim.Cells.CellGrowthResult.hpp"
#include "impl/CellSim.Cells.CellMetabolicArgs.hpp"
#include "impl/CellSim.Cells.CellMoleculeEmissionArgs.hpp"
#include "impl/CellSim.Cells.CellMoleculeSensingArgs.hpp"
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

    CellGrowthResult UserCellBehavior::ComputeGrowth([[maybe_unused]] const Cell* sender)
    {
        CellGrowthResult result;

        // TODO: resultに値を格納します

        return result;
    }

    double UserCellBehavior::ComputeMetabolicChange(
        [[maybe_unused]] const Cell* sender,
        [[maybe_unused]] CellMetabolicArgs args
    )
    {
        // TODO: ここに処理を追加します
        return 0.0;
    }

    double UserCellBehavior::ComputeMoleculeEmitAmount(
        [[maybe_unused]] const Cell* sender,
        [[maybe_unused]] CellMoleculeEmissionArgs args
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