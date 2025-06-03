#include "CellSim.Model.ClusterSproutingModel.hpp"
#include "CellSim.Numerics.Vector3T.hpp"

namespace CellSim::Model
{
    void ClusterSproutingModel::BeforeAdvanceStep(
        ::std::vector<Cells::Cell>& cells,
        ::std::vector<Molecule::MoleculeDiffusion> const& molecules
    )
    {
        // TODO: ここに処理を追加します
    }

    Numerics::Vector3 ClusterSproutingModel::ComputeForceOnCell(
        Cells::Cell const& target,
        ::std::vector<Cells::Cell> const& cells,
        ::std::vector<Molecule::MoleculeDiffusion> const& moleculeSpaces,
        const CellAlgorithms::CellAlgorithm* pCellAlgorithm
    ) const
    {
        // TODO: ここに処理を追加します

        return Numerics::Vector3();
    }

    void ClusterSproutingModel::InitializeCells(::std::vector<Cells::Cell>& cells)
    {
        // TODO: ここに処理を追加します
    }

    void ClusterSproutingModel::OnAdvanceStep(
        ::std::vector<Cells::Cell>& cells,
        ::std::vector<Molecule::MoleculeDiffusion> const& molecules
    )
    {
        // TODO: ここに処理を追加します
    }
}