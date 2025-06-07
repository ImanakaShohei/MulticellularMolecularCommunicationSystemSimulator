#include "CellSim.Users.UserSimulationModel.hpp"
#include "impl/CellSim.Molecular.MoleculeField.hpp"
#include "impl/CellSim.Numerics.Vector3T.hpp"

using namespace CellSim;
using namespace CellSim::CellAlgorithms;
using namespace CellSim::Cells;
using namespace CellSim::Model;
using namespace CellSim::Molecular;

namespace CellSim::Users
{
    UserSimulationModel::UserSimulationModel()
    {
        // TODO: ここに処理を追加します
    }

    UserSimulationModel::~UserSimulationModel()
    {
        // TODO: ここに処理を追加します
    }

    void UserSimulationModel::BeforeAdvanceStep(
        [[maybe_unused]] ::std::vector<Cell>& cells,
        [[maybe_unused]] ::std::vector<MoleculeField> const& molecules
    )
    {
        // TODO: ここに処理を追加します
    }

    Numerics::Vector3 UserSimulationModel::ComputeForceOnCell(
        [[maybe_unused]] Cell const& target,
        [[maybe_unused]] ::std::vector<Cell> const& cells,
        [[maybe_unused]] ::std::vector<MoleculeField> const& molecules,
        [[maybe_unused]] const CellAlgorithm* pCellAlgorithm
    ) const
    {
        // TODO: ここに処理を追加します

        return Numerics::Vector3();
    }

    void UserSimulationModel::InitializeCells([[maybe_unused]] ::std::vector<Cell>& cells)
    {
        // TODO: ここに処理を追加します
    }

    void UserSimulationModel::OnAdvanceStep(
        [[maybe_unused]] ::std::vector<Cell>& cells,
        [[maybe_unused]] ::std::vector<MoleculeField> const& molecules
    )
    {
        // TODO: ここに処理を追加します
    }

    bool UserSimulationModel::UseCellAlgorithm() const noexcept
    {
        // TODO: ComputeForceOnCell()で引数cellAlgorithmを使用する場合は'true'に置き換えます
        return false;
    }
}