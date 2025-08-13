#include "CellSim.Simulation.hpp"
#include "CellSim.Messages.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmAffectableCellQueryArgs.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmStepArgs.hpp"
#include "CellSim.CellAlgorithms.CellList.hpp"
#include "CellSim.CellAlgorithms.ClusterModel.hpp"
#include "CellSim.Model.CellSimulationModel.hpp"
#include "CellSim.Model.SimulationModelForceComputationArgs.hpp"
#include "CellSim.Model.SimulationModelStepArgs.hpp"
#include "CellSim.Settings.Config.Cell.hpp"
#include "CellSim.Settings.Config.CellAlgorithm.hpp"
#include "CellSim.Settings.Config.Molecular.hpp"
#include "CellSim.Settings.Config.Simulation.hpp"
#include "CellSim.Settings.Config.SimulationModel.hpp"
#include "CellSim.Threading.ThreadPool.hpp"

#include <chrono>

namespace CellSim
{
    void Simulation::m_applyForce()
    {
        // 力を加える
        if (m_overrideForceComputation) {
            // ここでm_pCellAlgorithmはnullptrではありません
            if (m_enableMultithreading) {
                Threading::ThreadPool::ParallelFor(
                    m_cells.begin(),
                    m_cells.end(),
                    [this] (Cells::Cell& cell) {
                        cell.ApplyForce(m_pCellAlgorithm->ComputeForceOnCell(this, { &cell, &m_cells, &m_molecules, m_pCellSimulationModel }));
                    }
                );
            }
            else {
                for (Cells::Cell& cell : m_cells) {
                    cell.ApplyForce(m_pCellAlgorithm->ComputeForceOnCell(this, { &cell, &m_cells, &m_molecules, m_pCellSimulationModel }));
                }
            }
        }
        else {
            if (m_enableMultithreading) {
                Threading::ThreadPool::ParallelFor(
                    m_cells.begin(),
                    m_cells.end(),
                    [this] (Cells::Cell& cell) {
                        cell.ApplyForce(m_pCellSimulationModel->ComputeForceOnCell(this, { &cell, &m_cells, &m_cells, &m_molecules, m_pCellAlgorithm }));
                    }
                );
            }
            else {
                for (Cells::Cell& cell : m_cells) {
                    cell.ApplyForce(m_pCellSimulationModel->ComputeForceOnCell(this, { &cell, &m_cells, &m_cells, &m_molecules, m_pCellAlgorithm }));
                }
            }
        }
    }

    void Simulation::m_advanceStep()
    {
        // 前処理
        m_beforeAdvanceStep();
        m_pCellSimulationModel->BeforeAdvanceStep(this, { &m_cells, &m_molecules });

        if (m_pCellSimulationModel->UseCellAlgorithm()) {
            m_pCellAlgorithm->BeforeAdvanceStep(this, { &m_cells, &m_molecules });

            if (Settings::Config::CellAlgorithm::UseClusterModel() && Settings::Config::CellAlgorithm::AlgorithmType() != CellAlgorithms::CellAlgorithmType::CellList) {
                m_pCellList->BeforeAdvanceStep(this, { &m_cells, &m_molecules });
            }
        }
        else {
            if (Settings::Config::CellAlgorithm::UseClusterModel()) {
                m_pCellList->BeforeAdvanceStep(this, { &m_cells, &m_molecules });
            }
        }

        for (Molecular::MoleculeField& field : m_molecules) {
            field.BeforeAdvanceStep(m_cells);
        }

        m_applyForce();

        if (Settings::Config::Cell::IsSensitiveToMolecules()) {

            // 状態を変更する可能性があるのでシングルスレッドで動かす
            for (Cells::Cell& cell : m_cells) {
                cell.ProcessMolecules(m_molecules);
            }
        }
        
        // 移動
        for (Cells::Cell& cell : m_cells) {
            cell.Move();
        }

        for (Molecular::MoleculeField& field : m_molecules) {
            field.Diffuse();
        }

        if (Settings::Config::CellAlgorithm::UseClusterModel()) {
            CellAlgorithms::ClusterModel::Combine(m_cells, m_molecules, m_pCellList);

            // 無効になったオブジェクトを削除
            for (Cells::Cell& cell : m_cells) {
                if (cell.Type() == Cells::CellType::Invalid()) {
                    ::std::vector<Cells::Cell> newCells;
                    newCells.reserve(m_cells.size());
                    
                    for (Cells::Cell& cell1 : m_cells) {
                        if (cell1.Type() != Cells::CellType::Invalid()) {
                            
                            newCells.emplace_back(::std::move(cell1));
                            
                        }
                    }
                    m_cells = ::std::move(newCells);
                    break;
                }
            }
        }

        m_pCellSimulationModel->OnAdvanceStep(this, { &m_cells, &m_molecules });
        if (m_pCellSimulationModel->UseCellAlgorithm()) m_pCellAlgorithm->OnAdvanceStep(this, { &m_cells, &m_molecules });
        
        for (Molecular::MoleculeField& field : m_molecules) {
            field.OnAdvanceStep(m_cells);
        }
    }

    void Simulation::m_beforeAdvanceStep()
    {
        // 無駄な最適化
        if (Settings::Config::Cell::EnableGrowth()) {
            for (Cells::Cell& cell : m_cells) {
                cell.ResetForce();
                cell.Grow();
            }
        }
        else {
            for (Cells::Cell& cell : m_cells) {
                cell.ResetForce();
            }
        }
        
        for (size_t i = 0; i != m_cells.size(); i++) {
            Cells::Cell& cell = m_cells[i];

            if (cell.ShouldDivideThisStep()) {
                m_cells.push_back(cell.Divide());
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

    Simulation::Simulation(SimulationOption option)
    : m_cells()
    , m_enableMultithreading(true)
    , m_molecules()
    , m_overrideForceComputation(false)
    , m_pCellAlgorithm(nullptr)
    , m_pCellList(nullptr)
    , m_pCellSimulationModel(Model::CellSimulationModel::FromType(Settings::Config::SimulationModel::SimulationType()))
    , m_writer(::std::move(option))
    {
        s_current = this;

        ::puts(Messages::Get("Simulation.Simulation.Initializing").c_str());

        m_initializeCellAlgorithm();
        
        m_pCellSimulationModel->InitializeCells(this, m_cells);

        for (Molecular::MoleculeCreateInfo const& info : Settings::Config::Molecular::MolecularConfigs()) {
            m_molecules.emplace_back(
                info.GridCount,
                Settings::Config::Simulation::Enable2DMode(),
                info.Kind,
                info.BoundaryCondition,
                info.InitialDistribution,
                info.MoleculeAmount,
                info.Behavior.get()
            );
        }

        m_writer.InitializeMoleculeData(m_molecules);
    }

    Simulation::~Simulation()
    {
        s_current = nullptr;

        delete m_pCellSimulationModel;
        if (Settings::Config::CellAlgorithm::UseClusterModel()) delete m_pCellList;

        if (m_pCellAlgorithm != nullptr && Settings::Config::CellAlgorithm::AlgorithmType() != CellAlgorithms::CellAlgorithmType::CellList) delete m_pCellAlgorithm;
    }

    void Simulation::Run()
    {
        s_current = this;

        ::puts(Messages::Get("Simulation.Run.Running").c_str());

        uint64_t totalStep = Settings::Config::Simulation::TotalSteps();

        ::std::chrono::system_clock::time_point beginClock  = std::chrono::system_clock::now();
        ::std::chrono::system_clock::time_point currentClock = beginClock;

        m_writer.Save(*this, 0);

        for (uint64_t step = 1; step <= totalStep; ++step) {

            m_beforeAdvanceStep();
            m_advanceStep();
            
            if (step % Settings::Config::Simulation::OutputInterval() == 0) {
                m_writer.Save(*this, step);
            }

            if (::std::chrono::duration_cast<::std::chrono::milliseconds>(::std::chrono::system_clock::now() - currentClock).count() >= 250) {
                ::printf("%llu/%llu\n", step, totalStep);
                currentClock = ::std::chrono::system_clock::now();
            }
            
        }

        currentClock = ::std::chrono::system_clock::now();

        uint64_t totalCellCount = 0;

        m_writer.SaveConfig(
            totalStep,
            Settings::Config::Cell::TotalCellCount(),
            ::std::chrono::duration_cast<::std::chrono::milliseconds>(currentClock - beginClock).count(),
            Settings::Config::SimulationModel::SimulationType(),
            Settings::Config::CellAlgorithm::AlgorithmType()
        );

        ::puts(Messages::Get("Simulation.Run.Completed").c_str());
    }
}