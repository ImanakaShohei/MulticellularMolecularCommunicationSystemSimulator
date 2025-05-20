#include "ClusterFormationModel.hpp"
#include "Simulation.hpp"

/**
 * @brief 与えられたCellに対して働く遠隔力を計算する。O(n^2)
 *
 * @param c
 * @return Vec3
 * @details @f{eqnarray*}{
 * F = \sum_i \frac{c(C - C_i)}{|C-C_i|}  *
 * e^{(-|C-C_i|/\lambda)}
 * @f}
 */
Vec3 ClusterFormationModel::calcRemoteForce(CellInfo const& target, CellInfo const& cell) noexcept
{
    const Vec3 diff              = target.position - cell.position;
    const double dist            = diff.length();

    if (dist == 0.0) [[unlikely]] return Vec3::zero();
    
    const double weight          = cell.weight * target.weight;

    return diff.timesScalar(-weight * std::exp(-dist * SimulationSettings::REVERSE_LAMBDA) / dist);
}

/**
 * @brief 与えられたCellに働く体積排除効果による力を計算する。O(n^2)
 *
 * @param c
 * @return Vec3
 * @details @f{eqnarray*}{
 * F = \sum_i
 * @f}
 */
Vec3 ClusterFormationModel::calcVolumeExclusion(CellInfo const& target, CellInfo const& cell) noexcept
{
    Vec3 force        = Vec3::zero();
    const Vec3 diff   = target.position - cell.position;
    const double dist = diff.length();
    // const double weight               = c2->getWeight() * c1->getWeight();
    const double sumRadius = target.radius + cell.radius;
    // const double overlapDist          = c1->getRadius() + c2->getRadius() - dist;
    constexpr double ELIMINATION_BIAS = 10.0;
    constexpr double ADHESION_BIAS    = 0.4;

    if (dist < sumRadius && dist != 0.0) {
        // force += diff.normalize().timesScalar(std::pow(1.8, overlapDist)).timesScalar(BIAS);

        //いのこくんによる最適化
        //force += diff.normalize().timesScalar(pow(1.0 - dist / sumRadius, 2) * ELIMINATION_BIAS);
        //force -= diff.normalize().timesScalar(pow(1.0 - dist / sumRadius, 2) * ADHESION_BIAS);

        force += diff.timesScalar(pow(1.0 - dist / sumRadius, 2) * (ELIMINATION_BIAS - ADHESION_BIAS) / dist);
    }

    return force;
}

Vec3 ClusterFormationModel::calcCellForce(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    Vec3 vec;
    CellInfo info = CellInfo(c);

    switch (info.cellType) {
        case CellType::WORKER:
        {
            auto list = m_cellAlgorithm.getAffectableCellInfos(c, cells, moleculeSpaces);
            for (auto cellInfo : list) {
        
                if (cellInfo.cellType != CellType::WORKER) continue;
        
                vec += calcRemoteForce(info, cellInfo);
            }
            vec = vec.normalize();

            for (auto cellInfo : list) {
        
                if (cellInfo.cellType == CellType::NONE) continue;
        
                vec += calcVolumeExclusion(info, cellInfo);
            }
            break;
        }
        case CellType::DEAD:
        {
            auto list = m_cellAlgorithm.getAffectableCellInfos(c, cells, moleculeSpaces);
            for (auto cellInfo : list) {
        
                if (cellInfo.cellType == CellType::NONE) continue;
        
                vec += calcVolumeExclusion(info, cellInfo);
            }
            break;
        }
        case CellType::NONE: return vec;
        default: break;
    }

    return vec.timesScalar(SimulationSettings::DELTA_TIME);
}