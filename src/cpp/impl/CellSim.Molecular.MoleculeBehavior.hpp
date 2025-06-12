#ifndef CELLSIM_MOLECULAR_MOLECULEBEAVIOR_HPP
#define CELLSIM_MOLECULAR_MOLECULEBEAVIOR_HPP

#include "base.hpp"
#include "CellSim.Molecular.BoundaryCondition.hpp"

#include <vector>

namespace CellSim::Molecular
{
    /// @brief 分子拡散のふるまい
    class MoleculeBehavior {
        private:

        ::CellSim::Molecular::BoundaryCondition m_boundaryCondition;

        public:

        MoleculeBehavior() noexcept;
        constexpr MoleculeBehavior(::CellSim::Molecular::BoundaryCondition boundaryCondition) noexcept;

        /// @brief 種類から作成
        /// @param kind 種類
        /// @return インスタンス
        [[nodiscard]] static MoleculeBehavior* FromKind(MoleculeBehaviorKind kind);

        /// @brief 種類から作成
        /// @param kind 種類
        /// @return インスタンス
        [[nodiscard]] static MoleculeBehavior* FromKind(MoleculeBehaviorKind kind, ::CellSim::Molecular::BoundaryCondition condition);

        virtual void BeforeAdvanceStep(
            const MoleculeField* sender,
            MoleculeBehaviorStepArgs args
        ) = 0;

        [[nodiscard]] constexpr ::CellSim::Molecular::BoundaryCondition BoundaryCondition() const noexcept;

        virtual void Diffuse(
            const MoleculeField* sender,
            MoleculeDiffusionArgs args
        ) = 0;

        virtual void InitializeMolecules(
            const MoleculeField* sender,
            MoleculeInitializationArgs args
        ) = 0;

        virtual void OnAdvanceStep(
            const MoleculeField* sender,
            MoleculeBehaviorStepArgs args
        ) = 0;
    };
}

namespace CellSim::Molecular
{
    constexpr MoleculeBehavior::MoleculeBehavior(::CellSim::Molecular::BoundaryCondition boundaryCondition) noexcept
        : m_boundaryCondition(boundaryCondition)
    {
    }

    constexpr ::CellSim::Molecular::BoundaryCondition MoleculeBehavior::BoundaryCondition() const noexcept
    {
        return m_boundaryCondition;
    }
}

#endif //!CELLSIM_MOLECULAR_MOLECULEBEAVIOR_HPP