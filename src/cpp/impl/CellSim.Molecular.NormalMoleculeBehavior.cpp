#include "CellSim.Molecular.NormalMoleculeBehavior.hpp"
#include "CellSim.Molecular.MoleculeField.hpp"
#include "CellSim.Containers.Span3.hpp"
#include "CellSim.Numerics.Vector3T.hpp"
#include "CellSim.Molecular.MoleculeBehaviorStepArgs.hpp"
#include "CellSim.Molecular.MoleculeDiffusionArgs.hpp"
#include "CellSim.Molecular.MoleculeInitializationArgs.hpp"
#include "CellSim.Messages.hpp"
#include "CellSim.Text.CString.hpp"
#include <stdexcept>

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

    NormalMoleculeBehavior::NormalMoleculeBehavior()
    {
        throw ::std::runtime_error(
            Text::CString::Format(
                Messages::Get("NotImplemented"),
                "NormalMoleculeBehavior::NormalMoleculeBehavior()"
            )
        );
    }

    NormalMoleculeBehavior::NormalMoleculeBehavior(::CellSim::Molecular::BoundaryCondition)
    {
        throw ::std::runtime_error(
            Text::CString::Format(
                Messages::Get("NotImplemented"),
                "NormalMoleculeBehavior::NormalMoleculeBehavior(::CellSim::Molecular::BoundaryCondition)"
            )
        );
    }

    NormalMoleculeBehavior::NormalMoleculeBehavior(double)
    {
        throw ::std::runtime_error(
            Text::CString::Format(
                Messages::Get("NotImplemented"),
                "NormalMoleculeBehavior::NormalMoleculeBehavior(double)"
            )
        );
    }

    NormalMoleculeBehavior::NormalMoleculeBehavior(
        ::CellSim::Molecular::BoundaryCondition,
        double
    )
    {
        throw ::std::runtime_error(
            Text::CString::Format(
                Messages::Get("NotImplemented"),
                "NormalMoleculeBehavior::NormalMoleculeBehavior(::CellSim::Molecular::BoundaryCondition, double)"
            )
        );
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

        switch (m_boundaryCondition) {
            case ::CellSim::Molecular::BoundaryCondition::Absorbing:
            {
                break;
            }
            case ::CellSim::Molecular::BoundaryCondition::Periodic:
            {
                break;
            }
            case ::CellSim::Molecular::BoundaryCondition::Reflective:
            {
                break;
            }
        }
    }

    void NormalMoleculeBehavior::InitializeMolecules(
        [[maybe_unused]] const MoleculeField* sender,
        MoleculeInitializationArgs args
    )
    {
        switch (args.DistributionType) {
            case InitialMoleculeDistribution::Centered:
            {
                break;
            }
            case InitialMoleculeDistribution::Gaussian:
            {
                break;
            }
            case InitialMoleculeDistribution::Uniform:
            {
                break;
            }
        }
    }

    void NormalMoleculeBehavior::OnAdvanceStep(
        [[maybe_unused]] const MoleculeField* sender,
        [[maybe_unused]] MoleculeBehaviorStepArgs args
    )
    {
        // TODO: ここに処理を追加します
    }
}