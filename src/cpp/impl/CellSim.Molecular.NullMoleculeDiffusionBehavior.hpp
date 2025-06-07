#ifndef CELLSIM_MOLECULE_NULLMOLECULEDIFFUSIONBEAVIOR_HPP
#define CELLSIM_MOLECULE_NULLMOLECULEDIFFUSIONBEAVIOR_HPP

#include "base.hpp"
#include "CellSim.Molecular.MoleculeDiffusionBehavior.hpp"
#include "CellSim.Molecular.InitialMoleculeDistribution.hpp"
#include "CellSim.Containers.Span3.hpp"

namespace CellSim::Molecular
{
    /// @brief 何もしない分子拡散
    class NullMoleculeDiffusionBehavior : public MoleculeDiffusionBehavior {
        private:

        using MoleculeDiffusionBehavior::MoleculeDiffusionBehavior;

        constexpr void BeforeAdvanceStep(
            ::std::vector<Cells::Cell> const& cells,
            Molecular::MoleculeField const& field
        ) override;

        constexpr void Diffuse(
            Containers::Span3<double> concentrations,
            Molecular::MoleculeField const& field
        ) override;

        constexpr void InitializeMolecules(
            InitialMoleculeDistribution initialMoleculeDistribution,
            Containers::Span3<double> concentrations,
            MoleculeField const& field
        ) override;

        constexpr void OnAdvanceStep(
            ::std::vector<Cells::Cell> const& cells,
            Molecular::MoleculeField const& field
        ) override;
    };
}

namespace CellSim::Molecular
{
    constexpr void NullMoleculeDiffusionBehavior::BeforeAdvanceStep(
        ::std::vector<Cells::Cell> const&,
        Molecular::MoleculeField const&
    )
    {
    }

    constexpr void NullMoleculeDiffusionBehavior::Diffuse(
        Containers::Span3<double>,
        Molecular::MoleculeField const&
    )
    {
    }

    constexpr void NullMoleculeDiffusionBehavior::InitializeMolecules(
        InitialMoleculeDistribution,
        Containers::Span3<double>,
        Molecular::MoleculeField const&
    )
    {
    }

    constexpr void NullMoleculeDiffusionBehavior::OnAdvanceStep(
        ::std::vector<Cells::Cell> const&,
        Molecular::MoleculeField const&
    )
    {
    }
}

#endif //!CELLSIM_MOLECULE_NULLMOLECULEDIFFUSIONBEAVIOR_HPP