#pragma once

#include "CellSimulationModel.hpp"

class MassRotationModel : public CellSimulationModel {
    public:

    constexpr MassRotationModel(CellAlgorithm& cellAlgorithm) noexcept : CellSimulationModel(cellAlgorithm) {}

    Vec3 calcCellForce(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;

    void beforeNextStep(::std::vector<UserCell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;
};