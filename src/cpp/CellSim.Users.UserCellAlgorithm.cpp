#include "CellSim.Users.UserCellAlgorithm.hpp"
#include "impl/CellSim.Cells.CellInfo.hpp"
#include "impl/CellSim.Threading.Generator.hpp"

using namespace CellSim;
using namespace CellSim::CellAlgorithms;
using namespace CellSim::Cells;
using namespace CellSim::Model;
using namespace CellSim::Molecular;
using namespace CellSim::Threading;

namespace CellSim::Users
{

    UserCellAlgorithm::UserCellAlgorithm()
    {
        // TODO: ここに処理を追加します
    }

    UserCellAlgorithm::~UserCellAlgorithm()
    {
        // TODO: ここに処理を追加します
    }

    void UserCellAlgorithm::BeforeAdvanceStep(
        [[maybe_unused]] ::std::vector<Cell> const& cells,
        [[maybe_unused]] ::std::vector<MoleculeDiffusion> const& molecules
    )
    {
        // TODO: ここに処理を追加します
    }

    ::std::vector<CellInfo> UserCellAlgorithm::GetAffectableCellInfos(
        [[maybe_unused]] Cell const& target,
        [[maybe_unused]] ::std::vector<Cell> const& cells,
        [[maybe_unused]] ::std::vector<MoleculeDiffusion> const& molecules
    ) const
    {
        //: ここに処理を追加します
        return {};
    }

    Generator<CellInfo> UserCellAlgorithm::IterateAffectableCellInfos(
        [[maybe_unused]] Cell const& target,
        [[maybe_unused]] ::std::vector<Cell> const& cells,
        [[maybe_unused]] ::std::vector<MoleculeDiffusion> const& molecules
    ) const
    {
        //: ここに処理を追加します
        co_return;
    }

    void UserCellAlgorithm::OnAdvanceStep(
        [[maybe_unused]] ::std::vector<Cell> const& cells,
        [[maybe_unused]] ::std::vector<MoleculeDiffusion> const& molecules
    )
    {
        // TODO: ここに処理を追加します
    }
}