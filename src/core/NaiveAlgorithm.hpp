#pragma once

#include "base.hpp"
#include "CellAlgorithm.hpp"
#include <vector>

class NaiveAlgorithm : public CellAlgorithm {
    public:

    Generator<CellInfo> iterateAffectableCellInfos(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces) override;
    ::std::vector<CellInfo> getAffectableCellInfos(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces) override;
};