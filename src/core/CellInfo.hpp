#pragma once

#include "../utils/Vec3.hpp"
#include "Cell.hpp"
#include "../CellType.hpp"

struct CellInfo {

    CellInfo() = default;
    constexpr CellInfo(Vec3 const& vec, Vec3 const& previusAddedForce, double weight, double radius, CellType type) noexcept;
    constexpr CellInfo(Cell& cell) noexcept;

    constexpr void update() noexcept;

    Vec3 position;
    Vec3 previusAddedForce;
    double weight;
    double radius;
    CellType cellType;
    Cell* pCell;
};

constexpr CellInfo::CellInfo(Vec3 const& vec, Vec3 const& previusAddedForce, double weight, double radius, CellType type) noexcept
    : position(vec)
    , previusAddedForce(previusAddedForce)
    , weight(weight)
    , radius(radius)
    , cellType(type)
    , pCell(nullptr)
{
}

constexpr CellInfo::CellInfo(Cell& cell) noexcept
    : position(cell.getPosition())
    , previusAddedForce(cell.getPreviusAddedForce())
    , weight(cell.getWeight())
    , radius(cell.getRadius())
    , cellType(cell.getCellType())
    , pCell(&cell)
{
}

constexpr void CellInfo::update() noexcept
{
    if (pCell == nullptr) return;
    
    position = pCell->getPosition();
    previusAddedForce = pCell->getPreviusAddedForce();
    weight = pCell->getWeight();
    radius = pCell->getRadius();
    cellType = pCell->getCellType();
}