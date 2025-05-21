#pragma once

#include "ClusterFormationModel.hpp"

class NetworkFormationModel : public ClusterFormationModel {
    
    public:

    constexpr NetworkFormationModel(CellAlgorithm& cellArgorithm) noexcept : ClusterFormationModel(cellArgorithm) {}

    Vec3 calcCellForce(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces) override;

    void onNextStep(::std::vector<Cell*>& cells, ::std::vector<MoleculeSpace*>& moleculeSpaces) override;
};