#include "NaiveAlgorithm.hpp"
#include "Simulation.hpp"

Vec3 NaiveAlgorithm::calcCellForce(const ::std::shared_ptr<UserCell>& c, ::std::vector<::std::shared_ptr<UserCell>> const& cells, const ::std::vector<::std::unique_ptr<UserMoleculeSpace>>&) const noexcept
{
    Vec3 vec;
    UserCell& target = *c;

    switch (target.getCellType()) {
        case CellType::WORKER:
        {
            for (auto&& p : cells) {
                if (p == c) continue;
        
                UserCell& cell = *p;
        
                if (cell.getCellType() != CellType::WORKER) continue;
        
                vec += Simulation::calcRemoteForce(c, p);
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
        case CellType::NONE: return vec;
        default: break;
    }

    return vec.timesScalar(SimulationSettings::DELTA_TIME);
}