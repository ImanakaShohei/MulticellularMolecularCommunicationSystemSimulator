using CellSim.Cells;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Molecular
{
    public class MoleculeField : ReadOnlyMoleculeField
    {
        public new double[,,] Concentrations => m_concentrations;

        public void BeforeAdvanceStep(IReadOnlyList<ReadOnlyCell> cells)
        {

        }

        public void OnAdvanceStep(IReadOnlyList<ReadOnlyCell> cells)
        {

        }
    }
}
