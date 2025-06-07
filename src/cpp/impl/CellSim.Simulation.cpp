#include "CellSim.Simulation.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"
#include "CellSim.CellAlgorithms.CellList.hpp"
#include "CellSim.Model.CellSimulationModel.hpp"
#include "CellSim.Settings.Config.CellAlgorithm.hpp"
#include "CellSim.Settings.Config.SimulationModel.hpp"
#include "CellSim.Threading.ThreadPool.hpp"

namespace CellSim
{
    void Simulation::m_addForce()
    {
        // 力を加える
        if (m_overrideForceComputation) {
            // ここでm_pCellAlgorithmはnullptrではありません
            if (m_enableMultithreading) {
                Threading::ThreadPool::ParallelFor(
                    m_cells.begin(),
                    m_cells.end(),
                    [this] (Cells::Cell& cell) {
                        cell.AddForce(m_pCellAlgorithm->ComputeForceOnCell(cell, m_cells, m_molecules));
                    }
                );
            }
            else {
                for (Cells::Cell& cell : m_cells) {
                    cell.AddForce(m_pCellAlgorithm->ComputeForceOnCell(cell, m_cells, m_molecules));
                }
            }
        }
        else {
            if (m_enableMultithreading) {
                Threading::ThreadPool::ParallelFor(
                    m_cells.begin(),
                    m_cells.end(),
                    [this] (Cells::Cell& cell) {
                        cell.AddForce(m_pCellSimulationModel->ComputeForceOnCell(cell, m_cells, m_molecules, m_pCellAlgorithm));
                    }
                );
            }
            else {
                for (Cells::Cell& cell : m_cells) {
                    cell.AddForce(m_pCellSimulationModel->ComputeForceOnCell(cell, m_cells, m_molecules, m_pCellAlgorithm));
                }
            }
        }
    }

    void Simulation::m_advanceStep()
    {
        // 前処理
        m_beforeAdvanceStep();
        m_pCellSimulationModel->BeforeAdvanceStep(m_cells, m_molecules);

        if (m_pCellSimulationModel->UseCellAlgorithm()) {
            m_pCellAlgorithm->BeforeAdvanceStep(m_cells, m_molecules);

            if (Settings::Config::CellAlgorithm::UseClusterModel() && Settings::Config::CellAlgorithm::AlgorithmType() != CellAlgorithms::CellAlgorithmType::CellList) {
                m_pCellList->BeforeAdvanceStep(m_cells, m_molecules);
            }
        }
        else {
            if (Settings::Config::CellAlgorithm::UseClusterModel()) {
                m_pCellList->BeforeAdvanceStep(m_cells, m_molecules);
            }
        }

        m_addForce();
        
        // 移動
        for (Cells::Cell& cell : m_cells) {
            cell.Move();
        }

        m_pCellSimulationModel->OnAdvanceStep(m_cells, m_molecules);
        if (m_pCellSimulationModel->UseCellAlgorithm()) m_pCellAlgorithm->OnAdvanceStep(m_cells, m_molecules);
        
    }

    void Simulation::m_beforeAdvanceStep()
    {
        for (Cells::Cell& cell : m_cells) {
            cell.ResetForce();
        }

        // TODO: ここに細胞の成長や分子の代謝の処理を追加
    }

    void Simulation::m_initializeCellAlgorithm()
    {
        // 最適化アルゴリズムを使用するときだけCellAlgorithmインスタンスを作成
        if (m_pCellSimulationModel->UseCellAlgorithm()) {
            m_pCellAlgorithm = CellAlgorithms::CellAlgorithm::FromType(Settings::Config::CellAlgorithm::AlgorithmType());

            m_overrideForceComputation = m_pCellAlgorithm->OverrideForceComputation();

            if (Settings::Config::CellAlgorithm::UseClusterModel()) {
                if (Settings::Config::CellAlgorithm::AlgorithmType() == CellAlgorithms::CellAlgorithmType::CellList) {
                    m_pCellList = static_cast<CellAlgorithms::CellList*>(m_pCellAlgorithm);
                }
                else {
                    m_pCellList = new CellAlgorithms::CellList();
                }
                
            }
        }
        else {
            if (Settings::Config::CellAlgorithm::UseClusterModel()) {
                m_pCellList = new CellAlgorithms::CellList();
            }
        }

        if (m_pCellAlgorithm != nullptr) {
            m_enableMultithreading = m_pCellAlgorithm->HasMultithreadingSupport();
        }
    }

    Simulation::Simulation()
    : m_cells()
    , m_enableMultithreading(true)
    , m_molecules()
    , m_overrideForceComputation(false)
    , m_pCellAlgorithm(nullptr)
    , m_pCellList(nullptr)
    , m_pCellSimulationModel(Model::CellSimulationModel::FromType(Settings::Config::SimulationModel::SimulationType()))
    {
        s_current = this;

        m_initializeCellAlgorithm();
        
        m_pCellSimulationModel->InitializeCells(m_cells);
    }

    Simulation::~Simulation()
    {
        s_current = nullptr;

        delete m_pCellSimulationModel;
        if (Settings::Config::CellAlgorithm::UseClusterModel()) delete m_pCellList;

        if (m_pCellAlgorithm != nullptr && Settings::Config::CellAlgorithm::AlgorithmType() == CellAlgorithms::CellAlgorithmType::CellList) delete m_pCellAlgorithm;
    }

    void Simulation::Run()
    {
        s_current = this;
    }
}