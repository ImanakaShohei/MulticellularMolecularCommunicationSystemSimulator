#include "NaiveAlgorithm.hpp"

Generator<CellInfo> NaiveAlgorithm::iterateAffectableCellInfos(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<UserMoleculeSpace*>&)
{
    for (Cell* pCell : cells) {
        if (pCell == &c) continue;
        
        co_yield CellInfo(*pCell);
    }
}

::std::vector<CellInfo> NaiveAlgorithm::getAffectableCellInfos(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<UserMoleculeSpace*>&)
{
    ::std::vector<CellInfo> list;
    list.reserve(cells.size());

    for (Cell* pCell : cells) {
        if (pCell == &c) continue;

        list.emplace_back(*pCell);
    }

    return list;
}