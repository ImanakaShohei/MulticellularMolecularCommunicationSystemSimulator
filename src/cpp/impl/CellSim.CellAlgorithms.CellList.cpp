#include "CellSim.CellAlgorithms.CellList.hpp"
#include "CellSim.Cells.CellInfo.hpp"
#include "CellSim.Threading.Generator.hpp"

namespace CellSim::CellAlgorithms
{
    CellList::CellList()
    {
        // TODO: ここに処理を追加します
    }

    CellList::~CellList()
    {
        // TODO: ここに処理を追加します
    }

    void CellList::BeforeAdvanceStep(
        [[maybe_ununsed]] ::std::vector<Cells::Cell> const& cells,
        [[maybe_ununsed]] ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
    )
    {
        // TODO: ここに処理を追加します
    }

    ::std::vector<Cells::CellInfo> CellList::GetAffectableCellInfos(
        [[maybe_ununsed]] Cells::Cell const& target,
        [[maybe_ununsed]] ::std::vector<Cells::Cell> const& cells,
        [[maybe_ununsed]] ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
    )
    {
        //: ここに処理を追加します
        return {};
    }

    Threading::Generator<Cells::CellInfo> CellList::IterateAffectableCellInfos(
        [[maybe_ununsed]] Cells::Cell const& target,
        [[maybe_ununsed]] ::std::vector<Cells::Cell> const& cells,
        [[maybe_ununsed]] ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
    )
    {
        //: ここに処理を追加します
        co_return;
    }

    void CellList::OnAdvanceStep(
        [[maybe_ununsed]] ::std::vector<Cells::Cell> const& cells,
        [[maybe_ununsed]] ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
    )
    {
        // TODO: ここに処理を追加します
    }
}