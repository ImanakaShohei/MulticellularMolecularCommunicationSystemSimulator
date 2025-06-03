#include "CellSim.Model.CellGrowthModel.hpp"
#include "CellSim.Numerics.Vector3T.hpp"

namespace CellSim::Model
{
    void CellGrowthModel::BeforeAdvanceStep(
        ::std::vector<Cells::Cell>& cells,
        ::std::vector<Molecule::MoleculeDiffusion> const& molecules
    )
    {
        // TODO: ここに処理を追加します
    }

    Numerics::Vector3 CellGrowthModel::ComputeForceOnCell(
        Cells::Cell const& target,
        ::std::vector<Cells::Cell> const& cells,
        ::std::vector<Molecule::MoleculeDiffusion> const& moleculeSpaces,
        CellAlgorithms::CellAlgorithm const& cellAlgorithm
    ) const
    {
        // TODO: ここに処理を追加します

        return Numerics::Vector3();
    }

    void CellGrowthModel::InitializeCells(::std::vector<Cells::Cell>& cells)
    {
        // TODO: ここに処理を追加します
    }

    void CellGrowthModel::OnAdvanceStep(
        ::std::vector<Cells::Cell>& cells,
        ::std::vector<Molecule::MoleculeDiffusion> const& molecules
    )
    {
        // TODO: ここに処理を追加します
    }
}