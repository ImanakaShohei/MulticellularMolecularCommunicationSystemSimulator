#include "CellSim.Cells.NormalCellBehavior.hpp"
#include "CellSim.Cells.Cell.hpp"
#include "CellSim.Cells.CellGrowthResult.hpp"
#include "CellSim.Settings.Config.Cell.hpp"
#include "CellSim.Settings.Config.Simulation.hpp"

namespace CellSim::Cells
{
    CellGrowthResult NormalCellBehavior::ComputeGrowth(Cell const& cell) const
    {
        double oldRadius = cell.Radius();
        double newRadius = oldRadius + Settings::Config::Cell::GrowthRate() * Settings::Config::Simulation::DeltaTime();

        double tmp = newRadius / oldRadius;

        double newMass = tmp * tmp * tmp * cell.Mass();

        return CellGrowthResult{ newMass, newRadius };
    }
}