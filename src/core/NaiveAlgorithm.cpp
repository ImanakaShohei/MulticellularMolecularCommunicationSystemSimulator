#include "NaiveAlgorithm.hpp"
#include "Simulation.hpp"

Vec3 NaiveAlgorithm::calcCellForce(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>&) noexcept
{
    Vec3 vec;
    UserCell const& target = c;

    switch (target.getCellType()) {
        case CellType::WORKER:
        {
            for (auto&& p : cells) {
                if (p == &target) continue;
        
                UserCell& cell = *p;
        
                if (cell.getCellType() != CellType::WORKER) continue;
        
                vec += Simulation::calcRemoteForce(c, cell);
            }
            vec = vec.normalize();

            for (auto&& p : cells) {
                if (p == &target) continue;
        
                UserCell& cell = *p;
        
                if (cell.getCellType() == CellType::NONE) continue;
        
                vec += Simulation::calcVolumeExclusion(c, cell);
            }
            break;
        }
        case CellType::DEAD:
        {
            for (auto&& p : cells) {
                if (p == &target) continue;
        
                UserCell& cell = *p;
        
                if (cell.getCellType() == CellType::NONE) continue;
        
                vec += Simulation::calcVolumeExclusion(c, cell);
            }
            break;
        }
        case CellType::NONE: return vec;
        default: break;
    }

    return vec.timesScalar(SimulationSettings::DELTA_TIME);
}