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
    public class CellGrowthModel : CellSimulationModel
    {
        private readonly double m_adhesiveRepulsionFactor;

        public CellGrowthModel() : this(Config.SimulationModel.CellGrowth.AdhesiveRepulsionFactor)
        {
        }

        public CellGrowthModel(double adhesiveRepulsionFactor)
        {
            if (adhesiveRepulsionFactor < 0) throw new ArgumentOutOfRangeException(Messages.Get("Model.CellGrowthModel.CellGrowthModel.Error.adhesiveRepulsionFactor"));
            m_adhesiveRepulsionFactor = adhesiveRepulsionFactor;
        }

        public override bool UseCellAlgorithm => true;

        public override void BeforeAdvanceStep(ReadOnlySimulation sender, SimulationModelStepArgs args)
        {
        }

        public override Vector3 ComputeForceOnCell(ReadOnlySimulation sender, SimulationModelForceComputationArgs args)
        {
            CellInfo info = new CellInfo(args.Target);
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
                    double sumRadius = info.Radius + cellInfo.Radius;

                    if (dist < sumRadius)
                    {
                        double tmp = 1.0 - dist / sumRadius;

                        vec += diff * (tmp * tmp);
                    }
                }
            );

            return m_adhesiveRepulsionFactor * vec;
        }

        public override void OnAdvanceStep(ReadOnlySimulation sender, SimulationModelStepArgs args)
        {
        }
    }
}
