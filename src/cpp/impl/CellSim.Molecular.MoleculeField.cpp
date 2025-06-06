#include "CellSim.Molecular.MoleculeField.hpp"

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
}