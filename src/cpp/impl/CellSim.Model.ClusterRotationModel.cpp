#include "CellSim.Model.ClusterRotationModel.hpp"
#include "CellSim.Numerics.Vector3T.hpp"

namespace CellSim::Model
{
    void ClusterRotationModel::BeforeAdvanceStep(
        ::std::vector<Cells::Cell>& cells,
        ::std::vector<Molecular::MoleculeDiffusion> const& molecules
    )
    {
        // TODO: ここに処理を追加します
    }

    Numerics::Vector3 ClusterRotationModel::ComputeForceOnCell(
        Cells::Cell const& target,
        ::std::vector<Cells::Cell> const& cells,
        ::std::vector<Molecular::MoleculeDiffusion> const& moleculeSpaces,
        const CellAlgorithms::CellAlgorithm* pCellAlgorithm
    ) const
    {
        // TODO: ここに処理を追加します

        return Numerics::Vector3();
    }

    void ClusterRotationModel::InitializeCells(::std::vector<Cells::Cell>& cells)
    {
        // TODO: ここに処理を追加します
    }

    void ClusterRotationModel::OnAdvanceStep(
        ::std::vector<Cells::Cell>& cells,
        ::std::vector<Molecular::MoleculeDiffusion> const& molecules
    )
    {
        // TODO: ここに処理を追加します
    }
}