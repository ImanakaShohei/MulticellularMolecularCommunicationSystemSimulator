using CellSim.Cells;
using CellSim.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.CellAlgorithms
{
    public class NaiveAlgorithm : CellAlgorithm
    {
        public override bool HasMultithreadingSupport => true;

        public override void BeforeAdvanceStep(ReadOnlySimulation sender, CellAlgorithmStepArgs args)
        {
        }

        public override IEnumerable<CellInfo> EnumerateAffectableCellInfos(CellSimulationModel sender, CellAlgorithmAffectableCellQueryArgs args)
        {
            foreach (ReadOnlyCell cell in args.Cells)
            {
                yield return new CellInfo(cell);
            }
        }

        public override List<CellInfo> GetAffectableCellInfos(CellSimulationModel sender, CellAlgorithmAffectableCellQueryArgs args)
        {
            List<CellInfo> list = new List<CellInfo>();
            list.Capacity = args.Cells.Count == 0 ? 0 : args.Cells.Count - 1;

            foreach (ReadOnlyCell cell in args.Cells)
            {
                list.Add(new CellInfo(cell));
            }

            return list;
        }

        public override void OnAdvanceStep(ReadOnlySimulation sender, CellAlgorithmStepArgs args)
        {
        }
    }
}
