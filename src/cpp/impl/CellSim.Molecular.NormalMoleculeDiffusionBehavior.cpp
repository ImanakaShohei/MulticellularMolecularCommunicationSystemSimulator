#include "CellSim.Molecular.NormalMoleculeDiffusionBehavior.hpp"
#include "CellSim.Containers.Span3.hpp"
#include "CellSim.Numerics.Vector3T.hpp"

namespace CellSim::Molecular
{
    void NormalMoleculeDiffusionBehavior::BeforeAdvanceStep(
        [[maybe_unused]] ::std::vector<Cells::Cell> const& cells,
        [[maybe_unused]] Molecular::MoleculeField const& field
    )
    {
        // TODO: ここに処理を追加します
    }

    void NormalMoleculeDiffusionBehavior::Diffuse(
        [[maybe_unused]] Containers::Span3<double> concentrations,
        [[maybe_unused]] Molecular::MoleculeField const& field
    )
    {
        // TODO: ここに処理を追加します
    }

    void NormalMoleculeDiffusionBehavior::OnAdvanceStep(
        [[maybe_unused]] ::std::vector<Cells::Cell> const& cells,
        [[maybe_unused]] Molecular::MoleculeField const& field
    )
    {
        // TODO: ここに処理を追加します
    }
}