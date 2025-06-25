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
        public CellAlgorithm CellAlgorithm;
        public IReadOnlyList<ReadOnlyCell> Cells;
        public IReadOnlyList<ReadOnlyMoleculeField> Fields;
        public ReadOnlyCell Target;

        public SimulationModelForceComputationArgs(
            CellAlgorithm cellAlgorithm,
            IReadOnlyList<ReadOnlyCell> cells,
            IReadOnlyList<ReadOnlyMoleculeField> fields,
            ReadOnlyCell target
        )
        {
            CellAlgorithm = cellAlgorithm;
            Cells = cells;
            Fields = fields;
            Target = target;
        }
    }
}
