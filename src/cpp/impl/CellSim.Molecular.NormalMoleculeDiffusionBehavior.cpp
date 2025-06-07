#include "CellSim.Molecular.NormalMoleculeDiffusionBehavior.hpp"
#include "CellSim.Molecular.MoleculeField.hpp"
#include "CellSim.Containers.Span3.hpp"
#include "CellSim.Numerics.Vector3T.hpp"

namespace CellSim::Molecular
{
    double NormalMoleculeDiffusionBehavior::m_computeDiffuse(
        Containers::Span3<double> concentrations,
        double reverseCo,
        size_t x,
        size_t y,
        size_t z
    ) const noexcept
    {
        return m_diffusionFactor *
            (
                concentrations[x + 1][y][z] + concentrations[x - 1][y][z] + concentrations[x][y + 1][z] +
                concentrations[x][y - 1][z] + concentrations[x][y][z + 1] + concentrations[x][y][z - 1] -
                6.0 * concentrations[x][y][z]
            ) /
            reverseCo
        ;
    }

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
        double co = field.GridLengthX() * field.GridCountY() * field.GridCountZ();
        double reverseCo = 1.0 / co;


    }

    void NormalMoleculeDiffusionBehavior::InitializeMolecules(
        [[maybe_unused]] InitialMoleculeDistribution initialMoleculeDistribution,
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