#include "CellAlgorithm.hpp"

::std::vector<CellInfo> CellAlgorithm::getAffectableCellInfos(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces)
{
    ::std::vector<CellInfo> list;
    for (CellInfo info : iterateAffectableCellInfos(c, cells, moleculeSpaces)) {
        list.push_back(info);
    }

    return list;
}