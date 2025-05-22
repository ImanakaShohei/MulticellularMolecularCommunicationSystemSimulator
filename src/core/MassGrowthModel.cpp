#include "MassGrowthModel.hpp"
#include "NormalCell.hpp"
#include <numbers>

#include "../SimulationSettings.hpp"

void MassGrowthModel::initCells(::std::vector<Cell*>& cells)
{
    constexpr double maxRadius = 150.0;
    std::mt19937 rand_gen{ (uint32_t)SimulationSettings::CELL_SEED }; //!< 乱数生成器(生成器はとりあえずメルセンヌ・ツイスタ)

    std::uniform_real_distribution<double> rand_theta(0, 2.0 * ::std::numbers::pi);
    std::uniform_real_distribution<double> rand_r(0, maxRadius);

    for (int32_t i = 0; i != SimulationSettings::CELL_NUM; i++) {
        double r = ::sqrt(rand_r(rand_gen));
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
            if (c.adhereCellsCount() <= 3) {
                // 接着している細胞から離れようとする
                force += diff.timesScalar((s_dMax - dist) * 2.0 / (s_dMax * dist));
            }
            else {
                double v = (dist - s_dMin) / (s_dMax - s_dMin);

                if (v > 0.0) {
                    force -= diff.timesScalar(v * 2.0 / dist);
                }
            }
        }

        if (dist < s_dCont) {
            force += diff.timesScalar((s_dCont - dist) * 10.0 / (s_dCont * dist));
        }
    }

    auto f = [] (CellInfo info, CellInfo cellInfo, Vec3& force) {
        const Vec3 diff = info.position - cellInfo.position;
        const double dist = diff.length();

        // すべての細胞に働く力
        force -= diff.timesScalar(std::exp(-dist / s_lambda) * 0.05 / dist);
    };
    
    switch (SimulationSettings::PERFORMANCE) {
        case PerformanceKind::HighPerformance:
        {
            for (CellInfo cellInfo : m_cellAlgorithm.getAffectableCellInfos(c, cells, moleculeSpaces)) {
                f(info, cellInfo, force);
            }
            break;
        }
        case PerformanceKind::LowMemory:
        {
            for (CellInfo cellInfo : m_cellAlgorithm.iterateAffectableCellInfos(c, cells, moleculeSpaces)) {
                f(info, cellInfo, force);
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

            if (dist < SimulationSettings::NF_MAX_ATTRACTION_DISTANCE) {
                cell.adhere(cell1);
                cell1.adhere(cell);
            }
        }
    }
    
}