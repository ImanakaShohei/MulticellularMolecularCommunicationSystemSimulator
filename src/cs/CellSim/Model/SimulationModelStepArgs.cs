using CellSim.Cells;
using CellSim.Molecular;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Model
{
    /// <summary>
    /// BeforeAdvanceStep(), OnAdvanceStep()の引数
    /// </summary>
    public struct SimulationModelStepArgs
    {
        public List<Cell> Cells;
        public IReadOnlyList<ReadOnlyMoleculeField> Fields;

        public SimulationModelStepArgs(List<Cell> cells, IReadOnlyList<ReadOnlyMoleculeField> fields)
        {
            Cells = cells;
            Fields = fields;
        }
    }
}
