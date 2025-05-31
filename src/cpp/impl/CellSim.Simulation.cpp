#include "CellSim.Simulation.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"
#include "CellSim.Model.CellSimulationModel.hpp"
#include "CellSim.Threading.ThreadPool.hpp"

namespace CellSim
{
    CellAlgorithms::CellAlgorithm* Simulation::s_createAlgorithm()
    {

    }

    void Simulation::m_beforeAdvanceStep()
    {
        for (Cells::Cell& cell : m_cells) {
            cell.ResetForce();
        }


    }

    void Simulation::m_advanceStep()
    {
        // 前処理
        m_beforeAdvanceStep();
        m_pCellSimulationModel->BeforeAdvanceStep(m_cells, m_molecules);
        if (m_pCellSimulationModel->UseCellAlgorithm()) m_pCellAlgorithm->BeforeAdvanceStep(m_cells, m_molecules);

        // 力を加える
        Threading::ThreadPool::ParallelFor(
            0,
            m_cells.size(),
            [this] (size_t i) {
                Cells::Cell& cell = m_cells[i];
                cell.AddForce(m_pCellSimulationModel->ComputeForceOnCell(cell, m_cells, m_molecules, *m_pCellAlgorithm));
            }
        );

        // 移動
        for (Cells::Cell& cell : m_cells) {
            cell.Move();
        }

        m_pCellSimulationModel->OnAdvanceStep(m_cells, m_molecules);
        if (m_pCellSimulationModel->UseCellAlgorithm()) m_pCellAlgorithm->OnAdvanceStep(m_cells, m_molecules);
        
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