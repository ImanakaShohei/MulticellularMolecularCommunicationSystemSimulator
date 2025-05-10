#include "UserCellAlgorithm.hpp"

Vec3 UserCellAlgorithm::calcCellForce([[maybe_unused]] UserCell& c, [[maybe_unused]] ::std::vector<UserCell*> const& cells, [[maybe_unused]] const ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    // TODO: ここに処理を追加します
    return Vec3::zero();
}

void UserCellAlgorithm::beforeNextStep([[maybe_unused]] const ::std::vector<UserCell*>& cells, [[maybe_unused]] const ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    // TODO: ここに処理を追加します
}

void UserCellAlgorithm::onNextStep([[maybe_unused]] const ::std::vector<UserCell*>& cells, [[maybe_unused]] const ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    // TODO: ここに処理を追加します
}