using CellSim.CellAlgorithms;
using CellSim.Cells;
using CellSim.Numerics;
using CellSim.Settings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http.Headers;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Model
{
    public class NetworkFormationModel : CellSimulationModel
    {
        private readonly double m_adhesiveRepulsionFactor;
        private readonly double m_attractionFactor;
        private readonly double m_lambda;
        private readonly double m_maxAttractionDistance;
        private readonly double m_maxRepulsionDistance;
        private readonly double m_minAttractionDistance;
        private readonly double m_remoteForceFactor;
        private readonly double m_reverseLambda;
        private readonly double m_squareMaxAttractionDistance;

        private readonly CellList m_cellList;

        public NetworkFormationModel()
            : this(
                Config.SimulationModel.NetworkFormation.AdhesiveRepulsionFactor,
                Config.SimulationModel.NetworkFormation.AttributeActionFactor,
                Config.SimulationModel.NetworkFormation.Lambda,
                Config.SimulationModel.NetworkFormation.MaxAttractionDistance,
                Config.SimulationModel.NetworkFormation.MaxRepulsionDistance,
                Config.SimulationModel.NetworkFormation.MinAttractionDistance,
                Config.SimulationModel.NetworkFormation.RemoteForceFactor
            )
        {
        }

        public NetworkFormationModel(
            double adhesiveRepulsionFactor,
            double attractionFactor,
            double lambda,
            double maxAttractionDistance,
            double maxRepulsionDistance,
            double minAttractionDistance,
            double remoteForceFactor
        )
        {
            if (adhesiveRepulsionFactor < 0.0) throw new ArgumentOutOfRangeException(Messages.Get("Model.NetworkFormationModel.NetworkFormationModel.Error.adhesiveRepulsionFactor"));
            if (attractionFactor < 0.0) throw new ArgumentOutOfRangeException(Messages.Get("Model.NetworkFormationModel.NetworkFormationModel.Error.attractionFactor"));
            if (lambda == 0.0) throw new ArgumentOutOfRangeException(Messages.Get("Model.NetworkFormationModel.NetworkFormationModel.Error.lambda"));
            if (maxAttractionDistance <= 0.0) throw new ArgumentOutOfRangeException(Messages.Get("Model.NetworkFormationModel.NetworkFormationModel.Error.maxAttractionDistance"));
            if (maxRepulsionDistance <= 0.0) throw new ArgumentOutOfRangeException(Messages.Get("Model.NetworkFormationModel.NetworkFormationModel.Error.maxRepulsionDistance"));
            if (minAttractionDistance <= 0.0) throw new ArgumentOutOfRangeException(Messages.Get("Model.NetworkFormationModel.NetworkFormationModel.Error.minAttractionDistance"));
            if (remoteForceFactor < 0.0) throw new ArgumentOutOfRangeException(Messages.Get("Model.NetworkFormationModel.NetworkFormationModel.Error.remoteForceFactor"));

            if (minAttractionDistance >= maxAttractionDistance) throw new ArgumentOutOfRangeException(Messages.Get("Model.NetworkFormationModel.NetworkFormationModel.Error.minAttractionDistance-maxAttractionDistance"));
            if (maxRepulsionDistance >= minAttractionDistance) throw new ArgumentOutOfRangeException(Messages.Get("Model.NetworkFormationModel.NetworkFormationModel.Error.maxRepulsionDistance-minAttractionDistance"));
        
            m_adhesiveRepulsionFactor = adhesiveRepulsionFactor;
            m_attractionFactor = attractionFactor;
            m_lambda = lambda;
            m_maxAttractionDistance = maxAttractionDistance;
            m_maxRepulsionDistance = maxRepulsionDistance;
            m_minAttractionDistance = minAttractionDistance;
            m_remoteForceFactor = remoteForceFactor;

            m_reverseLambda = 1.0 / lambda;
            m_squareMaxAttractionDistance = maxAttractionDistance * maxAttractionDistance;

            m_cellList = new CellList(
                (int)(Config.Simulation.FieldRadius / maxAttractionDistance) + 1,
                Config.Simulation.Enable2DMode,
                maxAttractionDistance    
            );
        }

        public override bool UseCellAlgorithm => true;

        public override void BeforeAdvanceStep(ReadOnlySimulation sender, SimulationModelStepArgs args)
        {
        }

        public override Vector3 ComputeForceOnCell(ReadOnlySimulation sender, SimulationModelForceComputationArgs args)
        {
            Vector3 force1 = new Vector3();
            Vector3 force2 = new Vector3();
            Vector3 force3 = new Vector3();

            CellInfo info = new CellInfo(args.Target);

            foreach (ReadOnlyCell cell in args.Target.AttachedCells)
            {
                Vector3 diff = info.Position - cell.Position;
                double dist = diff.Length;

                double v = dist - m_minAttractionDistance;

                if (v > 0.0)
                {
                    force1 -= (v / dist) * diff;
                }
                else
                {
                    v = m_maxRepulsionDistance - dist;

                    if (v > 0.0)
                    {
                        force2 += (v / (m_maxRepulsionDistance * dist)) * diff;
                    }
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
                    if (!cellInfo.IsAlive) return;

                    Vector3 diff = info.Position - cellInfo.Position;
                    double mass = info.Mass * cellInfo.Mass;

                    force3 -= (mass * Math.Exp(-m_reverseLambda)) * diff;
                }
            );

            return m_attractionFactor * force1 + m_adhesiveRepulsionFactor * force2 + m_remoteForceFactor * force3;
        }

        public override void OnAdvanceStep(ReadOnlySimulation sender, SimulationModelStepArgs args)
        {
            foreach (Cell cell in args.Cells)
            {
                cell.ClearAttachedCells();
            }

            m_cellList.ResetCells();
            m_cellList.SetCells(args.Cells);

            Parallel.ForEach(
                args.Cells,
                cell =>
                {
                    CellAlgorithm.Enumerate(
                        this,
                        m_cellList,
                        cell,
                        args.Cells,
                        args.Fields,
                        cellInfo =>
                        {
                            if (!cellInfo.IsAlive) return;

#pragma warning disable CS8604 // Null 参照引数の可能性があります。
                            cell.Adhere(cellInfo.Source as Cell);
#pragma warning restore CS8604 // Null 参照引数の可能性があります。
                        }
                    );
                }
            );
        }
    }
}
