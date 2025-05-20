#pragma once

#include "CellSimulationModel.hpp"

class MassRotationModel : public CellSimulationModel {
    public:

    constexpr MassRotationModel(CellAlgorithm& cellAlgorithm) noexcept : CellSimulationModel(cellAlgorithm) {}

    Vec3 calcCellForce(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;
};