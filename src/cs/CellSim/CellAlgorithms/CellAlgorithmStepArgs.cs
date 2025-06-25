using CellSim.Cells;
using CellSim.Molecular;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.CellAlgorithms
{
    /// <summary>
    /// BeforeAdvanceStep(), OnAdvanceStep()の引数
    /// </summary>
    public struct CellAlgorithmStepArgs
    {
        public IReadOnlyList<ReadOnlyCell> Cells;
        public IReadOnlyList<ReadOnlyMoleculeField> Fields;

        public CellAlgorithmStepArgs(
            IReadOnlyList<ReadOnlyCell> cells,
            IReadOnlyList<ReadOnlyMoleculeField> fields
        )
        {
            Cells = cells;
            Fields = fields;
        }
    }
}
