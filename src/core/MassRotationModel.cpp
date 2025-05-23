#include "MassRotationModel.hpp"
#include "../SimulationSettings.hpp"

MassRotationModel::MassRotationModel(CellAlgorithm& cellAlgorithm) noexcept
    : CellSimulationModel(cellAlgorithm)
    , m_adhesionDistanceThreshold(SimulationSettings::MR_ADHESION_DISTANCE_THRESHOLD)
    , m_adhesionForceFactor(SimulationSettings::MR_ADHESION_FORCE_FACTOR)
    , m_centralForceFactor(SimulationSettings::MR_CENTRAL_FORCE_FACTOR)
    , m_repulsionFactor(SimulationSettings::MR_REPULSION_FACTOR)
    , m_repulsionMaxDistance(SimulationSettings::MR_REPULSION_MAX_DISTANCE)
{
    #if 0
    if (SimulationSettings::CELL_GROWTH) {
        ::std::cerr << "In this simulation model, 'cell_growth' must be set to false." << ::std::endl;
        exit(1);
    }
    #endif
}

Vec3 MassRotationModel::calcCellForce(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces)
{
    Vec3 force = Vec3::zero();
    const Vec3 center = Vec3(0, 0, 0);
    const Vec3 diff_from_center = c.getPosition();
    Vec3 force_cont = Vec3::zero();
    CellInfo info = CellInfo(c);

    // 中心力
    force -= diff_from_center.timesScalar(m_centralForceFactor / diff_from_center.length());

    auto f = [] (
        CellInfo info,
        CellInfo cellInfo,
        Vec3& force,
        Vec3& force_cont,
        double adhesionForceFactor,
        double repulsionMaxDistance,
        double repulsionFactor,
        double adhesionDistanceThreshold
    )
    {
        const Vec3 diff = info.position - cellInfo.position;
        const double dist = diff.length();

        if (dist < repulsionMaxDistance) {
            force += diff.timesScalar(repulsionFactor * (repulsionMaxDistance - dist) / (repulsionMaxDistance * dist));
        }

        if (dist < adhesionDistanceThreshold) {
            force_cont += adhesionForceFactor * cellInfo.pCell->getPeriodAddedForce();
        }
    };

    switch (SimulationSettings::PERFORMANCE) {
        case PerformanceKind::HighPerformance:
        {
            for (auto cellInfo : m_cellAlgorithm.getAffectableCellInfos(c, cells, moleculeSpaces)) {
                f(
                    info,
                    cellInfo,
                    force,
                    force_cont,
                    m_adhesionForceFactor,
                    m_repulsionMaxDistance,
                    m_repulsionFactor,
                    m_adhesionDistanceThreshold
                );
            }
            break;
        }
        case PerformanceKind::LowMemory:
        {
            for (auto cellInfo : m_cellAlgorithm.iterateAffectableCellInfos(c, cells, moleculeSpaces)) {
                f(
                    info,
                    cellInfo,
                    force,
                    force_cont,
                    m_adhesionForceFactor,
                    m_repulsionMaxDistance,
                    m_repulsionFactor,
                    m_adhesionDistanceThreshold
                );
            }
            break;
        }
    }

    if (force_cont != Vec3::zero()) force += force_cont;
    
    return force.timesScalar(SimulationSettings::DELTA_TIME);
}