#include "CellSim.Users.UserCellAlgorithm.hpp"
#include "impl/CellSim.Cells.CellInfo.hpp"
#include "impl/CellSim.Threading.Generator.hpp"

using namespace CellSim;
using namespace CellSim::CellAlgorithms;
using namespace CellSim::Cells;
using namespace CellSim::Model;
using namespace CellSim::Model::Molecule;
using namespace CellSim::Threading;

namespace CellSim::Users
{
    void UserCellAlgorithm::BeforeNextStep(
        [[maybe_ununsed]] ::std::vector<Cell> const& cells,
        [[maybe_ununsed]] ::std::vector<MoleculeDiffusion> const& molecules
    )
    {
        // TODO: ここに処理を追加します
    }

    ::std::vector<CellInfo> GetAffectableCellInfos(
        [[maybe_ununsed]] Cell const& c,
        [[maybe_ununsed]] ::std::vector<Cell> const& cells,
        [[maybe_ununsed]] ::std::vector<MoleculeDiffusion> const& molecules
    )
    {
        //: ここに処理を追加します
        return {};
    }

    Generator<CellInfo> UserCellAlgorithm::IterateAffectableCellInfos(
        [[maybe_ununsed]] Cell const& c,
        [[maybe_ununsed]] ::std::vector<Cell> const& cells,
        [[maybe_ununsed]] ::std::vector<MoleculeDiffusion> const& molecules
    )
    {
        //: ここに処理を追加します
        co_return;
    }

    void UserCellAlgorithm::OnNextStep(
        [[maybe_ununsed]] ::std::vector<Cell> const& cells,
        [[maybe_ununsed]] ::std::vector<MoleculeDiffusion> const& molecules
    )
    {
        // TODO: ここに処理を追加します
    }
}