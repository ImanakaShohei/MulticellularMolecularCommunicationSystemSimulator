#include "CellSim.Molecular.MoleculeBehavior.hpp"
#include "CellSim.Molecular.MoleculeBehaviorKind.hpp"
#include "CellSim.Molecular.NormalMoleculeBehavior.hpp"
#include "CellSim.Molecular.NullMoleculeBehavior.hpp"
#include "CellSim.Settings.Config.Molecular.hpp"
#include "../CellSim.Users.UserMoleculeBehavior.hpp"
#include <stdexcept>

namespace CellSim::Molecular
{
    MoleculeBehavior::MoleculeBehavior() noexcept
    {
    }

    MoleculeBehavior::~MoleculeBehavior()
    {
        if (m_diffusionDeltaBuffer == nullptr) return;

        delete[] m_diffusionDeltaBuffer;
    }

    MoleculeBehavior& MoleculeBehavior::operator=(MoleculeBehavior&& right) noexcept
    {
        if (m_diffusionDeltaBuffer != nullptr) delete[] m_diffusionDeltaBuffer;

        m_diffusionDeltaBuffer = right.m_diffusionDeltaBuffer;

        right.m_diffusionDeltaBuffer = nullptr;

        return *this;
    }

    void MoleculeBehavior::SetBuffer(
        size_t gridCount,
        bool enable2dMode,
        ::CellSim::Molecular::BoundaryCondition boundaryCondition
    )
    {
        m_boundaryCondition = boundaryCondition;

        if (enable2dMode) {
            m_diffusionDeltaBuffer = new double[gridCount * gridCount];

            m_concentrations = Containers::Span3<double>(
                gridCount,
                gridCount,
                1,
                m_diffusionDeltaBuffer
            );

            m_enable2dMode = true;
            m_gridCountX = m_gridCountY = gridCount;
            m_gridCountZ = 1;
        }
        else {
            m_diffusionDeltaBuffer = new double[gridCount * gridCount * gridCount];

            m_concentrations = Containers::Span3<double>(
                gridCount,
                gridCount,
                gridCount,
                m_diffusionDeltaBuffer
            );

            m_gridCountX = m_gridCountY = m_gridCountZ = gridCount;
            m_enable2dMode = false;
        }
    }
}