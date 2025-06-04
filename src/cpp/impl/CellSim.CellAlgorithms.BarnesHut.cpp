#include "CellSim.CellAlgorithms.BarnesHut.hpp"
#include "CellSim.Cells.CellInfo.hpp"
#include "CellSim.Threading.Generator.hpp"

namespace CellSim::CellAlgorithms
{
    BarnesHut::BarnesHut()
    {
        // TODO: ここに処理を追加します
    }

    BarnesHut::~BarnesHut()
    {
        // TODO: ここに処理を追加します
    }

    void BarnesHut::BeforeAdvanceStep(
        [[maybe_unused]] ::std::vector<Cells::Cell> const& cells,
        [[maybe_unused]] ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
    )
    {
        // TODO: ここに処理を追加します
    }

    ::std::vector<Cells::CellInfo> BarnesHut::GetAffectableCellInfos(
        [[maybe_unused]] Cells::Cell const& target,
        [[maybe_unused]] ::std::vector<Cells::Cell> const& cells,
        [[maybe_unused]] ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
    ) const
    {
        //: ここに処理を追加します
        return {};
    }

    Threading::Generator<Cells::CellInfo> BarnesHut::IterateAffectableCellInfos(
        [[maybe_unused]] Cells::Cell const& target,
        [[maybe_unused]] ::std::vector<Cells::Cell> const& cells,
        [[maybe_unused]] ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
    ) const
    {
        //: ここに処理を追加します
        co_return;
    }

    void BarnesHut::OnAdvanceStep(
        [[maybe_unused]] ::std::vector<Cells::Cell> const& cells,
        [[maybe_unused]] ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
    )
    {
        // TODO: ここに処理を追加します
    }
}