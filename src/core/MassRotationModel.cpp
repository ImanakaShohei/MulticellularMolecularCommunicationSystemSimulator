#include "MassRotationModel.hpp"
#include "../SimulationSettings.hpp"

Vec3 MassRotationModel::calcCellForce(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces)
{
    Vec3 force = Vec3::zero();
    const Vec3 center = Vec3(0, 0, 0);
    const Vec3 diff_from_center = c.getPosition();
    Vec3 force_cont = Vec3::zero();
    CellInfo info = CellInfo(c);
    const Vec3 velocity = c.getVelocity();

    constexpr double COEFFICIENT = 1.0;
    constexpr double REPUlSION_C = 0.20;
    constexpr double REPULSION_LEN = 15;
    constexpr double BONDING_LEN = 5;

    force -= diff_from_center.timesScalar(COEFFICIENT / diff_from_center.length());

    auto f = [] (CellInfo info, CellInfo cellInfo, Vec3& force, Vec3& force_cont, Vec3 velocity) {
        const Vec3 diff = info.position - cellInfo.position;
        const double dist = diff.length();

        if (dist < REPULSION_LEN) {
            force += diff.timesScalar(REPUlSION_C * (REPULSION_LEN - dist) / (REPULSION_LEN * dist));
        }

        if (dist < BONDING_LEN) {
            force_cont += velocity;
        }
    };

    switch (SimulationSettings::PERFORMANCE) {
        case PerformanceKind::HighPerformance:
        {
            for (auto cellInfo : m_cellAlgorithm.getAffectableCellInfos(c, cells, moleculeSpaces)) {
                f(info, cellInfo, force, force_cont, velocity);
            }
            break;
        }
        case PerformanceKind::LowMemory:
        {
            for (auto cellInfo : m_cellAlgorithm.iterateAffectableCellInfos(c, cells, moleculeSpaces)) {
                f(info, cellInfo, force, force_cont, velocity);
            }
            break;
        }
    }

    if (force_cont != Vec3::zero()) force += force_cont.timesScalar(0.2 / force_cont.length());
    
    return force.timesScalar(SimulationSettings::DELTA_TIME);
}