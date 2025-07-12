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
    void NormalMoleculeBehavior::m_applyBoundaryConditions(Containers::Span3<double> concentrations)
    {
        switch (BoundaryCondition()) {
            case ::CellSim::Molecular::BoundaryCondition::Absorbing:
            {
                size_t tmp;
                if (Enable2dMode()) {
                    tmp = GridCountY() - 1;
                    for (size_t x = 0; x < GridCountX(); x++) {
                        concentrations[x][0][0]   = 0;
                        concentrations[x][tmp][0] = 0;
                    }
                    
                    tmp = GridCountX() - 1;
                    for (size_t y = 0; y < GridCountY(); y++) {
                        concentrations[0][y][0]   = 0;
                        concentrations[tmp][y][0] = 0;
                    }
                }
                else {
                    tmp = GridCountZ() - 1;
                    for (size_t x = 0; x < GridCountX(); x++) {
                        for (size_t y = 0; y < GridCountY(); y++) {
                            concentrations[x][y][0]   = 0;
                            concentrations[x][y][tmp] = 0;
                        }
                    }
                    
                    tmp = GridCountY() - 1;
                    for (size_t x = 0; x < GridCountX(); x++) {
                        for (size_t z = 0; z < GridCountZ(); z++) {
                            concentrations[x][0][z]   = 0;
                            concentrations[x][tmp][z] = 0;
                        }
                    }
                    
                    tmp = GridCountX() - 1;
                    for (size_t y = 0; y < GridCountY(); y++) {
                        for (size_t z = 0; z < GridCountZ(); z++) {
                            concentrations[0][y][z]   = 0;
                            concentrations[tmp][y][z] = 0;
                        }
                    }
                }
                break;
            }
            case ::CellSim::Molecular::BoundaryCondition::Periodic:
            {
                size_t tmp1;
                size_t tmp2;

                if (Enable2dMode()) {
                    tmp1 = GridCountY() - 2;
                    tmp2 = GridCountY() - 1;
                    for (size_t x = 0; x < GridCountX(); x++) {
                        concentrations[x][0][0]    = concentrations[x][tmp1][0];
                        concentrations[x][tmp2][0] = concentrations[x][1][0];
                    }
                    
                    tmp1 = GridCountX() - 2;
                    tmp2 = GridCountX() - 1;
                    for (size_t y = 0; y < GridCountY(); y++) {
                        concentrations[0][y][0]    = concentrations[tmp1][y][0];
                        concentrations[tmp2][y][0] = concentrations[1][y][0];
                    }
                }
                else {
                    tmp1 = GridCountZ() - 2;
                    tmp2 = GridCountZ() - 1;
                    for (size_t x = 0; x < GridCountX(); x++) {
                        for (size_t y = 0; y < GridCountY(); y++) {
                            concentrations[x][y][0]    = concentrations[x][y][tmp1];
                            concentrations[x][y][tmp2] = concentrations[x][y][1];
                        }
                    }
                    
                    tmp1 = GridCountY() - 2;
                    tmp2 = GridCountY() - 1;
                    for (size_t x = 0; x < GridCountX(); x++) {
                        for (size_t z = 0; z < GridCountZ(); z++) {
                            concentrations[x][0][z]    = concentrations[x][tmp1][z];
                            concentrations[x][tmp2][z] = concentrations[x][1][z];
                        }
                    }
                    
                    tmp1 = GridCountX() - 2;
                    tmp2 = GridCountX() - 1;
                    for (size_t y = 0; y < GridCountY(); y++) {
                        for (size_t z = 0; z < GridCountZ(); z++) {
                            concentrations[0][y][z]    = concentrations[tmp1][y][z];
                            concentrations[tmp2][y][z] = concentrations[1][y][z];
                        }
                    }
                }
                break;
            }
            case ::CellSim::Molecular::BoundaryCondition::Reflective:
            {
                size_t tmp1;
                size_t tmp2;
                if (Enable2dMode()) {
                    tmp1 = GridCountY() - 1;
                    tmp2 = GridCountY() - 2;
                    for (size_t x = 0; x < GridCountX(); x++) {
                        concentrations[x][0][0]    = concentrations[x][1][0];
                        concentrations[x][tmp1][0] = concentrations[x][tmp2][0];
                    }
                    
                    tmp1 = GridCountX() - 1;
                    tmp2 = GridCountX() - 2;
                    for (size_t y = 0; y < GridCountY(); y++) {
                        concentrations[0][y][0]    = concentrations[1][y][0];
                        concentrations[tmp1][y][0] = concentrations[tmp2][y][0];
                    }
                }
                else {
                    tmp1 = GridCountZ() - 1;
                    tmp2 = GridCountZ() - 2;
                    for (size_t x = 0; x < GridCountX(); x++) {
                        for (size_t y = 0; y < GridCountY(); y++) {
                            concentrations[x][y][0]    = concentrations[x][y][1];
                            concentrations[x][y][tmp1] = concentrations[x][y][tmp2];
                        }
                    }
                    
                    tmp1 = GridCountY() - 1;
                    tmp2 = GridCountY() - 2;
                    for (size_t x = 0; x < GridCountX(); x++) {
                        for (size_t z = 0; z < GridCountZ(); z++) {
                            concentrations[x][0][z]    = concentrations[x][1][z];
                            concentrations[x][tmp1][z] = concentrations[x][tmp2][z];
                        }
                    }
                    
                    tmp1 = GridCountX() - 1;
                    tmp2 = GridCountX() - 2;
                    for (size_t y = 0; y < GridCountY(); y++) {
                        for (size_t z = 0; z < GridCountZ(); z++) {
                            concentrations[0][y][z]    = concentrations[1][y][z];
                            concentrations[tmp1][y][z] = concentrations[tmp2][y][z];
                        }
                    }
                }
                break;
            }
        }
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
        
    }

    void NormalMoleculeBehavior::InitializeMolecules(
        [[maybe_unused]] const MoleculeField* sender,
        MoleculeInitializationArgs args
    )
    {
        switch (args.DistributionType) {
            case InitialMoleculeDistribution::Centered:
            {
                if (GridCountX() & 1) {
                    
                }
                else {

                }
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