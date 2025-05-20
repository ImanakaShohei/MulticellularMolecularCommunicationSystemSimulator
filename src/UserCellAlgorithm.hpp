#pragma once

#include "core/CellAlgorithm.hpp"

class UserCellAlgorithm : public CellAlgorithm {
    private:
    public:

    UserCellAlgorithm() = default;

    void beforeNextStep(const ::std::vector<UserCell*>& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;
    void onNextStep(const ::std::vector<UserCell*>& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;

    Generator<CellInfo> iterateAffectableCellInfos(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;
    ::std::vector<CellInfo> getAffectableCellInfos(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;
};