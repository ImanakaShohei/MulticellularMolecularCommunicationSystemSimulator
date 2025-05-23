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
    Vec3 previusVelocity;
    double weight;
    double radius;
    CellType cellType;
    Cell* pCell;
};

constexpr CellInfo::CellInfo(Vec3 const& vec, Vec3 const& previusVelocity, double weight, double radius, CellType type) noexcept
    : position(vec)
    , previusVelocity(previusVelocity)
    , weight(weight)
    , radius(radius)
    , cellType(type)
    , pCell(nullptr)
{
}

constexpr CellInfo::CellInfo(Cell& cell) noexcept
    : position(cell.getPosition())
    , previusVelocity(cell.getPreviusVelocity())
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
    previusVelocity = pCell->getPreviusVelocity();
    weight = pCell->getWeight();
    radius = pCell->getRadius();
    cellType = pCell->getCellType();
}