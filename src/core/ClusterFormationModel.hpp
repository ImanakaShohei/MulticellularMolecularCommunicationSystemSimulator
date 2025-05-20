#pragma once

#include "CellSimulationModel.hpp"

/// @brief クラスタ形成モデル
class ClusterFormationModel : public CellSimulationModel {

    private:

    static Vec3 calcRemoteForce(CellInfo target, CellInfo cell) noexcept;
    static Vec3 calcVolumeExclusion(CellInfo target, CellInfo cell) noexcept;

    public:

    constexpr ClusterFormationModel(CellAlgorithm& cellAlgorithm) noexcept : CellSimulationModel(cellAlgorithm) {}
    
    Vec3 calcCellForce(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;
};