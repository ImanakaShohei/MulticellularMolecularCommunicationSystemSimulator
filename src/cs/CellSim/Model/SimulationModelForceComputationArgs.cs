using CellSim.CellAlgorithms;
using CellSim.Cells;
using CellSim.Molecular;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Model
{
    public struct SimulationModelForceComputationArgs
    {
        public IReadOnlyList<ReadOnlyCell> AffectedCells;
        public CellAlgorithm? CellAlgorithm;
        public IReadOnlyList<ReadOnlyCell> Cells;
        public IReadOnlyList<ReadOnlyMoleculeField> Fields;
        public ReadOnlyCell Target;

        public SimulationModelForceComputationArgs(
            ReadOnlyCell target,
            IReadOnlyList<ReadOnlyCell> cells,
            IReadOnlyList<ReadOnlyCell> affectedCells,
            IReadOnlyList<ReadOnlyMoleculeField> fields,
            CellAlgorithm? cellAlgorithm
        )
        {
            AffectedCells = affectedCells;
            CellAlgorithm = cellAlgorithm;
            Cells = cells;
            Fields = fields;
            Target = target;
        }
    }
}
