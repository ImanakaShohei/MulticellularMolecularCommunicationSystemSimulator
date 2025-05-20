#include "NaiveAlgorithm.hpp"

Generator<CellInfo> NaiveAlgorithm::iterateAffectableCellInfos(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>&)
{
    for (UserCell* pCell : cells) {
        if (pCell == &c) continue;
        
        co_yield CellInfo(*pCell);
    }
}

::std::vector<CellInfo> NaiveAlgorithm::getAffectableCellInfos(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>&)
{
    ::std::vector<CellInfo> list;
    list.reserve(cells.size());

    for (UserCell* pCell : cells) {
        if (pCell == &c) continue;

        list.emplace_back(*pCell);
    }

    return list;
}