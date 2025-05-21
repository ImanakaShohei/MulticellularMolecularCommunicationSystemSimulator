#pragma once

#include "Cell.hpp"
#include "../utils/Vec3.hpp"
#include "MoleculeSpace.hpp"
#include <vector>
#include "CellInfo.hpp"
#include "../threading/Generator.hpp"

class CellAlgorithm {
    private:

    protected:

    CellAlgorithm() = default;
    CellAlgorithm(CellAlgorithm const&) = default;
    CellAlgorithm(CellAlgorithm&&) = default;

    CellAlgorithm& operator=(CellAlgorithm const&) = default;
    CellAlgorithm& operator=(CellAlgorithm&&) = default;

    public:

    constexpr virtual ~CellAlgorithm() {}

    constexpr virtual void beforeNextStep(const ::std::vector<Cell*>&, const ::std::vector<MoleculeSpace*>&) {}
    constexpr virtual void onNextStep(const ::std::vector<Cell*>&, const ::std::vector<MoleculeSpace*>&) {}

    virtual Generator<CellInfo> iterateAffectableCellInfos(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces) = 0;
    virtual ::std::vector<CellInfo> getAffectableCellInfos(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces);
};