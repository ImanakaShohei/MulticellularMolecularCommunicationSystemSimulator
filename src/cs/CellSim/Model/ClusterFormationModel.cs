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
    public class ClusterFormationModel : CellSimulationModel
    {
        private readonly double m_adhesiveRepulsionFactor;
        private readonly double m_lambda;
        private readonly double m_reverseLambda;
        private readonly double m_remoteForceFactor;

        private Vector3 ComputeRemoteForce(
            Vector3 diff,
            double dist,
            double targetMass,
            double cellMass
        )
        {
            double mass = cellMass + targetMass;

            return (-mass * Math.Exp(-dist * m_reverseLambda) / dist) * diff;
        }

        private Vector3 ComputeVolumeExclusion(
            Vector3 diff,
            double dist,
            double targetRadius,
            double cellRadius
        )
        {
            double sumRadius = targetRadius + cellRadius;

            if (dist < sumRadius)
            {
                double tmp = 1.0 - dist / sumRadius;

                return diff * (tmp * tmp);
            }

            return Vector3.Zero;
        }

        public ClusterFormationModel()
            : this(
                Config.SimulationModel.ClusterFormation.AdhesiveRepulsionFactor,
                Config.SimulationModel.ClusterFormation.Lambda,
                Config.SimulationModel.ClusterFormation.RemoteForceFactor
            )
        {
        }

        public ClusterFormationModel(
            double adhesiveRepulsionFactor,
            double lambda,
            double remoteForceFactor
        )
        {
            if (adhesiveRepulsionFactor < 0.0) throw new ArgumentOutOfRangeException(Messages.Get("Model.ClusterFormationModel.ClusterFormationModel.Error.adhesiveRepulsionFactor"));
            if (lambda == 0.0) throw new ArgumentOutOfRangeException(Messages.Get("Model.ClusterFormationModel.ClusterFormationModel.Error.lambda"));
            if (remoteForceFactor < 0.0) throw new ArgumentOutOfRangeException(Messages.Get("Model.ClusterFormationModel.ClusterFormationModel.Error.remoteForceFactor"));

            m_adhesiveRepulsionFactor = adhesiveRepulsionFactor;
            m_lambda = lambda;
            m_reverseLambda = 1.0 / lambda;
            m_remoteForceFactor = remoteForceFactor;
        }

        public override bool UseCellAlgorithm => true;

        public override void BeforeAdvanceStep(ReadOnlySimulation sender, SimulationModelStepArgs args)
        {
        }

        public override Vector3 ComputeForceOnCell(ReadOnlySimulation sender, SimulationModelForceComputationArgs args)
        {
            CellInfo info = new CellInfo(args.Target);

            if (info.IsAlive)
            {
                Vector3 vec1 = new Vector3();
                Vector3 vec2 = new Vector3();

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
                        if (cellInfo.IsAlive)
                        {
                            vec1 += ComputeRemoteForce(diff, dist, info.Mass, cellInfo.Mass);
                        }
                        vec2 += ComputeVolumeExclusion(diff, dist, info.Radius, cellInfo.Radius);
                    }
                );

                return m_remoteForceFactor * vec1.Normalized + m_adhesiveRepulsionFactor * vec2;
            }

            Vector3 vec = new Vector3();

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
                    vec += ComputeVolumeExclusion(diff, dist, info.Radius, cellInfo.Radius);
                }
            );

            return m_adhesiveRepulsionFactor * vec;
        }

        public override void OnAdvanceStep(ReadOnlySimulation sender, SimulationModelStepArgs args)
        {
        }
    }
}
