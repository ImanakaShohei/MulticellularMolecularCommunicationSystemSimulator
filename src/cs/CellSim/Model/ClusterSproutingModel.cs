using CellSim.CellAlgorithms;
using CellSim.Cells;
using CellSim.Numerics;
using CellSim.Settings;
using OpenCvSharp.Dnn;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Model
{
    /// <summary>
    /// クラスタスプラウトモデル
    /// </summary>
    public class ClusterSproutingModel : CellSimulationModel
    {
        private readonly int m_adhesionThreshold; //接着している細胞の数がこの値以下の時に反発力が働く
        private readonly double m_coefficientCd; //反発力にかける係数
        private readonly double m_contactDistance; //細胞同士がこの値より近づくと反発力が発生
        private readonly double m_followerAttractionFactor; //接着している細胞の数がadhesion_thresholdより多い時に受ける引力にかける係数
        private readonly double m_globalAttractionFactor; //すべての細胞間にかかる力の係数
        private readonly double m_lambda; //力の届く範囲を決める値
        private readonly double m_leaderRepulsionFactor; //接着している細胞の数がadhesion_thresholdの時に受ける反発力にかける係数
        private readonly double m_leaderRepulsionMaxDistance; //リーダーに届く反発力の最大距離
        private readonly double m_leaderRepulsionMinDistance; //リーダーに届く反発力の最小距離
        private readonly double m_leaderRepulsionRange; // m_leaderRepulsionMaxDistance - m_leaderRepulsionMinDistance
        private readonly double m_squareContactDistance; //

        public ClusterSproutingModel()
            : this(
                Config.SimulationModel.ClusterSprouting.AdhesionThreshold,
                Config.SimulationModel.ClusterSprouting.CoefficientCd,
                Config.SimulationModel.ClusterSprouting.ContactDistance,
                Config.SimulationModel.ClusterSprouting.FollowerAttractionFactor,
                Config.SimulationModel.ClusterSprouting.GlobalAttractionFactor,
                Config.SimulationModel.ClusterSprouting.Lambda,
                Config.SimulationModel.ClusterSprouting.LeaderRepulsionFactor,
                Config.SimulationModel.ClusterSprouting.LeaderRepulsionMaxDistance,
                Config.SimulationModel.ClusterSprouting.LeaderRepulsionMinDistance
            )
        {
        }

        public ClusterSproutingModel(
            int adhesionThreshold,
            double coefficientCd,
            double contactDistance,
            double followerAttractionFactor,
            double globalAttractionFactor,
            double lambda,
            double leaderRepulsionFactor,
            double leaderRepulsionMaxDistance,
            double leaderRepulsionMinDistance
        )
        {
            ArgumentOutOfRangeException.ThrowIfNegative(coefficientCd);
            ArgumentOutOfRangeException.ThrowIfNegative(contactDistance);
            ArgumentOutOfRangeException.ThrowIfNegative(followerAttractionFactor);
            ArgumentOutOfRangeException.ThrowIfNegative(globalAttractionFactor);
            ArgumentOutOfRangeException.ThrowIfZero(lambda);
            ArgumentOutOfRangeException.ThrowIfNegative(leaderRepulsionFactor);
            ArgumentOutOfRangeException.ThrowIfNegative(leaderRepulsionMaxDistance);
            ArgumentOutOfRangeException.ThrowIfNegative(leaderRepulsionMinDistance);

            ArgumentOutOfRangeException.ThrowIfLessThanOrEqual(leaderRepulsionMaxDistance, leaderRepulsionMinDistance);
            ArgumentOutOfRangeException.ThrowIfGreaterThanOrEqual(contactDistance, leaderRepulsionMinDistance);

            m_adhesionThreshold = adhesionThreshold;
            m_coefficientCd = coefficientCd;
            m_contactDistance = contactDistance;
            m_followerAttractionFactor = followerAttractionFactor;
            m_globalAttractionFactor = globalAttractionFactor;
            m_lambda = lambda;
            m_leaderRepulsionFactor = leaderRepulsionFactor;
            m_leaderRepulsionMaxDistance = leaderRepulsionMaxDistance;
            m_leaderRepulsionMinDistance = leaderRepulsionMinDistance;

            m_leaderRepulsionRange = leaderRepulsionMaxDistance - leaderRepulsionMinDistance;
            m_squareContactDistance = contactDistance * contactDistance;
        }

        public override bool UseCellAlgorithm => true;

        public override void BeforeAdvanceStep(ReadOnlySimulation sender, SimulationModelStepArgs args)
        {
            foreach (Cell cell in args.Cells)
            {
                cell.ClearAttachedCells();
            }

            for (int i = 0; i < args.Cells.Count; i++)
            {
                Cell cell1 = args.Cells[i];

                if (!cell1.IsAlive) continue;

                for (int j = i + 1; j < args.Cells.Count; j++)
                {
                    Cell cell2 = args.Cells[j];

                    if (!cell2.IsAlive) continue;

                    Vector3 diff = cell1.Position - cell2.Position;

                    if (diff.SquareLength < m_squareContactDistance)
                    {
                        cell1.Adhere(cell2);
                        cell2.Adhere(cell1);
                    }
                }
            }
        }

        public override Vector3 ComputeForceOnCell(ReadOnlySimulation sender, SimulationModelForceComputationArgs args)
        {
            Vector3 force1 = new Vector3();
            Vector3 force2 = new Vector3();
            Vector3 force3 = new Vector3();
            Vector3 force4 = new Vector3();
            CellInfo info = new CellInfo(args.Target);

            int attachedCellCount = args.Target.AttachedCellCount;

            foreach (ReadOnlyCell cell in args.Target.AttachedCells)
            {
                Vector3 diff = info.Position - cell.Position;
                double dist = diff.Length;

                if (attachedCellCount < m_adhesionThreshold)
                {
                    force1 += diff * ((m_leaderRepulsionMaxDistance - dist) / (m_leaderRepulsionMaxDistance * dist));
                }
                else
                {
                    double v = dist - m_leaderRepulsionMinDistance;

                    // 近すぎると何も起こらない
                    if (v > 0.0)
                    {
                        force2 -= diff * (v / (dist * m_leaderRepulsionRange));
                    }
                }

                // 近すぎると反発力が発生
                if (dist < m_contactDistance)
                {
                    force3 += diff * ((m_contactDistance - dist) / (m_contactDistance * dist));
                }
            }

            CellAlgorithm.Enumerate(
                this,
                args.CellAlgorithm,
                args.Target,
                args.Cells,
                args.Fields,
                cellInfo =>
                {
                    Vector3 diff = info.Position - cellInfo.Position;
                    double dist = diff.Length;

                    // すべての細胞に働く力
                    force4 -= diff * (Math.Exp(-dist / m_lambda) / dist);
                }
            );

            return m_leaderRepulsionFactor * force1 + m_followerAttractionFactor * force2 + m_coefficientCd * force3 + m_globalAttractionFactor * force4;
        }
        public override void OnAdvanceStep(ReadOnlySimulation sender, SimulationModelStepArgs args)
        {
        }
    }
}
