#pragma once

#include "core/CellSimulationModel.hpp"

class UserSimulationModel : public CellSimulationModel {
    public:

    constexpr UserSimulationModel(CellAlgorithm& cellAlgorithm) noexcept : CellSimulationModel(cellAlgorithm) {}

    void initCells(::std::vector<Cell*>& cells) override;

    Vec3 calcCellForce(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces) override;

    void beforeNextStep(::std::vector<Cell*>& cells, ::std::vector<MoleculeSpace*>& moleculeSpaces) override;
    void onNextStep(::std::vector<Cell*>& cells, ::std::vector<MoleculeSpace*>& moleculeSpaces) override;
};