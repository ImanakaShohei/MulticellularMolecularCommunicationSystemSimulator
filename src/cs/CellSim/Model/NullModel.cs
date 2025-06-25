using CellSim.Cells;
using CellSim.Numerics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Model
{
    /// <summary>
    /// 何もしない力学モデル
    /// </summary>
    public class NullModel : CellSimulationModel
    {
        public override bool UseCellAlgorithm => false;

        public override void BeforeAdvanceStep(ReadOnlySimulation sender, SimulationModelStepArgs args)
        {
            return;
        }

        public override Vector3 ComputeForceOnCell(ReadOnlySimulation sender, SimulationModelForceComputationArgs args)
        {
            return Vector3.Zero;
        }

        public override void InitializeCells(ReadOnlySimulation sender, List<Cell> cells)
        {
        }

        public override void OnAdvanceStep(ReadOnlySimulation sender, SimulationModelStepArgs args)
        {
            return;
        }
    }
}
