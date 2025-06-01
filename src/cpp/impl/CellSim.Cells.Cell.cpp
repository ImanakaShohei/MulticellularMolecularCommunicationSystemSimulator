#include "CellSim.Cells.Cell.hpp"
#include "CellSim.Cells.CellGrowthResult.hpp"

namespace CellSim::Cells
{
    constinit int32_t Cell::s_id = 0;

    void Cell::Grow()
    {
        CellGrowthResult result = m_behaviorPtr->ComputeGrowth(*this);

        m_radius = result.NewRadius;
        m_mass = result.NewMass;
    }
}