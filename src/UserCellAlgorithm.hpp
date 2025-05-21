#pragma once

#include "core/CellAlgorithm.hpp"

class UserCellAlgorithm : public CellAlgorithm {
    private:
    public:

    UserCellAlgorithm() = default;

    void beforeNextStep(const ::std::vector<Cell*>& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces) override;
    void onNextStep(const ::std::vector<Cell*>& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces) override;

    Generator<CellInfo> iterateAffectableCellInfos(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces) override;
    ::std::vector<CellInfo> getAffectableCellInfos(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces) override;
};