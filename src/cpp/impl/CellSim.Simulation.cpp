#include "CellSim.Simulation.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"
#include "CellSim.CellAlgorithms.CellList.hpp"
#include "CellSim.Model.CellSimulationModel.hpp"
#include "CellSim.Settings.Config.Cell.hpp"
#include "CellSim.Settings.Config.CellAlgorithm.hpp"
#include "CellSim.Settings.Config.Simulation.hpp"
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

        for (Molecular::MoleculeField& field : m_molecules) {
            field.BeforeAdvanceStep(m_cells);
        }

        m_addForce();

        if (Settings::Config::Cell::IsSensitiveToMolecules()) {
            Threading::ThreadPool::ParallelFor(
                m_cells.begin(),
                m_cells.end(),
                [this] (Cells::Cell& cell) {
                    for (Molecular::MoleculeField const& field : m_molecules) {
                        cell.SenseMolecules(field);
                    }
                }
            );

            // 状態を変更する可能性があるのでシングルスレッドで動かす
            for (Cells::Cell& cell : m_cells) {
                cell.EmitMolecule(m_molecules);
            }
        }
        
        // 移動
        for (Cells::Cell& cell : m_cells) {
            cell.Move();
        }

        m_pCellSimulationModel->OnAdvanceStep(m_cells, m_molecules);
        if (m_pCellSimulationModel->UseCellAlgorithm()) m_pCellAlgorithm->OnAdvanceStep(m_cells, m_molecules);
        
        for (Molecular::MoleculeField& field : m_molecules) {
            field.OnAdvanceStep(m_cells);
        }
    }

    void Simulation::m_beforeAdvanceStep()
    {
        if (Settings::Config::Cell::EnableGrowth()) {
            if (Settings::Config::Cell::IsSensitiveToMolecules()) {
                for (Cells::Cell& cell : m_cells) {
                    cell.ResetForce();
                    cell.Grow();
                    cell.Metabolize();
                }
            }
            else {
                for (Cells::Cell& cell : m_cells) {
                    cell.ResetForce();
                    cell.Grow();
                }
            }
        }
        else {
            if (Settings::Config::Cell::IsSensitiveToMolecules()) {
                for (Cells::Cell& cell : m_cells) {
                    cell.ResetForce();
                    cell.Metabolize();
                }
            }
            else {
                for (Cells::Cell& cell : m_cells) {
                    cell.ResetForce();
                }
            }
        }
        
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

    void Simulation::m_save(uint64_t step) const
    {
        if (m_option.IsOutputBinary()) {

        }

        if (m_option.IsOutputCsv()) {

        }

        if (m_option.IsOutputImage()) {

        }

        if (m_option.IsOutputVideo()) {

        }
    }

    Simulation::Simulation(SimulationOption option)
    : m_cells()
    , m_enableMultithreading(true)
    , m_molecules()
    , m_overrideForceComputation(false)
    , m_pCellAlgorithm(nullptr)
    , m_pCellList(nullptr)
    , m_pCellSimulationModel(Model::CellSimulationModel::FromType(Settings::Config::SimulationModel::SimulationType()))
    , m_option(::std::move(option))
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

        uint64_t totalStep = Settings::Config::Simulation::TotalSteps();

        for (uint64_t step = 0; step != totalStep; ++step) {

            m_beforeAdvanceStep();
            m_advanceStep();
            

        }
    }
}