using CellSim.Cells;
using CellSim.Numerics;
using CellSim.Settings;
using CellSim.Users;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Model
{
    /// <summary>
    /// 力学モデル
    /// </summary>
    public abstract class CellSimulationModel
    {
        /// <summary>
        /// CellSimulationTypeからインスタンスを作成
        /// </summary>
        /// <param name="type">種類</param>
        /// <returns>インスタンス</returns>
        /// <exception cref="NotImplementedException"></exception>
        public static CellSimulationModel FromType(CellSimulationType type)
        {
            return type switch
            {
                CellSimulationType.CellGrowth => new CellGrowthModel(),
                CellSimulationType.ClusterFormation => new ClusterFormationModel(),
                CellSimulationType.ClusterRotation => new ClusterRotationModel(),
                CellSimulationType.ClusterSprouting => new ClusterSproutingModel(),
                CellSimulationType.NetworkFormation => new NetworkFormationModel(),
                CellSimulationType.Null => new NullModel(),
                CellSimulationType.User => new UserSimulationModel(),
                _ => throw new NotImplementedException(Messages.Get("Model.CellSimulationModel.FromType.Error")),
            };
        }

        /// <summary>
        /// モデルでCellAlgorithmを使うかどうか
        /// </summary>
        public abstract bool UseCellAlgorithm{ get; }

        /// <summary>
        /// 前処理
        /// </summary>
        /// <param name="sender">このメソッドを呼んだインスタンス</param>
        /// <param name="args">処理に必要な情報</param>
        public abstract void BeforeAdvanceStep(
            ReadOnlySimulation sender,
            SimulationModelStepArgs args
        );

        /// <summary>
        /// ターゲットの細胞かける力を計算
        /// </summary>
        /// <param name="sender">このメソッドを呼んだインスタンス</param>
        /// <param name="args">リスト</param>
        /// <returns>計算結果</returns>
        public abstract Vector3 ComputeForceOnCell(
            ReadOnlySimulation sender,
            SimulationModelForceComputationArgs args
        );

        /// <summary>
        /// リストに細胞を格納
        /// </summary>
        /// <param name="sender">このメソッドを呼んだインスタンス</param>
        /// <param name="cells">リスト</param>
        public virtual void InitializeCells(
            ReadOnlySimulation sender,
            List<Cell> cells
        )
        {
            Random random = new Random(Config.Cell.InitialPlacementSeed);

            CellBehavior behavior = CellBehavior.FromType(Config.CellBehavior.BehaviorType);
            CellType type = Config.Cell.Type;
            int cellCount = Config.Cell.CellCount;
            double mass = Config.Cell.Mass;
            double radius = Config.Cell.Radius;
            double initialPlacmentRadius = Config.Cell.InitialPlacementRadius;

            if (Config.Simulation.Enable2DMode)
            {
                for (int count = 0; count < cellCount; count++)
                {
                    double r = Math.Sqrt(random.NextDouble()) * initialPlacmentRadius;
                    double theta = random.NextDouble() * (Math.PI * 2.0);
                    double x = r * Math.Cos(theta);
                    double y = r * Math.Sin(theta);

                    cells.Add(
                        new Cell(
                            type,
                            behavior.Clone(),
                            mass,
                            radius,
                            new Vector3(x, y, 0)
                        )
                    );
                }
            }
            else
            {
                for (int count = 0; count < cellCount; count++)
                {
                    double v = random.NextDouble();

                    double theta = random.NextDouble() * (Math.PI * 2.0);
                    double phi = Math.Acos(1.0 - 2.0 * v);

                    double x = Math.Sin(phi) * Math.Cos(theta) * initialPlacmentRadius;
                    double y = Math.Sin(phi) * Math.Sin(theta) * initialPlacmentRadius;
                    double z = Math.Cos(phi) * initialPlacmentRadius;

                    cells.Add(
                        new Cell(
                            type,
                            behavior.Clone(),
                            mass,
                            radius,
                            new Vector3(x, y, z)
                        )
                    );
                }
            }
        }

        /// <summary>
        /// 後処理
        /// </summary>
        /// <param name="sender">このメソッドを呼んだインスタンス</param>
        /// <param name="args">処理に必要な情報</param>
        public abstract void OnAdvanceStep(
            ReadOnlySimulation sender,
            SimulationModelStepArgs args
        );
    }
}
