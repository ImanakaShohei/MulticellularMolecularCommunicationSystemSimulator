using CellSim.CellAlgorithms;
using CellSim.Cells;
using CellSim.Model;
using CellSim.Molecular;
using CellSim.Numerics;
using CellSim.Settings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim
{
    /// <summary>
    /// シミュレーション実行クラス
    /// </summary>
    public class Simulation : ReadOnlySimulation
    {
        private void ApplyForce()
        {
            // 力を加える
            if (m_overrideForceComputation)
            {
                // ここでm_pCellAlgorithmはnullptrではありません
                if (m_enableMultithreading)
                {
                    Parallel.ForEach(
                        m_cells,
                        Config.Optimization.ParallelOptions,
                        cell =>
                        {
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                            cell.ApplyForce(CellAlgorithm.ComputeForceOnCell(this, new CellAlgorithmForceComputationArgs(m_cells, m_molecules, m_simulationModel, cell)));
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
                        }
                    );
                }
                else
                {
                    foreach (Cell cell in m_cells)
                    {
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                        cell.ApplyForce(CellAlgorithm.ComputeForceOnCell(this, new CellAlgorithmForceComputationArgs(m_cells, m_molecules, m_simulationModel, cell)));
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
                    }
                }
            }
            else
            {
                if (m_enableMultithreading)
                {
                    Parallel.ForEach(
                        m_cells,
                        Config.Optimization.ParallelOptions,
                        cell =>
                        {
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
#pragma warning disable CS8604 // Null 参照引数の可能性があります。
                            cell.ApplyForce(m_simulationModel.ComputeForceOnCell(this, new SimulationModelForceComputationArgs(cell, m_cells, m_cells, m_molecules, CellAlgorithm)));
#pragma warning restore CS8604 // Null 参照引数の可能性があります。
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
                        }
                    );

                }
                else
                {
                    foreach (Cell cell in m_cells)
                    {
#pragma warning disable CS8604 // Null 参照引数の可能性があります。
                        cell.ApplyForce(m_simulationModel.ComputeForceOnCell(this, new SimulationModelForceComputationArgs(cell, m_cells, m_cells, m_molecules, CellAlgorithm)));
#pragma warning restore CS8604 // Null 参照引数の可能性があります。
                    }
                }
            }
        }
        private void AdvanceStep()
        {
            // 前処理
            BeforeAdvanceStep();
            m_simulationModel.BeforeAdvanceStep(this, new SimulationModelStepArgs(m_cells, m_molecules));

            if (m_simulationModel.UseCellAlgorithm)
            {
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                CellAlgorithm.BeforeAdvanceStep(this, new CellAlgorithmStepArgs(m_cells, m_molecules));
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。

                if (Config.CellAlgorithm.UseClusterModel && Config.CellAlgorithm.AlgorithmType != CellAlgorithmType.CellList)
                {
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                    CellList.BeforeAdvanceStep(this, new CellAlgorithmStepArgs(m_cells, m_molecules));
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
                }
            }
            else
            {
                if (Config.CellAlgorithm.UseClusterModel)
                {
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                    CellList.BeforeAdvanceStep(this, new CellAlgorithmStepArgs(m_cells, m_molecules));
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
                }
            }

            foreach (MoleculeField field in m_molecules)
            {
                field.BeforeAdvanceStep(m_cells);
            }

            ApplyForce();

            if (Config.Cell.IsSensitiveToMolecules)
            {
                // 状態を変更する可能性があるのでシングルスレッドで動かす
                foreach (Cell cell in m_cells)
                {
                    cell.ProcessMolecules(m_molecules);
                }
            }


            // 移動
            foreach (Cell cell in m_cells)
            {
                cell.Move();
            }

            if (Config.CellAlgorithm.UseClusterModel)
            {
                ClusterModel.Combine(m_cells, m_molecules, CellList);

                // 無効になったオブジェクトを削除
                int i = m_cells.Count - 1;

                while (i >= 0)
                {
                    Cell cell = m_cells[i];

                    if (cell.Type == CellType.Invalid)
                    {
                        m_cells.RemoveAt(i);
                        continue;
                    }

                    --i;
                }
            }

            m_simulationModel.OnAdvanceStep(this, new SimulationModelStepArgs(m_cells, m_molecules));
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
            if (m_simulationModel.UseCellAlgorithm) CellAlgorithm.OnAdvanceStep(this, new CellAlgorithmStepArgs(m_cells, m_molecules));
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。

            foreach (MoleculeField field in m_molecules)
            {
                field.OnAdvanceStep(m_cells);
            }
        }

        private void BeforeAdvanceStep()
        {
            // 無駄な最適化
            if (Config.Cell.EnableGrowth)
            {
                foreach (Cell cell in m_cells)
                {
                    cell.ResetForce();
                    cell.Grow();
                }
            }
            else
            {
                foreach (Cell cell in m_cells)
                {
                    cell.ResetForce();
                }
            }

            for (int i = 0; i != m_cells.Count; i++)
            {
                Cell cell = m_cells[i];

                if (cell.ShouldDivideThisStep)
                {
                    m_cells.Add(cell.Divide());
                }
            }
        }

        public Simulation(SimulationOption option) : base(option)
        {
        }

        public void Run()
        {
            Console.WriteLine(Messages.Get("Simulation.Run.Running"));

            ulong totalStep = Config.Simulation.TotalSteps;

            DateTime beginClock = DateTime.Now;
            DateTime currentClock = beginClock;

            m_writer.Save(this, 0);

            for (ulong step = 1; step <= totalStep; ++step)
            {

                BeforeAdvanceStep();
                AdvanceStep();

                if (step % Config.Simulation.OutputInterval == 0)
                {
                    m_writer.Save(this, step);
                }

                if ((long)(DateTime.Now - currentClock).TotalMilliseconds >= 250)
                {
                    Console.WriteLine($"{step}/{totalStep}");
                    currentClock = DateTime.Now;
                }

            }

            currentClock = DateTime.Now;

            m_writer.SaveConfig(
                totalStep,
                Config.Cell.CellCount,
                (long)(currentClock - beginClock).TotalMilliseconds,
                Config.SimulationModel.SimulationType,
                Config.CellAlgorithm.AlgorithmType
            );

            Console.WriteLine(Messages.Get("Simulation.Run.Completed"));
        }
    }
}
