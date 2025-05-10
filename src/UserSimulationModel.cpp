#include "UserSimulationModel.hpp"

void UserSimulationModel::initCells(::std::vector<UserCell*>& cells)
{
    // TODO: ユーザー独自の処理に変更
    CellSimulationModel::initCells(cells);
}

Vec3 UserSimulationModel::calcCellForce(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    // TODO: ユーザー独自の処理に変更
    return CellSimulationModel::calcCellForce(c, cells, moleculeSpaces);
}

void UserSimulationModel::beforeNextStep(::std::vector<UserCell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    // TODO: ユーザー独自の処理に変更
    CellSimulationModel::beforeNextStep(cells, moleculeSpaces);
}

void UserSimulationModel::onNextStep(::std::vector<UserCell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    // TODO: ユーザー独自の処理に変更
    CellSimulationModel::onNextStep(cells, moleculeSpaces);
}