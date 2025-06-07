#ifndef CELLSIM_MOLECULE_NORMALMOLECULEDIFFUSIONBEAVIOR_HPP
#define CELLSIM_MOLECULE_NORMALMOLECULEDIFFUSIONBEAVIOR_HPP

#include "base.hpp"
#include "CellSim.Molecular.MoleculeDiffusionBehavior.hpp"
#include "CellSim.Containers.Span3.hpp"

namespace CellSim::Molecular
{
    class NormalMoleculeDiffusionBehavior : public MoleculeDiffusionBehavior {
        private:

        double m_computeDiffuse(
            Containers::Span3<double> concentrations,
            double reverseCo,
            size_t x,
            size_t y,
            size_t z
        ) const noexcept;

        double m_diffusionFactor;

        public:

        NormalMoleculeDiffusionBehavior();
        NormalMoleculeDiffusionBehavior(::CellSim::Molecular::BoundaryCondition boundaryCondition);
        NormalMoleculeDiffusionBehavior(double diffusionFactor);
        NormalMoleculeDiffusionBehavior(
            ::CellSim::Molecular::BoundaryCondition boundaryCondition,
            double diffusionFactor
        );

        void BeforeAdvanceStep(
            ::std::vector<Cells::Cell> const& cells,
            Molecular::MoleculeField const& field
        ) override;

        /// @brief 拡散係数
        [[nodiscard]] constexpr double DiffusionFactor() const noexcept;

        void Diffuse(
            Containers::Span3<double> concentrations,
            Molecular::MoleculeField const& field
        ) override;

        void InitializeMolecules(
            InitialMoleculeDistribution initialMoleculeDistribution,
            Containers::Span3<double> concentrations,
            MoleculeField const& field
        ) override;

        void OnAdvanceStep(
            ::std::vector<Cells::Cell> const& cells,
            Molecular::MoleculeField const& field
        ) override;
    };
}

namespace CellSim::Molecular
{
    constexpr double NormalMoleculeDiffusionBehavior::DiffusionFactor() const noexcept
    {
        return m_diffusionFactor;
    }
}

#endif //!CELLSIM_MOLECULE_NORMALMOLECULEDIFFUSIONBEAVIOR_HPP