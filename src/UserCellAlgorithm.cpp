#include "UserCellAlgorithm.hpp"

void UserCellAlgorithm::beforeNextStep([[maybe_unused]] const ::std::vector<Cell*>& cells, [[maybe_unused]] const ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    // TODO: ここに処理を追加します
}

void UserCellAlgorithm::onNextStep([[maybe_unused]] const ::std::vector<Cell*>& cells, [[maybe_unused]] const ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    // TODO: ここに処理を追加します
}

Generator<CellInfo> UserCellAlgorithm::iterateAffectableCellInfos([[maybe_unused]] Cell& c, [[maybe_unused]] ::std::vector<Cell*> const& cells, [[maybe_unused]] const ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    // TODO: ここに処理を追加します
    co_return;
}

::std::vector<CellInfo> UserCellAlgorithm::getAffectableCellInfos(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    // TODO: 最適コードに置き換えます

    ::std::vector<CellInfo> list;
    for (CellInfo info : iterateAffectableCellInfos(c, cells, moleculeSpaces)) {
        list.push_back(info);
    }

    return list;
}