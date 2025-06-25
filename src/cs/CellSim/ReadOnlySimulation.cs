using CellSim.CellAlgorithms;
using CellSim.Cells;
using CellSim.Model;
using CellSim.Molecular;
using CellSim.Settings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim
{
    /// <summary>
    /// 
    /// </summary>
    public class ReadOnlySimulation : IDisposable
    {
        private CellAlgorithm? m_cellAlgorithm;
        /// <summary>
        /// クラスタモデルで使うCellListインスタンス
        /// </summary>
        private CellList? m_cellList;

        /// <summary>
        /// 細胞リスト
        /// </summary>
        protected readonly List<Cell> m_cells;

        /// <summary>
        /// 複数スレッドによる処理をするかどうか
        /// </summary>
        protected bool m_enableMultithreading;

        /// <summary>
        /// 分子空間リスト
        /// </summary>
        protected readonly List<MoleculeField> m_molecules;

        /// <summary>
        /// アルゴリズム側で力を計算するかどうか
        /// </summary>
        protected bool m_overrideForceComputation;

        /// <summary>
        /// シミュレーションモデルインスタンスへのポインター
        /// </summary>
        protected readonly CellSimulationModel m_simulationModel;

        /// <summary>
        /// 結果を出力するクラス
        /// </summary>
        protected readonly SimulationResultWriter m_writer;

        private void InitializeCellAlgorithm()
        {
            // 最適化アルゴリズムを使用するときだけCellAlgorithmインスタンスを作成
            if (m_simulationModel.UseCellAlgorithm)
            {
                m_cellAlgorithm = CellAlgorithm.FromType(Config.CellAlgorithm.AlgorithmType);

                m_overrideForceComputation = m_cellAlgorithm.OverrideForceComputation;

                if (Config.CellAlgorithm.UseClusterModel)
                {
                    if (Config.CellAlgorithm.AlgorithmType == CellAlgorithmType.CellList)
                    {
                        m_cellList = m_cellAlgorithm as CellList;
                    }
                    else
                    {
                        m_cellList = new CellList();
                    }

                }
            }
            else
            {
                if (Config.CellAlgorithm.UseClusterModel)
                {
                    m_cellList = new CellList();
                }
            }

            if (m_cellAlgorithm != null)
            {
                m_enableMultithreading = m_cellAlgorithm.HasMultithreadingSupport;
            }
        }

        public CellAlgorithm? CellAlgorithm => m_cellAlgorithm;
        public CellList? CellList => m_cellList;

        public IReadOnlyList<ReadOnlyCell> Cells => m_cells;

        public IReadOnlyList<ReadOnlyMoleculeField> Molecules => m_molecules;

        public CellSimulationModel SimulationModel => m_simulationModel;

        protected ReadOnlySimulation(SimulationOption option)
        {
            m_cells = new List<Cell>();
            m_enableMultithreading = true;
            m_molecules = new List<MoleculeField>();
            m_overrideForceComputation = false;
            m_cellAlgorithm = null;
            m_cellList = null;
            m_simulationModel = CellSimulationModel.FromType(Config.SimulationModel.SimulationType);
            m_writer = new SimulationResultWriter(option);

            Console.WriteLine(Messages.Get("Simulation.Simulation.Initializing"));
            
            InitializeCellAlgorithm();

            m_simulationModel.InitializeCells(this, m_cells);
        }
        public void Dispose()
        {
            m_writer.Dispose();
            GC.SuppressFinalize(this);
        }
    }
}
