using CellSim.Cells;
using CellSim.Model;
using CellSim.Molecular;
using CellSim.Numerics;
using CellSim.Settings;
using CellSim.Users;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.CellAlgorithms
{
    /// <summary>
    /// 高速化アルゴリズム
    /// </summary>
    public abstract class CellAlgorithm
    {
        public static void Enumerate(CellSimulationModel model, CellAlgorithm cellAlgorithm, ReadOnlyCell target, IReadOnlyList<ReadOnlyCell> cells, IReadOnlyList<ReadOnlyMoleculeField> fields, Action<CellInfo> action)
        {
            switch (Config.Optimization.Peformance)
            {
                case PeformanceType.Fast:
                    foreach (CellInfo cellInfo in cellAlgorithm.GetAffectableCellInfos(model, new CellAlgorithmAffectableCellQueryArgs(cells, fields, target)))
                    {
                        action(cellInfo);
                    }
                    break;
                case PeformanceType.LowMemory:
                    foreach (CellInfo cellInfo in cellAlgorithm.EnumerateAffectableCellInfos(model, new CellAlgorithmAffectableCellQueryArgs(cells, fields, target)))
                    {
                        action(cellInfo);
                    }
                    break;
            }
        }

        /// <summary>
        /// CellAlgorithmTypeからインスタンスを作成
        /// </summary>
        /// <param name="type">種類</param>
        /// <returns>インスタンス</returns>
        /// <exception cref="NotSupportedException"></exception>
        public static CellAlgorithm FromType(CellAlgorithmType type)
        {
            return type switch
            {
                CellAlgorithmType.BarnesHut => new BarnesHut(),
                CellAlgorithmType.CellList => new CellList(),
                CellAlgorithmType.Naive => new NaiveAlgorithm(),
                CellAlgorithmType.Null => new NullAlgorithm(),
                CellAlgorithmType.ParticleMesh => new ParticleMesh(),
                CellAlgorithmType.User => new UserCellAlgorithm(),
                _ => throw new NotSupportedException(Messages.Get("CellAlgorithms.CellAlgorithm.FromType.Error"))
            };
        }

        /// <summary>
        /// このアルゴリズムが複数スレッドによる処理をサポートしているかどうか
        /// </summary>
        public abstract bool HasMultithreadingSupport{ get; }

        /// <summary>
        /// アルゴリズム側で力の計算をすることを強制するフラグ
        /// </summary>
        public virtual bool OverrideForceComputation => false;

        /// <summary>
        /// 前処理
        /// </summary>
        /// <param name="sender">このメソッドを呼んだシミュレーションインスタンス</param>
        /// <param name="args">処理に必要な情報</param>
        public abstract void BeforeAdvanceStep(
            ReadOnlySimulation sender,
            CellAlgorithmStepArgs args
        );

        /// <summary>
        /// ターゲットの細胞かける力を計算
        /// </summary>
        /// <param name="sender">このメソッドを呼んだシミュレーションインスタンス</param>
        /// <param name="args">処理に必要な情報</param>
        /// <returns>計算結果</returns>
        /// <remarks>この関数はOverrideForceComputation()が'true'のときに呼ばれます</remarks>
        public virtual Vector3 ComputeForceOnCell(
            ReadOnlySimulation sender,
            CellAlgorithmForceComputationArgs args
        )
        {
            return Vector3.Zero;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="args"></param>
        /// <returns></returns>
        public abstract IEnumerable<CellInfo> EnumerateAffectableCellInfos(
            CellSimulationModel sender,
            CellAlgorithmAffectableCellQueryArgs args
        );

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="args"></param>
        /// <returns></returns>
        public abstract List<CellInfo> GetAffectableCellInfos(
            CellSimulationModel sender,
            CellAlgorithmAffectableCellQueryArgs args
        );

        /// <summary>
        /// 前処理
        /// </summary>
        /// <param name="sender">このメソッドを呼んだシミュレーションインスタンス</param>
        /// <param name="args">処理に必要な情報</param>
        public abstract void OnAdvanceStep(
            ReadOnlySimulation sender,
            CellAlgorithmStepArgs args
        );

        
    }
}
