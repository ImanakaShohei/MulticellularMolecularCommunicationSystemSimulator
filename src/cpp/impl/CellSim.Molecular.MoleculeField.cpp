#include "CellSim.Molecular.MoleculeField.hpp"
#include "CellSim.Molecular.MoleculeDiffusionBehavior.hpp"
#include "CellSim.Settings.Config.Simulation.hpp"

#include <stdexcept>

namespace CellSim::Molecular
{
    MoleculeField::MoleculeField(
        size_t gridCountX,
        size_t gridCountY,
        size_t gridCountZ,
        MoleculeKind kind,
        MoleculeDiffusionBehavior* pBehavior
    )
        : m_concentrations()
        , m_pConcentration(new double[gridCountX * gridCountY * gridCountZ])
        , m_gridCountX(gridCountX)
        , m_gridCountY(gridCountY)
        , m_gridCountZ(gridCountZ)
        , m_gridLengthX(Settings::Config::Simulation::FieldRadiusX() * 2.0 / gridCountX)
        , m_gridLengthY(Settings::Config::Simulation::FieldRadiusY() * 2.0 / gridCountY)
        , m_gridLengthZ(Settings::Config::Simulation::FieldRadiusZ() * 2.0 / gridCountZ)
        , m_reverseGridLengthX(1.0 / m_gridLengthX)
        , m_reverseGridLengthY(1.0 / m_gridLengthY)
        , m_reverseGridLengthZ(1.0 / m_gridLengthZ)
        , m_kind(kind)
        , m_pBehavior(pBehavior)
    {
        m_concentrations = Containers::Span3<double>(gridCountX, gridCountY, gridCountZ, m_pConcentration);

        if (pBehavior == nullptr) [[unlikely]] throw ::std::invalid_argument("MoleculeDiffusionBehavior* is nullptr.");
    }

    MoleculeField::~MoleculeField()
    {
        if (m_pConcentration == nullptr) return;

        delete[] m_pConcentration;
        delete m_pBehavior;
    }

    void MoleculeField::BeforeAdvanceStep(::std::vector<Cells::Cell> const& cells)
    {
        m_pBehavior->BeforeAdvanceStep(cells, *this);
    }

    void MoleculeField::Diffuse()
    {
        m_pBehavior->Diffuse(m_concentrations, *this);
    }

    void MoleculeField::OnAdvanceStep(::std::vector<Cells::Cell> const& cells)
    {
        m_pBehavior->OnAdvanceStep(cells, *this);
    }

    Numerics::GridPosition3 MoleculeField::ToGridPosition3(Numerics::Vector3 position) const noexcept
    {
        double x = position.X + Settings::Config::Simulation::FieldRadiusX();

        double y = position.Y + Settings::Config::Simulation::FieldRadiusY();

        double z = position.Z + Settings::Config::Simulation::FieldRadiusZ();

        return Numerics::GridPosition3(
            (size_t)((position.X + Settings::Config::Simulation::FieldRadiusX()) * m_reverseGridLengthX),
            (size_t)((position.Y + Settings::Config::Simulation::FieldRadiusY()) * m_reverseGridLengthY),
            (size_t)((position.Z + Settings::Config::Simulation::FieldRadiusZ()) * m_reverseGridLengthZ)
        );
    }
}