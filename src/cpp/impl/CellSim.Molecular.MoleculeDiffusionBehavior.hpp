#ifndef CELLSIM_MOLECULE_MOLECULEDIFFUSIONBEAVIOR_HPP
#define CELLSIM_MOLECULE_MOLECULEDIFFUSIONBEAVIOR_HPP

#include "base.hpp"
#include "CellSim.Molecular.BoundaryCondition.hpp"

#include <vector>

namespace CellSim::Molecular
{
    /// @brief 分子拡散のふるまい
    class MoleculeDiffusionBehavior {
        private:

        ::CellSim::Molecular::BoundaryCondition m_boundaryCondition;

        public:

        MoleculeDiffusionBehavior() noexcept;
        constexpr MoleculeDiffusionBehavior(::CellSim::Molecular::BoundaryCondition boundaryCondition) noexcept;

        /// @brief 種類から作成
        /// @param kind 種類
        /// @return インスタンス
        [[nodiscard]] static MoleculeDiffusionBehavior* FromKind(MoleculeDiffusionBehaviorKind kind, ::CellSim::Molecular::BoundaryCondition condition);

        virtual void BeforeAdvanceStep(
            ::std::vector<Cells::Cell> const& cells,
            MoleculeField const& field
        ) = 0;

        [[nodiscard]] constexpr ::CellSim::Molecular::BoundaryCondition BoundaryCondition() const noexcept;

        virtual void Diffuse(
            Containers::Span3<double> concentrations,
            MoleculeField const& field
        ) = 0;

        virtual void InitializeMolecules(
            InitialMoleculeDistribution initialMoleculeDistribution,
            Containers::Span3<double> concentrations,
            MoleculeField const& field
        ) = 0;

        virtual void OnAdvanceStep(
            ::std::vector<Cells::Cell> const& cells,
            MoleculeField const& field
        ) = 0;
    };
}

namespace CellSim::Molecular
{
    constexpr MoleculeDiffusionBehavior::MoleculeDiffusionBehavior(::CellSim::Molecular::BoundaryCondition boundaryCondition) noexcept
        : m_boundaryCondition(boundaryCondition)
    {
    }

    constexpr ::CellSim::Molecular::BoundaryCondition MoleculeDiffusionBehavior::BoundaryCondition() const noexcept
    {
        return m_boundaryCondition;
    }
}

#endif //!CELLSIM_MOLECULE_MOLECULEDIFFUSIONBEAVIOR_HPP