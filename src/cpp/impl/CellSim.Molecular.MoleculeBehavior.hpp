#ifndef CELLSIM_MOLECULAR_MOLECULEBEAVIOR_HPP
#define CELLSIM_MOLECULAR_MOLECULEBEAVIOR_HPP

#include "base.hpp"
#include "CellSim.Molecular.BoundaryCondition.hpp"
#include "CellSim.Containers.Span3.hpp"

#include <vector>
#include <nlohmann/json_fwd.hpp>

namespace CellSim::Molecular
{
    /// @brief 分子拡散のふるまい
    class MoleculeBehavior {
        private:

        ::CellSim::Molecular::BoundaryCondition m_boundaryCondition;
        Containers::Span3<double> m_concentrations;
        double* m_diffusionDeltaBuffer;
        bool m_enable2dMode;

        size_t m_gridCountX;
        size_t m_gridCountY;
        size_t m_gridCountZ;

        public:

        MoleculeBehavior() noexcept;
        MoleculeBehavior(MoleculeBehavior const&) = delete;
        constexpr MoleculeBehavior(MoleculeBehavior&& right) noexcept;

        virtual ~MoleculeBehavior();

        MoleculeBehavior& operator=(MoleculeBehavior const&) = delete;
        MoleculeBehavior& operator=(MoleculeBehavior&& right) noexcept;

        /// @brief 種類から作成
        /// @param kind 種類
        /// @return インスタンス
        [[nodiscard]] static MoleculeBehavior* FromKind(MoleculeBehaviorKind kind);

        [[nodiscard]] static MoleculeBehavior* FromJson(::nlohmann::json const& j);

        virtual void BeforeAdvanceStep(
            const MoleculeField* sender,
            MoleculeBehaviorStepArgs args
        ) = 0;

        [[nodiscard]] constexpr ::CellSim::Molecular::BoundaryCondition BoundaryCondition() const noexcept;

        [[nodiscard]] constexpr Containers::Span3<double> Concentrations() noexcept;

        [[nodiscard]] constexpr bool Enable2dMode() const noexcept;

        [[nodiscard]] constexpr size_t GridCount() const noexcept;
        
        /// @brief 境界を含むX方向のグリッドの数
        [[nodiscard]] constexpr size_t GridCountX() const noexcept;

        /// @brief 境界を含むY方向のグリッドの数
        [[nodiscard]] constexpr size_t GridCountY() const noexcept;

        /// @brief 境界を含むZ方向のグリッドの数
        [[nodiscard]] constexpr size_t GridCountZ() const noexcept;

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

        void SetBuffer(size_t gridCount, bool enable2dMode, ::CellSim::Molecular::BoundaryCondition boundaryCondition);
    };
}

namespace CellSim::Molecular
{
    constexpr MoleculeBehavior::MoleculeBehavior(MoleculeBehavior&& right) noexcept
        : m_boundaryCondition(right.m_boundaryCondition)
        , m_diffusionDeltaBuffer(right.m_diffusionDeltaBuffer)
    {
        right.m_diffusionDeltaBuffer = nullptr;
    }

    constexpr ::CellSim::Molecular::BoundaryCondition MoleculeBehavior::BoundaryCondition() const noexcept
    {
        return m_boundaryCondition;
    }

    constexpr Containers::Span3<double> MoleculeBehavior::Concentrations() noexcept
    {
        return m_concentrations;
    }

    constexpr bool MoleculeBehavior::Enable2dMode() const noexcept
    {
        return m_enable2dMode;
    }

    constexpr size_t MoleculeBehavior::GridCount() const noexcept
    {
        return m_gridCountX;
    }

    constexpr size_t MoleculeBehavior::GridCountX() const noexcept
    {
        return m_gridCountX;
    }

    constexpr size_t MoleculeBehavior::GridCountY() const noexcept
    {
        return m_gridCountY;
    }

    constexpr size_t MoleculeBehavior::GridCountZ() const noexcept
    {
        return m_gridCountZ;
    }
    
}

#endif //!CELLSIM_MOLECULAR_MOLECULEBEAVIOR_HPP