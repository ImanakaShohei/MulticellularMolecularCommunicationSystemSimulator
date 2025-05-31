#include "CellSim.Simulation.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"
#include "CellSim.Model.CellSimulationModel.hpp"
#include "CellSim.Threading.ThreadPool.hpp"

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
        m_pCellSimulationModel->BeforeNextStep(m_cells, m_molecules);
        if (m_pCellSimulationModel->UseCellAlgorithm()) m_pCellAlgorithm->BeforeNextStep(m_cells, m_molecules);

        // 力を加える
        Threading::ThreadPool::ParallelFor(
            0,
            m_cells.size(),
            [this] (size_t i) {
                auto& cell = m_cells[i];
                cell.AddForce(m_pCellSimulationModel->ComputeForceOnCell(cell, m_cells, m_molecules, *m_pCellAlgorithm));
            }
        );

        m_pCellSimulationModel->OnNextStep(m_cells, m_molecules);
        if (m_pCellSimulationModel->UseCellAlgorithm()) m_pCellAlgorithm->OnNextStep(m_cells, m_molecules);
        
    }

    Simulation::Simulation()
    : m_cells()
    , m_molecules()
    , m_pCellAlgorithm(s_createAlgorithm())
    , m_pCellList(nullptr)
    , m_pCellSimulationModel()
    {

    }
}