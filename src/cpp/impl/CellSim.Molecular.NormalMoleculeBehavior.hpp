#ifndef CELLSIM_MOLECULAR_NORMALMOLECULEBEAVIOR_HPP
#define CELLSIM_MOLECULAR_NORMALMOLECULEBEAVIOR_HPP

#include "base.hpp"
#include "CellSim.Molecular.MoleculeBehavior.hpp"
#include "CellSim.Containers.Span3.hpp"

namespace CellSim::Molecular
{
    class NormalMoleculeBehavior : public MoleculeBehavior {
        private:

        double m_computeDiffuse(
            Containers::Span3<double> concentrations,
            double reverseCo,
            size_t x,
            size_t y,
            size_t z
        ) const noexcept;

        ::CellSim::Molecular::BoundaryCondition m_boundaryCondition;
        double m_diffusionFactor;

        protected:

        /// @brief 境界条件に応じて境界部分を更新
        void m_applyBoundaryConditions(bool enable2dMode, Containers::Span3<double> concentrations);

        public:

        NormalMoleculeBehavior();
        NormalMoleculeBehavior(::CellSim::Molecular::BoundaryCondition boundaryCondition);
        NormalMoleculeBehavior(double diffusionFactor);
        NormalMoleculeBehavior(
            ::CellSim::Molecular::BoundaryCondition boundaryCondition,
            double diffusionFactor
        );

        void BeforeAdvanceStep(
            const MoleculeField* sender,
            MoleculeBehaviorStepArgs args
        ) override;

        /// @brief 拡散係数
        [[nodiscard]] constexpr double DiffusionFactor() const noexcept;

        void Diffuse(
            const MoleculeField* sender,
            MoleculeDiffusionArgs args
        ) override;

        void InitializeMolecules(
            const MoleculeField* sender,
            MoleculeInitializationArgs args
        ) override;

        void OnAdvanceStep(
            const MoleculeField* sender,
            MoleculeBehaviorStepArgs args
        ) override;
    };
}

namespace CellSim::Molecular
{
    constexpr double NormalMoleculeBehavior::DiffusionFactor() const noexcept
    {
        return m_diffusionFactor;
    }
}

#endif //!CELLSIM_MOLECULAR_NORMALMOLECULEBEAVIOR_HPP