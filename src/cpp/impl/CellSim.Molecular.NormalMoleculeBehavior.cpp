#include "CellSim.Molecular.NormalMoleculeBehavior.hpp"
#include "CellSim.Molecular.MoleculeField.hpp"
#include "CellSim.Containers.Span3.hpp"
#include "CellSim.Numerics.Vector3T.hpp"
#include "CellSim.Molecular.MoleculeBehaviorStepArgs.hpp"
#include "CellSim.Molecular.MoleculeDiffusionArgs.hpp"
#include "CellSim.Molecular.MoleculeInitializationArgs.hpp"
#include "CellSim.Messages.hpp"
#include "CellSim.Settings.Config.Simulation.hpp"
#include "CellSim.Text.CString.hpp"

#include <numbers>
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
            ) *
            reverseCo
        ;
    }

    double NormalMoleculeBehavior::m_computeDiffuse2d(
        Containers::Span3<double> concentrations,
        double reverseCo,
        size_t x,
        size_t y
    ) const noexcept
    {
        return m_diffusionFactor *
            (
                concentrations[x + 1][y][0] + concentrations[x - 1][y][0] +
                concentrations[x][y + 1][0] + concentrations[x][y - 1][0] -
                4.0 * concentrations[x][y][0]
            ) *
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

    NormalMoleculeBehavior::NormalMoleculeBehavior(double diffusionFactor)
        : m_diffusionFactor(diffusionFactor)
    {
        if (diffusionFactor < 0) [[unlikely]] throw ::std::invalid_argument("diffusionFactor must be non-negative.");
    }

    void NormalMoleculeBehavior::BeforeAdvanceStep(
        [[maybe_unused]] const MoleculeField* sender,
        [[maybe_unused]] MoleculeBehaviorStepArgs args
    )
    {
        for (auto& v : Concentrations()) {
            v = 0;
        }
    }

    void NormalMoleculeBehavior::Diffuse(
        const MoleculeField* field,
        MoleculeDiffusionArgs args
    )
    {
        double reverseCo = 1.0 / (field->GridLength() * field->GridLength());
        size_t maxGridIndex = GridCountX() - 1; // 境界を除く
        if (Enable2dMode()) {
            for (size_t x = 1; x < maxGridIndex; x++) {
                auto span2 = Concentrations()[x];

                for (size_t y = 1; y < maxGridIndex; y++) {
                    span2.At(y, 0) += m_computeDiffuse2d(args.Concentrations, reverseCo, x, y);
                }
            }
        }
        else {
            for (size_t x = 1; x < maxGridIndex; x++) {
                auto span2 = Concentrations()[x];

                for (size_t y = 1; y < maxGridIndex; y++) {
                    auto span = span2[y];

                    for (size_t z = 1; z < maxGridIndex; z++) {
                        span[z] += m_computeDiffuse(args.Concentrations, reverseCo, x, y, z);
                    }
                }
            }
        }

        auto pDelta = Concentrations().begin();
        auto eDelta = Concentrations().end();
        auto pConcentration = args.Concentrations.begin();

        for (; pDelta != eDelta; ++pDelta, ++pConcentration) {
            *pConcentration += *pDelta * Settings::Config::Simulation::DeltaTime();
        }

        m_applyBoundaryConditions(args.Concentrations);
    }

    void NormalMoleculeBehavior::InitializeMolecules(
        const MoleculeField*,
        MoleculeInitializationArgs args
    )
    {
        if (args.MoleculeAmount == 0) return;
        
        switch (args.DistributionType) {
            case InitialMoleculeDistribution::Centered:
            {
                size_t index;
                // 奇数
                if (GridCount() & 1) {
                    index = GridCount() / 2 + 1;

                    args.Concentrations[index][index][Enable2dMode() ? 0 : index] = args.MoleculeAmount;
                }
                // 偶数
                else {
                    index = GridCount();
                    double moleculeAmount;
                    if (Enable2dMode()) {
                        moleculeAmount = args.MoleculeAmount / 4;
                        args.Concentrations[index][index][0] = moleculeAmount;
                        args.Concentrations[index][index + 1][0] = moleculeAmount;
                        args.Concentrations[index + 1][index][0] = moleculeAmount;
                        args.Concentrations[index + 1][index + 1][0] = moleculeAmount;
                    }
                    else {
                        moleculeAmount = args.MoleculeAmount / 8;
                        args.Concentrations[index][index][index] = moleculeAmount;
                        args.Concentrations[index][index][index + 1] = moleculeAmount;
                        args.Concentrations[index][index + 1][index] = moleculeAmount;
                        args.Concentrations[index][index + 1][index + 1] = moleculeAmount;
                        args.Concentrations[index + 1][index][index] = moleculeAmount;
                        args.Concentrations[index + 1][index][index + 1] = moleculeAmount;
                        args.Concentrations[index + 1][index + 1][index] = moleculeAmount;
                        args.Concentrations[index + 1][index + 1][index + 1] = moleculeAmount;
                    }
                }
                break;
            }
            case InitialMoleculeDistribution::Uniform:
            {
                // 境界部分は無視する
                
                size_t gridCount = GridCount() - 2;
                size_t end = GridCount() - 1;
                double moleculeAmount;

                if (Enable2dMode()) {
                    moleculeAmount = args.MoleculeAmount / (gridCount * gridCount);

                    for (size_t x = 1; x < end; x++) {
                        auto span2 = args.Concentrations[x];
                        for (size_t y = 1; y < end; y++) {
                            span2[y][0] = moleculeAmount;
                        }
                    }
                }
                else {
                    moleculeAmount = args.MoleculeAmount / (gridCount * gridCount * gridCount);

                    for (size_t x = 1; x < end; x++) {
                        auto span2 = args.Concentrations[x];
                        for (size_t y = 1; y < end; y++) {
                            auto span = span2[y];

                            for (size_t z = 1; z < end; z++) {
                                span[z] = moleculeAmount;
                            }
                        }
                    }
                }
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