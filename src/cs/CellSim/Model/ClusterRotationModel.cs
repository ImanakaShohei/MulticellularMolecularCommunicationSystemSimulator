using CellSim.CellAlgorithms;
using CellSim.Cells;
using CellSim.Numerics;
using CellSim.Settings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Model
{
    /// <summary>
    /// クラスタ回転モデル
    /// </summary>
    public class ClusterRotationModel : CellSimulationModel
    {
        private readonly double m_adhesionDistanceThreshold; // 細胞同士がこの値より近いと接着力が働く
        private readonly double m_adhesionForceFactor; // 接着力にかける係数
        private readonly double m_centralForceFactor; // 中心力にかける係数
        private readonly double m_repulsionFactor; // 反発力の係数
        private readonly double m_repulsionMaxDistance; // 細胞同士がこの値より近いと反発する

        public ClusterRotationModel()
            : this(
                Config.SimulationModel.ClusterRotation.AdhesionDistanceThreshold,
                Config.SimulationModel.ClusterRotation.AdhesionForceFactor,
                Config.SimulationModel.ClusterRotation.CentralForceFactor,
                Config.SimulationModel.ClusterRotation.RepulsionFactor,
                Config.SimulationModel.ClusterRotation.RepulsionMaxDistance
            )
        {
        }

        public ClusterRotationModel(
            double adhesionDistanceThreshold,
            double adhesionForceFactor,
            double centralForceFactor,
            double repulsionFactor,
            double repulsionMaxDistance
        )
        {
            ArgumentOutOfRangeException.ThrowIfNegative(adhesionDistanceThreshold, nameof(adhesionDistanceThreshold));
            ArgumentOutOfRangeException.ThrowIfNegative(adhesionForceFactor, nameof(adhesionForceFactor));
            ArgumentOutOfRangeException.ThrowIfNegative(centralForceFactor, nameof(centralForceFactor));
            ArgumentOutOfRangeException.ThrowIfNegative(repulsionFactor, nameof(repulsionFactor));
            ArgumentOutOfRangeException.ThrowIfNegative(adhesionDistanceThreshold, nameof(adhesionDistanceThreshold));
            ArgumentOutOfRangeException.ThrowIfNegative(repulsionMaxDistance, nameof(repulsionMaxDistance));
            ArgumentOutOfRangeException.ThrowIfGreaterThanOrEqual(repulsionMaxDistance, adhesionDistanceThreshold, nameof(repulsionMaxDistance));
            
            m_adhesionDistanceThreshold = adhesionDistanceThreshold;
            m_adhesionForceFactor = adhesionForceFactor;
            m_centralForceFactor = centralForceFactor;
            m_repulsionFactor = repulsionFactor;
            m_repulsionMaxDistance = repulsionMaxDistance;
        }

        public override bool UseCellAlgorithm => true;

        public override void BeforeAdvanceStep(ReadOnlySimulation sender, SimulationModelStepArgs args)
        {
        }

        public override Vector3 ComputeForceOnCell(ReadOnlySimulation sender, SimulationModelForceComputationArgs args)
        {
            Vector3 force = new Vector3();
            Vector3 forceCenter = new Vector3();
            Vector3 forceCont = new Vector3();
            CellInfo info = new CellInfo(args.Target);

            forceCenter = info.Position * (-m_centralForceFactor / info.Position.Length);

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

                    if (dist < m_repulsionMaxDistance)
                    {
                        force += diff * ((m_repulsionMaxDistance - dist) / (m_repulsionMaxDistance * dist));
                    }

                    if (dist < m_adhesionDistanceThreshold)
                    {
                        forceCont += cellInfo.PreviusForce;
                    }
                }
            );

            return m_repulsionFactor * force + m_adhesionForceFactor * forceCont + forceCenter;
        }

        public override void OnAdvanceStep(ReadOnlySimulation sender, SimulationModelStepArgs args)
        {
        }
    }
}
