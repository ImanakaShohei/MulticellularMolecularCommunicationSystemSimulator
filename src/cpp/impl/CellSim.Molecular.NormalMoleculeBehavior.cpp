#include "CellSim.Molecular.NormalMoleculeBehavior.hpp"
#include "CellSim.Molecular.MoleculeField.hpp"
#include "CellSim.Containers.Span3.hpp"
#include "CellSim.Numerics.Vector3T.hpp"
#include "CellSim.Molecular.MoleculeBehaviorStepArgs.hpp"
#include "CellSim.Molecular.MoleculeDiffusionArgs.hpp"
#include "CellSim.Molecular.MoleculeInitializationArgs.hpp"

namespace CellSim::Molecular
{
    double NormalMoleculeBehavior::m_computeDiffuse(
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

    void NormalMoleculeBehavior::BeforeAdvanceStep(
        [[maybe_unused]] const MoleculeField* sender,
        [[maybe_unused]] MoleculeBehaviorStepArgs args
    )
    {
        // TODO: ここに処理を追加します
    }

    void NormalMoleculeBehavior::Diffuse(
        const MoleculeField* sender,
        [[maybe_unused]] MoleculeDiffusionArgs args
    )
    {
        double co = sender->GridLengthX() * sender->GridCountY() * sender->GridCountZ();
        double reverseCo = 1.0 / co;


    }

    void NormalMoleculeBehavior::InitializeMolecules(
        [[maybe_unused]] const MoleculeField* sender,
        [[maybe_unused]] MoleculeInitializationArgs args
    )
    {
        // TODO: ここに処理を追加します
    }

    void NormalMoleculeBehavior::OnAdvanceStep(
        [[maybe_unused]] const MoleculeField* sender,
        [[maybe_unused]] MoleculeBehaviorStepArgs args
    )
    {
        // TODO: ここに処理を追加します
    }
}