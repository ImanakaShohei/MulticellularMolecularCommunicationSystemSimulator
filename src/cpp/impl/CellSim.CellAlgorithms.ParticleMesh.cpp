#include "CellSim.CellAlgorithms.ParticleMesh.hpp"
#include "CellSim.Cells.CellInfo.hpp"
#include "CellSim.Threading.Generator.hpp"

namespace CellSim::CellAlgorithms
{
    ParticleMesh::ParticleMesh()
    {
        // TODO: ここに処理を追加します
    }

    ParticleMesh::~ParticleMesh()
    {
        // TODO: ここに処理を追加します
    }

    void ParticleMesh::BeforeAdvanceStep(
        [[maybe_ununsed]] ::std::vector<Cells::Cell> const& cells,
        [[maybe_ununsed]] ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
    )
    {
        // TODO: ここに処理を追加します
    }

    ::std::vector<Cells::CellInfo> ParticleMesh::GetAffectableCellInfos(
        [[maybe_ununsed]] Cells::Cell const& target,
        [[maybe_ununsed]] ::std::vector<Cells::Cell> const& cells,
        [[maybe_ununsed]] ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
    ) const
    {
        //: ここに処理を追加します
        return {};
    }

    Threading::Generator<Cells::CellInfo> ParticleMesh::IterateAffectableCellInfos(
        [[maybe_ununsed]] Cells::Cell const& target,
        [[maybe_ununsed]] ::std::vector<Cells::Cell> const& cells,
        [[maybe_ununsed]] ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
    ) const
    {
        //: ここに処理を追加します
        co_return;
    }

    void ParticleMesh::OnAdvanceStep(
        [[maybe_ununsed]] ::std::vector<Cells::Cell> const& cells,
        [[maybe_ununsed]] ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
    )
    {
        // TODO: ここに処理を追加します
    }
}