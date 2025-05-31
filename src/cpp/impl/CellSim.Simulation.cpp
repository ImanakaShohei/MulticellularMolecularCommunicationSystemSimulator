#include "CellSim.Simulation.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"

namespace CellSim
{
    CellAlgorithms::CellAlgorithm* Simulation::s_createAlgorithm()
    {

    }

    void Simulation::m_beforeNextStep()
    {

    }

    void Simulation::m_nextstep()
    {
        m_beforeNextStep();
        m_pCellAlgorithm->BeforeNextStep(m_cells, m_molecules);

        m_pCellAlgorithm->OnNextStep(m_cells, m_molecules);
    }

    Simulation::Simulation()
    : m_cells()
    , m_molecules()
    , m_pCellAlgorithm(s_createAlgorithm())
    , m_pCellList(nullptr)
    , m_pSimulationModel()
    {

    }
}