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
        [[maybe_unused]] ::std::vector<Cells::Cell> const& cells,
        [[maybe_unused]] ::std::vector<Molecular::MoleculeField> const& molecules
    )
    {
        // TODO: ここに処理を追加します
    }

    ::std::vector<Cells::CellInfo> ParticleMesh::GetAffectableCellInfos(
        [[maybe_unused]] Cells::Cell const& target,
        [[maybe_unused]] ::std::vector<Cells::Cell> const& cells,
        [[maybe_unused]] ::std::vector<Molecular::MoleculeField> const& molecules
    ) const
    {
        //: ここに処理を追加します
        return {};
    }

    bool ParticleMesh::HasMultithreadingSupport() const noexcept
    {
        // TODO: 複数スレッドによる処理ができない場合は'false'にします
        return true;
    }

    Threading::Generator<Cells::CellInfo> ParticleMesh::IterateAffectableCellInfos(
        [[maybe_unused]] Cells::Cell const& target,
        [[maybe_unused]] ::std::vector<Cells::Cell> const& cells,
        [[maybe_unused]] ::std::vector<Molecular::MoleculeField> const& molecules
    ) const
    {
        //: ここに処理を追加します
        co_return;
    }

    void ParticleMesh::OnAdvanceStep(
        [[maybe_unused]] ::std::vector<Cells::Cell> const& cells,
        [[maybe_unused]] ::std::vector<Molecular::MoleculeField> const& molecules
    )
    {
        // TODO: ここに処理を追加します
    }
}