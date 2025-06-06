#ifndef CELLSIM_CELLS_CELLBEHAVIOR_HPP
#define CELLSIM_CELLS_CELLBEHAVIOR_HPP

#include "base.hpp"

namespace CellSim::Cells
{
    /// @brief 細胞のふるまい
    /// @attention このクラスはスレッドセーフではありません
    class CellBehavior {
        private:

        size_t m_ownerCount;

        public:
        
        constexpr CellBehavior() noexcept;

        constexpr void AddOwner() noexcept;

        /// @brief 細胞の成長度合いを計算
        /// @param cell ターゲットの細胞
        /// @return 計算結果
        [[nodiscard]] virtual CellGrowthResult ComputeGrowth(Cell const& cell) = 0;

        [[nodiscard]] virtual double ComputeMoleculeEmitAmount(Cell const& cell, Molecular::MoleculeField const& field) = 0;

        [[nodiscard]] virtual CellBehavior* CreateClone() const = 0;

        [[nodiscard]] constexpr bool HasOwner() const noexcept;

        /// @brief インスタンスが状態を持つかどうか
        [[nodiscard]] virtual bool HasState() const noexcept = 0;

        constexpr void RemoveOwner() noexcept;
    };
}

namespace CellSim::Cells
{
    constexpr CellBehavior::CellBehavior() noexcept
        : m_ownerCount(1)
    {
    }

    constexpr void CellBehavior::AddOwner() noexcept
    {
        ++m_ownerCount;
    }

    constexpr bool CellBehavior::HasOwner() const noexcept
    {
        return m_ownerCount != 0;
    }

    constexpr void CellBehavior::RemoveOwner() noexcept
    {
        --m_ownerCount;
    }
    
}

#endif //!CELLSIM_CELLS_CELLBEHAVIOR_HPP