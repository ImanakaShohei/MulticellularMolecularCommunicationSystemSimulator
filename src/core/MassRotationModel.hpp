#pragma once

#include "CellSimulationModel.hpp"
#include <vector>

class MassRotationModel : public CellSimulationModel {
    private:

    double m_adhesionDistanceThreshold; // 細胞同士がこの値より近いと接着力が働く
    double m_adhesionForceFactor; // 接着力にかける係数
    double m_centralForceFactor; // 中心力にかける係数
    double m_repulsionFactor; // 反発力の係数
    double m_repulsionMaxDistance; // 細胞同士がこの値より近いと反発する

    public:

    MassRotationModel(CellAlgorithm& cellAlgorithm) noexcept;

    Vec3 calcCellForce(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces) override;
};