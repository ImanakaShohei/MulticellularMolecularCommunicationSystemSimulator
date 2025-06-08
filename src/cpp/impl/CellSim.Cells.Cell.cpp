#include "CellSim.Cells.Cell.hpp"
#include "CellSim.Cells.CellGrowthResult.hpp"
#include "CellSim.Molecular.MoleculeField.hpp"

#include <stdexcept>

namespace CellSim::Cells
{
    constinit uint32_t Cell::s_id = 0;

    Cell::Cell(
        CellType type,
        CellBehaviorPtr const& pBehavior,
        double mass,
        double radius,
        Numerics::Vector3 position
    )
        : m_attachedCells()
        , m_behaviorPtr(pBehavior)
        , m_force()
        , m_id(s_id)
        , m_internalMolecules()
        , m_isAlive(true)
        , m_mass(mass)
        , m_polarity()
        , m_previusForce()
        , m_radius(radius)
        , m_type(type)
    {
        if (mass <= 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'mass' must be greater than zero.");
        if (radius <= 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'radius' must be greater than zero.");

        ++s_id;
    }

    void Cell::EmitMolecule(Molecular::MoleculeField& field)
    {
        Numerics::GridPosition3 position3 = field.ToGridPosition3(m_position);

        field.Concentrations().At(position3.X, position3.Y, position3.Z) += m_behaviorPtr->ComputeMoleculeEmitAmount(*this, field);
    }

    void Cell::Grow()
    {
        CellGrowthResult result = m_behaviorPtr->ComputeGrowth(*this);

        m_radius = result.NewRadius;
        m_mass = result.NewMass;
    }
}