#include "NetworkFormationModel.hpp"

NetworkFormationModel::NetworkFormationModel(CellAlgorithm& cellArgorithm)
    : CellSimulationModel(cellArgorithm)
    , m_bondMatrix(SimulationSettings::CELL_NUM, ::std::vector<bool>(SimulationSettings::CELL_NUM, false))
{
}

Vec3 NetworkFormationModel::calcCellForce(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>&)
{
    Vec3 force = Vec3::zero();
    for (auto&& pCell : cells) {
        if (&c == pCell) continue;

        UserCell& cell = *pCell;

        const Vec3 diff = c.getPosition() - cell.getPosition();
        const double dist = diff.length();
        const double co = 30.0 / dist;
        force -= diff.timesScalar(std::exp(-dist / s_lambda) / dist);
        
        if (m_bondMatrix[c.id][cell.id]) {
            force -= diff.timesScalar(std::max((dist - s_dMin) / (s_dMax - s_dMin), 0.0) * co);
        }
        force += diff.timesScalar(std::max((s_dEx - dist) / s_dEx, 0.0) * co);
    }
    
    return force.timesScalar(SimulationSettings::DELTA_TIME);
}

void NetworkFormationModel::onNextStep(const ::std::vector<UserCell*>& cells, const ::std::vector<UserMoleculeSpace*>&)
{
    const size_t cellsLength = cells.size();

    for (size_t i = 0; i != cellsLength; i++) {
        UserCell& cell = *cells[i];

        cell.clearAdhereCells();

        for (size_t j = 0; j != cellsLength; j++) {
            if (i == j) continue;

            UserCell& cell1 = *cells[j];

            const Vec3 diff = cell.getPosition() - cell1.getPosition();
            const double dist = diff.length();

            auto&& ref = m_bondMatrix[i][j];

            if (dist < s_dMin) {
                ref = true;
            }
            // ここでdist >= s_dMin
            else if (dist > s_dMax && ref) {
                ref = false;
            }
            // (s_dMin <= dist) && (dist <= s_dMax || !m_bondMatrix[i][j]) の時は何もしない

            if (ref) cell.adhere(cell1);
        }
    }
}