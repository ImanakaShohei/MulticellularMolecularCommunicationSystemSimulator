#include "MassGrowthModel.hpp"
#include "NormalCell.hpp"
#include <numbers>

#include "../SimulationSettings.hpp"

MassGrowthModel::MassGrowthModel(CellAlgorithm& cellArgorithm) noexcept
    : CellSimulationModel(cellArgorithm)
    , m_adhesionThreshold(SimulationSettings::MG_ADHESIONTHRESHOLD)
    , m_coefficientCd(SimulationSettings::MG_COEFFICIENT_CD)
    , m_contactDistance(SimulationSettings::MG_CONTACT_DISTANCE)
    , m_followerAttractionFactor(SimulationSettings::MG_FOLLOWER_ATTRACTION_FACTOR)
    , m_globalAttractionFactor(SimulationSettings::MG_GLOBAL_ATTRACTION_FACTOR)
    , m_leaderRepulsionFactor(SimulationSettings::MG_LEADER_REPULSION_FACTOR)
    , m_leaderRepulsionMaxDistance(SimulationSettings::MG_LEADER_REPULSION_MAX_DISTANCE)
    , m_leaderRepulsionMinDistance(SimulationSettings::MG_LEADER_REPULSION_MIN_DISTANCE)
    , m_leaderRepulsionRange(SimulationSettings::MG_LEADER_REPULSION_MAX_DISTANCE - SimulationSettings::MG_LEADER_REPULSION_MIN_DISTANCE)
    , m_lambda(SimulationSettings::LAMBDA)
{
    if (SimulationSettings::USE_CLUSTER_MODEL) {
        ::std::cerr << "In this simulation model, 'use_cluster_model' must be set to false." << ::std::endl;
        exit(1);
    }
}

void MassGrowthModel::initCells(::std::vector<Cell*>& cells)
{
    std::mt19937 rand_gen{ (uint32_t)SimulationSettings::CELL_SEED }; //!< 乱数生成器(生成器はとりあえずメルセンヌ・ツイスタ)

    std::uniform_real_distribution<double> rand_theta(0, 2.0 * ::std::numbers::pi);
    std::uniform_real_distribution<double> rand_r(0, 1.0);

    for (int32_t i = 0; i != SimulationSettings::CELL_NUM; i++) {
        double r = ::sqrt(rand_r(rand_gen)) * SimulationSettings::MG_INITIAL_RADIUS;
        double theta = rand_theta(rand_gen);
        double x = r * std::cos(theta);
        double y = r * std::sin(theta);

        cells.push_back(new NormalCell(CellType::WORKER, x, y, 10));
    }
}

Vec3 MassGrowthModel::calcCellForce(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces) 
{
    Vec3 force = Vec3::zero();
    CellInfo info = CellInfo(c);
    
    for (auto pCell : cells) {
        if (&c == pCell) continue;
        Cell& cell = *pCell;

        const Vec3 diff = info.position - cell.getPosition();
        const double dist = diff.length();

        if (c.isAdhere(pCell)) {
            if (c.adhereCellsCount() <= m_adhesionThreshold) {
                // 接着している細胞から離れようとする
                // ここで
                force += diff.timesScalar((m_leaderRepulsionMaxDistance - dist) * m_leaderRepulsionFactor / (m_leaderRepulsionMaxDistance * dist));
            }
            else {
                double v = dist - m_leaderRepulsionMinDistance;

                // 近すぎると何も起こらない
                if (v > 0.0) {
                    force -= diff.timesScalar(v * m_followerAttractionFactor / (dist * m_leaderRepulsionRange));
                }
            }
        }

        // 近すぎると反発力が発生
        if (dist < m_contactDistance) {
            force += diff.timesScalar((m_contactDistance - dist) * m_coefficientCd / (m_contactDistance * dist));
        }
    }

    auto f = [] (CellInfo info, CellInfo cellInfo, Vec3& force, double lambda, double globalAttractionFactor) {
        const Vec3 diff = info.position - cellInfo.position;
        const double dist = diff.length();

        // すべての細胞に働く力
        force -= diff.timesScalar(std::exp(-dist / lambda) * globalAttractionFactor / dist);
    };
    
    switch (SimulationSettings::PERFORMANCE) {
        case PerformanceKind::HighPerformance:
        {
            for (CellInfo cellInfo : m_cellAlgorithm.getAffectableCellInfos(c, cells, moleculeSpaces)) {
                f(info, cellInfo, force, m_lambda, m_globalAttractionFactor);
            }
            break;
        }
        case PerformanceKind::LowMemory:
        {
            for (CellInfo cellInfo : m_cellAlgorithm.iterateAffectableCellInfos(c, cells, moleculeSpaces)) {
                f(info, cellInfo, force, m_lambda, m_globalAttractionFactor);
            }
            break;
        }
    }

    return force.timesScalar(SimulationSettings::DELTA_TIME);
}

void MassGrowthModel::beforeNextStep(::std::vector<Cell*>& cells, ::std::vector<MoleculeSpace*>&)
{
    const size_t cellsLength = cells.size();

    for (Cell* pCell : cells) {
        pCell->clearAdhereCells();
    }

    for (size_t i = 0; i != cellsLength; i++) {
        Cell& cell = *cells[i];

        if (cell.getCellType() != CellType::WORKER) continue;
        
        for (size_t j = i + 1; j != cellsLength; j++) {

            Cell& cell1 = *cells[j];

            if (cell1.getCellType() != CellType::WORKER) continue;

            const Vec3 diff = cell.getPosition() - cell1.getPosition();
            const double dist = diff.length();

            if (dist < m_contactDistance) {
                cell.adhere(cell1);
                cell1.adhere(cell);
            }
        }
    }
    
}