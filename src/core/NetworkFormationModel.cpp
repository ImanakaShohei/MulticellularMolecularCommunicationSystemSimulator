#include "NetworkFormationModel.hpp"

Vec3 NetworkFormationModel::calcCellForce(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpace)
{
    static const double co = SimulationSettings::NF_COEFFICIENT / (SimulationSettings::NF_MAX_ATTRACTION_DISTANCE - SimulationSettings::NF_MIN_ATTRACTION_DISTANCE);

    Vec3 force = Vec3::zero();
    for (auto pCell : cells) {
        if (&c == pCell) continue;

        UserCell& cell = *pCell;

        if (c.isAdhere(pCell)) {
            const Vec3 diff = c.getPosition() - cell.getPosition();
            const double dist = diff.length();

            double v = dist - SimulationSettings::NF_MIN_ATTRACTION_DISTANCE;

            if (v > 0.0) {
                force -= diff.timesScalar(v * co / dist);
            }
            else {
                v = SimulationSettings::NF_MAX_REPULSION_DISTANCE - dist;

                if (v > 0.0) {
                    force += diff.timesScalar(v * SimulationSettings::NF_COEFFICIENT / (SimulationSettings::NF_MAX_REPULSION_DISTANCE * dist));
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

            if (dist < SimulationSettings::NF_MAX_ATTRACTION_DISTANCE) {
                cell.adhere(cell1);
                cell1.adhere(cell);
            }
        }
    }
}