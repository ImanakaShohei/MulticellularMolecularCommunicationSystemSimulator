#include "NetworkFormationModel.hpp"

Vec3 NetworkFormationModel::calcCellForce(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpace)
{
    Vec3 force = Vec3::zero();
    for (auto pCell : cells) {
        if (&c == pCell) continue;

        UserCell& cell = *pCell;

        if (c.isAdhere(pCell)) {
            const Vec3 diff = c.getPosition() - cell.getPosition();
            const double dist = diff.length();

            constexpr double co = 3.0 / (s_dMax - s_dMin);

            double v = dist - s_dMin;

            if (v > 0.0) {
                force -= diff.timesScalar(v * co / dist);
            }
            else {
                v = s_dEx - dist;

                if (v > 0.0) {
                    force += diff.timesScalar(v * 3.0 / (s_dEx * dist));
                }
            }
            
        }
    }
    return force.timesScalar(SimulationSettings::DELTA_TIME) + CellSimulationModel::calcCellForce(c, cells, moleculeSpace);
}

void NetworkFormationModel::onNextStep(::std::vector<UserCell*>& cells, ::std::vector<UserMoleculeSpace*>&)
{
    const size_t cellsLength = cells.size();

    for (size_t i = 0; i != cellsLength; i++) {
        UserCell& cell = *cells[i];

        if (cell.getCellType() != CellType::WORKER) continue;

        cell.clearAdhereCells();

        for (size_t j = i + 1; j != cellsLength; j++) {

            UserCell& cell1 = *cells[j];

            if (cell1.getCellType() != CellType::WORKER) continue;

            const Vec3 diff = cell.getPosition() - cell1.getPosition();
            const double dist = diff.length();

            if (dist < s_dMax) {
                cell.adhere(cell1);
                cell1.adhere(cell);
            }
        }
    }
}