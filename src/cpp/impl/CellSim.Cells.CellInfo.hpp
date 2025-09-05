#ifndef CELLSIM_CELLS_CELLINFO_HPP
#define CELLSIM_CELLS_CELLINFO_HPP

#include "base.hpp"
#include "CellSim.Cells.Cell.hpp"
#include "CellSim.Cells.CellType.hpp"

namespace CellSim::Cells
{
    /// @brief 細胞の情報
    struct CellInfo {
        public:
        /// @brief 参照元のCellインスタンス
        /// @note 参照元がない場合はnullptr
        const Cell* CellPtr;

        /// @brief 質量
        double Mass;

        /// @brief 位置
        Numerics::Vector3 Position;

        /// @brief 1ステップ前に加えられた力
        Numerics::Vector3 PreviusForce;

        /// @brief 半径
        double Radius;

        /// @brief 細胞の種類
        CellType Type;

        /// @brief 生きているかどうか
        bool IsAlive;

        CellInfo() = default;
        
        constexpr CellInfo(
            double mass,
            bool isAlive,
            Numerics::Vector3 position,
            Numerics::Vector3 previusForce,
            double radius,
            CellType type
        ) noexcept;
        constexpr CellInfo(Cell const& cell) noexcept;
    };
}

namespace CellSim::Cells
{
    constexpr CellInfo::CellInfo(
        double mass,
        bool isAlive,
        Numerics::Vector3 position,
        Numerics::Vector3 previusForce,
        double radius,
        CellType type
    ) noexcept
        : CellPtr(nullptr)
        , Mass(mass)
        , Position(position)
        , PreviusForce(previusForce)
        , Radius(radius)
        , Type(type)
        , IsAlive(isAlive)
    {
    }

    constexpr CellInfo::CellInfo(Cell const& cell) noexcept
        : CellPtr(&cell)
        , Mass(cell.Mass())
        , Position(cell.Position())
        , PreviusForce(cell.PreviusForce())
        , Radius(cell.Radius())
        , Type(cell.Type())
        , IsAlive(cell.IsAlive())
    {
    }
}

#endif //!CELLSIM_CELLS_CELLINFO_HPP