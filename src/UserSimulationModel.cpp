#include "UserSimulationModel.hpp"

void UserSimulationModel::initCells(::std::vector<Cell*>& cells)
{
    // TODO: ユーザー独自の処理に変更
    CellSimulationModel::initCells(cells);
}

Vec3 UserSimulationModel::calcCellForce(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    // TODO: ユーザー独自の処理に変更
    return Vec3::zero();
}

void UserSimulationModel::beforeNextStep(::std::vector<Cell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    // TODO: ユーザー独自の処理に変更
    CellSimulationModel::beforeNextStep(cells, moleculeSpaces);
}

void UserSimulationModel::onNextStep(::std::vector<Cell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    // TODO: ユーザー独自の処理に変更
    CellSimulationModel::onNextStep(cells, moleculeSpaces);
}