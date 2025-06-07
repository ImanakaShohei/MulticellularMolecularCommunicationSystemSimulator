#ifndef CELLSIM_MOLECULE_BOUNDARYCONDITION_HPP
#define CELLSIM_MOLECULE_BOUNDARYCONDITION_HPP

#include "base.hpp"

namespace CellSim::Molecular
{
    /// @brief 境界条件
    enum class BoundaryCondition {
        Reflective,  // Neumann条件：壁のように跳ね返る（反射境界）
        Absorbing,   // Dirichlet条件：境界で吸収される（吸収境界）
        Periodic     // PBC条件：反対側に回り込む（周期境界）
    };
}

#endif //!CELLSIM_MOLECULE_BOUNDARYCONDITION_HPP