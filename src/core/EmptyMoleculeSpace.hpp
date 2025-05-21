#pragma once

#include "MoleculeSpace.hpp"

/// @brief 何もしない分子空間
class EmptyMoleculeSpace : public MoleculeSpace {
    public:
    
    EmptyMoleculeSpace() = default;

    constexpr void calcConcentrationDiff() noexcept override {}
    constexpr void nextStep() noexcept override {}

    constexpr double getMoleculeNum(Vec3 pos) const noexcept override;

    void print(::std::ostream& out) const noexcept override;
};

constexpr double EmptyMoleculeSpace::getMoleculeNum(Vec3) const noexcept
{
    return 0.0;
}