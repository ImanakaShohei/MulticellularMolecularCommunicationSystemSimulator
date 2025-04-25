#include "Cluster.hpp"
#include "Simulation.hpp"

Vec3 Cluster::calcCellForce(const ::std::shared_ptr<UserCell>& c, ::std::vector<::std::shared_ptr<UserCell>> const& cells, const ::std::vector<::std::unique_ptr<UserMoleculeSpace>>&) noexcept
{
    Vec3 vec;
    UserCell& target = *c;

    switch (target.getCellType()) {
        case CellType::WORKER:
        {
            for (auto&& p : cells) {
                if (p == c) continue;
        
                UserCell& cell = *p;
        
                if (cell.getCellType() == CellType::WORKER) continue;

                const Vec3 diff              = target.getPosition() - cell.getPosition();
                const double dist            = diff.length();
                const double weight          = cell.getWeight() * target.getWeight();
        
                vec -= diff.normalize().timesScalar(weight * std::exp(-dist * SimulationSettings::CLUSTER_REVERSE_LAMBDA));
            }
            vec = vec.normalize();

            for (auto&& p : cells) {
                if (p == c) continue;
        
                UserCell& cell = *p;
        
                if (cell.getCellType() == CellType::NONE) continue;
        
                vec += Simulation::calcVolumeExclusion(c, p);
            }
            break;
        }
        case CellType::DEAD:
        {
            for (auto&& p : cells) {
                if (p == c) continue;
        
                UserCell& cell = *p;
        
                if (cell.getCellType() == CellType::NONE) continue;
        
                vec += Simulation::calcVolumeExclusion(c, p);
            }
            break;
        }
        default: break;
    }

    return vec.timesScalar(SimulationSettings::DELTA_TIME);
}

void Cluster::beforeNextStep(const ::std::vector<::std::shared_ptr<UserCell>>& cells, const ::std::vector<::std::unique_ptr<UserMoleculeSpace>>&)
{
    size_t length = cells.size();
    //細胞同士が十分に近ければくっついたと判定する
    for (size_t i = 0; i < length; ++i) {
        UserCell& cell = *cells[i];
        switch (cell.getCellType()) {
            case CellType::WORKER:
            {
                for (size_t j = i + 1; j < length; j++) {

                    UserCell& cellr = *cells[j];

                    if (cellr.getCellType() != CellType::WORKER) continue;
        
                    //
                    double radius = cell.getRadius() + cellr.getRadius();
        
                    //距離 < 細胞半径 + 細胞半径 でくっつく
                    //高速化のため、２乗で計算
                    if ((cell.getPosition() - cellr.getPosition()).squareLength() < radius * radius) {
                        cell.combine(cellr);
                        continue;
                    }
                }
                break;
            }

            default: break;
        }
        
    }
}