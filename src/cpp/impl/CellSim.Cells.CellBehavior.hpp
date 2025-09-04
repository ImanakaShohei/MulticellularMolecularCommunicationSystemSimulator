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

        virtual ~CellBehavior() = default;

        constexpr void AddOwner() noexcept;

        /// @brief 細胞の成長度合いを計算
        /// @param sender この関数を呼び出した細胞インスタンス
        /// @return 計算結果
        [[nodiscard]] virtual CellGrowthResult ComputeGrowth(
            const Cell* sender
        ) = 0;

        /// @brief 細胞内外の分子の状態を更新
        /// @param sender この関数を呼んだ細胞インスタンス
        /// @param args 処理に必要な情報
        /// @return 計算結果
        [[nodiscard]] virtual MolecularProcessResult ComputeMolecularProcess(
            const Cell* sender,
            MolecularProcessArgs args
        ) = 0;

        [[nodiscard]] virtual CellBehavior* CreateClone() const = 0;

        /// @brief 細胞分裂後の細胞の状態を定義
        /// @param sender この関数を呼び出した細胞インスタンス
        /// @return 分裂後の2つの細胞の状態
        [[nodiscard]] virtual CellDivisionResult ComputeDivisionOutcome(
            const Cell* sender
        ) = 0;

        [[nodiscard]] constexpr bool HasOwner() const noexcept;

        /// @brief インスタンスを使いまわせるかどうか
        [[nodiscard]] virtual bool IsReusable() const noexcept = 0;

        /// @brief Cell.SenseMolecules()から呼ばれる関数
        /// @param sender この関数を呼び出した細胞インスタンス
        /// @param args 処理に必要な情報
        /// @return 分子から受ける力
        virtual Numerics::Vector3 OnSenseMolecules(
            const Cell* sender,
            CellMoleculeSensingArgs args
        ) = 0;

        constexpr void RemoveOwner() noexcept;

        /// @brief このステップで細胞が分裂するかを定義
        /// @param sender この関数を呼び出した細胞インスタンス
        /// @return 細胞が分裂するかどうか
        [[nodiscard]] virtual bool ShouldDivideThisStep(
            const Cell* sender
        ) noexcept = 0;
        
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