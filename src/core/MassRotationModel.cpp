#include "MassRotationModel.hpp"

void MassRotationModel::beforeNextStep(::std::vector<UserCell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    // すべての細胞の力を初期化する(速度を0に設定)
    for (auto pCell : cells) {
        pCell->initForce();
    }

    for (auto pCell : cells) {
        UserCell& c = *pCell;

        switch (c.getCellType()) {
            case CellType::DEAD:
            case CellType::NONE:
                break;

            default:
                c.metabolize();
                break;
        }
    }

    // 要素数の変更があるので連想for文は使わない
    for (uint32_t i = 0; i < cells.size(); i++) {
        UserCell& cell = *cells[i];

        switch (cell.getCellType()) {
            case CellType::DEAD:
            case CellType::NONE:
                break;

            default:
            {
                if (!cell.checkWillDivide()) break;
                
                UserCell* c = new UserCell(cell.divide());
                
                // 分裂した場合は配列に新しいCellを上書き(あるいは追加)する。
                if (c->arrayIndex >= (int32_t)cells.size()) {
                    cells.push_back(c);
                }
                else {
                    cells[c->arrayIndex] = c;
                }
                
                break;
            }
        }
    }

    CellSimulationModel::beforeNextStep(cells, moleculeSpaces);
}

Vec3 MassRotationModel::calcCellForce(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>&)
{
    Vec3 force = Vec3::zero();
    const Vec3 center = Vec3(0, 0, 0);
    const Vec3 diff_from_center = c.getPosition();
    Vec3 force_cont = Vec3::zero();

    constexpr double COEFFICIENT = 1.0;
    constexpr double REPUlSION_C = 0.20;
    constexpr double REPULSION_LEN = 15;
    constexpr double BONDING_LEN = 5;

    force -= diff_from_center.timesScalar(COEFFICIENT / diff_from_center.length());

    for (auto pCell : cells) {
        auto cell = *pCell;

        if (pCell == &c) continue;

        const Vec3 diff = c.getPosition() - cell.getPosition();
        const double dist = diff.length();

        if (dist < REPULSION_LEN) {
            force += diff.timesScalar(REPUlSION_C * (REPULSION_LEN - dist) / (REPULSION_LEN * dist));
        }

        if (dist < BONDING_LEN) {
            force_cont += cell.getVelocity();
        }
    }

    if (force_cont != Vec3::zero()) force += force_cont.timesScalar(0.2 / force_cont.length());
    
    return force.timesScalar(SimulationSettings::DELTA_TIME);
}