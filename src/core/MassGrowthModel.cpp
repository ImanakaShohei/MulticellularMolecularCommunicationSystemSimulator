#include "MassGrowthModel.hpp"
#include <numbers>

MassGrowthModel::MassGrowthModel(CellAlgorithm& cellAlgorithm)
    : CellSimulationModel(cellAlgorithm)
    , m_bondMatrix(SimulationSettings::CELL_NUM, ::std::vector<bool>(SimulationSettings::CELL_NUM, false))
{
}

void MassGrowthModel::initCells(::std::vector<UserCell*>& cells)
{
    std::mt19937 rand_gen{ (uint32_t)SimulationSettings::CELL_SEED }; //!< 乱数生成器(生成器はとりあえずメルセンヌ・ツイスタ)

    std::uniform_real_distribution<double> rand_r(0, 150);
    std::uniform_real_distribution<double> rand_theta(0, 2 * ::std::numbers::pi);

    for (int32_t i = 0; i != SimulationSettings::CELL_NUM; i++) {
        double r = rand_r(rand_gen);
        double theta = rand_theta(rand_gen);
        double x = r * std::cos(theta);
        double y = r * std::sin(theta);

        cells.push_back(new UserCell(CellType::WORKER, x, y, 10));
    }
}

Vec3 MassGrowthModel::calcCellForce(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) 
{
    Vec3 force = Vec3::zero();
    
    for (auto pCell : cells) {
        UserCell& cell = *pCell;
        if (c.id == cell.id) continue;

        const Vec3 diff = c.getPosition()- cell.getPosition();
        const double dist = diff.length();
        if (m_bondMatrix[c.id][cell.id]) {
            if (c.adhereCellsCount() <= 3) {
                force += diff.timesScalar((s_dMax - dist) * 2.0 / (s_dMax * dist));
            }
            else {
                force -= diff.timesScalar(std::max(0.0, (dist- s_dMin) / (s_dMax- s_dMin)) * 2.0 / dist);
            }
        }

        force -= diff.timesScalar(std::exp(-dist / s_lambda) * 0.05 / dist);
        if (dist < s_dCont) {
            force += diff.timesScalar((s_dCont- dist) * 10.0 / (s_dCont * dist));
        }
    }

    return force.timesScalar(SimulationSettings::DELTA_TIME);
}

void MassGrowthModel::beforeNextStep(::std::vector<UserCell*>& cells, ::std::vector<UserMoleculeSpace*>&)
{
    size_t preCellCount = cells.size();

    for (auto&& pCell : cells) {
        pCell->initForce();
    }

    for (size_t i = 0; i != preCellCount; i++) {
        for (size_t j = 0; j != preCellCount; j++) {
            if (j == i) continue;

            UserCell& celli = *cells[i];
            UserCell& cellj = *cells[j];

            const Vec3 diff = celli.getPosition() - cellj.getPosition();
            const double dist = diff.length();

            auto&& ref = m_bondMatrix[i][j];

            if (dist < s_dCont) {
                ref = true;
            }
            // ここでdist >= s_dCont
            else if (dist > s_dMax && ref) {
                ref = false;
            }
            // (s_dCont <= dist) && (dist <= s_dMax || !m_bondMatrix[i][j]) の時は何もしない

            if (ref) celli.adhere(cellj);
        }
    }
    
}