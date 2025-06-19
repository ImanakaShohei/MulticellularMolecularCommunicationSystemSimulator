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
        const Cell* CellPtr;
        double Mass;
        Numerics::Vector3 Position;
        Numerics::Vector3 PreviusForce;
        double Radius;
        CellType Type;
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