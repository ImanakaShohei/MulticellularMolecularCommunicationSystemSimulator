#include "CellAlgorithm.hpp"

::std::vector<CellInfo> CellAlgorithm::getAffectableCellInfos(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    ::std::vector<CellInfo> list;
    for (CellInfo info : iterateAffectableCellInfos(c, cells, moleculeSpaces)) {
        list.push_back(info);
    }

    return list;
}