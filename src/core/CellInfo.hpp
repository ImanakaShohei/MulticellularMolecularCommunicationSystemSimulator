#pragma once

#include "../utils/Vec3.hpp"
#include "Cell.hpp"
#include "../CellType.hpp"

struct CellInfo {

    CellInfo() = default;
    constexpr CellInfo(Vec3 const& vec, double weight, double radius, CellType type) noexcept;
    constexpr CellInfo(Cell& cell) noexcept;

    Vec3 position;
    double weight;
    double radius;
    CellType cellType;
    Cell* pCell;
};

constexpr CellInfo::CellInfo(Vec3 const& vec, double weight, double radius, CellType type) noexcept
    : position(vec)
    , weight(weight)
    , radius(radius)
    , cellType(type)
    , pCell(nullptr)
{
}

constexpr CellInfo::CellInfo(Cell& cell) noexcept
    : position(cell.getPosition())
    , weight(cell.getWeight())
    , radius(cell.getRadius())
    , cellType(cell.getCellType())
    , pCell(&cell)
{
}