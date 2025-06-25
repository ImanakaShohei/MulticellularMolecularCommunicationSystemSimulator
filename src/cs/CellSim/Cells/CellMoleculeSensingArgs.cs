using CellSim.Molecular;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cells
{
    public struct CellMoleculeSensingArgs
    {
        public ReadOnlyMoleculeField Field;

        public CellMoleculeSensingArgs(ReadOnlyMoleculeField field)
        {
            Field = field;
        }
    }
}
