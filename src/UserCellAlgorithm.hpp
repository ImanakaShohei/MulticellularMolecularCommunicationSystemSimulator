#pragma once

#include "core/CellAlgorithm.hpp"

class UserCellAlgorithm : public CellAlgorithm {
    private:
    public:

    UserCellAlgorithm() = default;

    Vec3 calcCellForce(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;
    void beforeNextStep(const ::std::vector<UserCell*>& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;
    void onNextStep(const ::std::vector<UserCell*>& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;
};