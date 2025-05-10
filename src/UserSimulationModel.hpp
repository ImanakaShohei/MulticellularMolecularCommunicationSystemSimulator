#pragma once

#include "core/CellSimulationModel.hpp"

class UserSimulationModel : public CellSimulationModel {
    public:

    constexpr UserSimulationModel(CellAlgorithm& cellAlgorithm) noexcept : CellSimulationModel(cellAlgorithm) {}

    void initCells(::std::vector<UserCell*>& cells) override;

    Vec3 calcCellForce(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;

    void beforeNextStep(::std::vector<UserCell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;
    void onNextStep(::std::vector<UserCell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;
};