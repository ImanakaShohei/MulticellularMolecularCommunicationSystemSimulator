using CellSim.Cells;
using CellSim.Model;
using CellSim.Numerics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.CellAlgorithms
{
    public class NullAlgorithm : CellAlgorithm
    {
        public override bool HasMultithreadingSupport => true;

        public override void BeforeAdvanceStep(ReadOnlySimulation sender, CellAlgorithmStepArgs args)
        {
        }

        public override IEnumerable<CellInfo> EnumerateAffectableCellInfos(CellSimulationModel sender, CellAlgorithmAffectableCellQueryArgs args)
        {
            yield break;
        }

        public override List<CellInfo> GetAffectableCellInfos(CellSimulationModel sender, CellAlgorithmAffectableCellQueryArgs args)
        {
            return [];
        }

        public override void OnAdvanceStep(ReadOnlySimulation sender, CellAlgorithmStepArgs args)
        {
        }
    }
}
