#ifndef CELLSIM_MOLECULAR_NULLMOLECULEBEAVIOR_HPP
#define CELLSIM_MOLECULAR_NULLMOLECULEBEAVIOR_HPP

#include "base.hpp"
#include "CellSim.Molecular.MoleculeBehavior.hpp"
#include "CellSim.Molecular.MoleculeBehaviorStepArgs.hpp"
#include "CellSim.Molecular.MoleculeDiffusionArgs.hpp"
#include "CellSim.Molecular.MoleculeInitializationArgs.hpp"
#include "CellSim.Containers.Span3.hpp"

namespace CellSim::Molecular
{
    /// @brief 何もしない分子拡散
    class NullMoleculeBehavior : public MoleculeBehavior {
        private:

        using MoleculeBehavior::MoleculeBehavior;

        constexpr void BeforeAdvanceStep(
            const MoleculeField* sender,
            MoleculeBehaviorStepArgs args
        ) override;

        constexpr void Diffuse(
            const MoleculeField* sender,
            MoleculeDiffusionArgs args
        ) override;

        constexpr void InitializeMolecules(
            const MoleculeField* sender,
            MoleculeInitializationArgs args
        ) override;

        constexpr void OnAdvanceStep(
            const MoleculeField* sender,
            MoleculeBehaviorStepArgs args
        ) override;
    };
}

namespace CellSim::Molecular
{
    constexpr void NullMoleculeBehavior::BeforeAdvanceStep(
            const MoleculeField*,
            MoleculeBehaviorStepArgs
    )
    {
    }

    constexpr void NullMoleculeBehavior::Diffuse(
            const MoleculeField*,
            MoleculeDiffusionArgs
    )
    {
    }

    constexpr void NullMoleculeBehavior::InitializeMolecules(
            const MoleculeField*,
            MoleculeInitializationArgs
    )
    {
    }

    constexpr void NullMoleculeBehavior::OnAdvanceStep(
            const MoleculeField*,
            MoleculeBehaviorStepArgs
    )
    {
    }
}

#endif //!CELLSIM_MOLECULAR_NULLMOLECULEBEAVIOR_HPP