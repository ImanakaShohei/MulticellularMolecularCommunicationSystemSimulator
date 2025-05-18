#pragma once

#include "ClusterFormationModel.hpp"

class NetworkFormationModel : public ClusterFormationModel {
    
    public:

    constexpr NetworkFormationModel(CellAlgorithm& cellArgorithm) noexcept : ClusterFormationModel(cellArgorithm) {}

    Vec3 calcCellForce(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;

    void onNextStep(::std::vector<UserCell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;
};