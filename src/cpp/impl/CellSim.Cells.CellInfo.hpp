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
        bool IsAlive;
        double Mass;
        Numerics::Vector3 Position;
        Numerics::Vector3 PreviusForce;
        double Radius;
        CellType Type;

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
        , IsAlive(isAlive)
        , Position(position)
        , PreviusForce(previusForce)
        , Radius(radius)
        , Type(type)
    {
    }

    constexpr CellInfo::CellInfo(Cell const& cell) noexcept
        : CellPtr(&cell)
        , Mass(cell.Mass())
        , IsAlive(cell.IsAlive())
        , Position(cell.Position())
        , PreviusForce(cell.PreviusForce())
        , Radius(cell.Radius())
        , Type(cell.Type())
    {
    }
}

#endif //!CELLSIM_CELLS_CELLINFO_HPP