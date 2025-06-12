#ifndef CELLSIM_MOLECULAR_INITIALMOLECULEDISTRIBUTION_HPP
#define CELLSIM_MOLECULAR_INITIALMOLECULEDISTRIBUTION_HPP

#include "base.hpp"

namespace CellSim::Molecular
{
    /// @brief 分子の初期配置
    enum class InitialMoleculeDistribution {
        Centered,    // 中心に集中
        Gaussian,
        Uniform,     // 空間全体に均等に配置
    };
}

#endif //!CELLSIM_MOLECULE_INITIALMOLECULEDISTRIBUTION_HPP