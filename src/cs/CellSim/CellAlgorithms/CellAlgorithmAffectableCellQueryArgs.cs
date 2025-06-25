using CellSim.Cells;
using CellSim.Molecular;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.CellAlgorithms
{
    public struct CellAlgorithmAffectableCellQueryArgs
    {
        public IReadOnlyList<ReadOnlyCell> Cells;
        public IReadOnlyList<ReadOnlyMoleculeField> Fields;
        public ReadOnlyCell Target;

        public CellAlgorithmAffectableCellQueryArgs(
            IReadOnlyList<ReadOnlyCell> cells,
            IReadOnlyList<ReadOnlyMoleculeField> fields,
            ReadOnlyCell target
        )
        {
            Cells = cells;
            Fields = fields;
            Target = target;
        }
    }
}
