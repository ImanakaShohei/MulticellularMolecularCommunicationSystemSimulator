#include "CellSim.Cells.Cell.hpp"
#include "CellSim.Cells.CellDivisionResult.hpp"
#include "CellSim.Cells.CellGrowthResult.hpp"
#include "CellSim.Messages.hpp"
#include "CellSim.Molecular.Molecule.hpp"
#include "CellSim.Molecular.MoleculeInfo.hpp"
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
        if (mass <= 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Cells.Cell.Cell.Error.mass"));
        if (radius <= 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Cells.Cell.Cell.Error.radius"));

        ++s_id;
    }

    bool Cell::ShouldDivideThisStep() const noexcept
    {
        return m_behaviorPtr->ShouldDivideThisStep();
    }

    void Cell::Combine(Cell& c) noexcept
    {
        m_radius = ::cbrt(m_radius * m_radius * m_radius + c.m_radius * c.m_radius * c.m_radius);
        m_position = (m_position * m_mass + c.m_position * c.m_mass) / (m_mass + c.m_mass);
        m_mass += c.m_mass;

        c.m_type = CellType::Invalid;
    }

    Cell Cell::Divide()
    {
        CellDivisionResult result = m_behaviorPtr->ComputeDivisionOutcome(this);

        m_mass = result.OriginalDaughter.NewMass;
        m_position = result.OriginalDaughter.NewPosition;
        m_radius = result.OriginalDaughter.NewRadius;

        return Cell(
            m_type,
            m_behaviorPtr,
            result.NewDaughter.NewMass,
            result.NewDaughter.NewRadius,
            result.NewDaughter.NewPosition
        );
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

    void Cell::Metabolize()
    {
        for (Molecular::Molecule& molecule : m_internalMolecules) {
            molecule.Amount(molecule.Amount() + m_behaviorPtr->ComputeMetabolicChange(this, { molecule.Amount(), molecule.Kind() }));
        }
    }
}