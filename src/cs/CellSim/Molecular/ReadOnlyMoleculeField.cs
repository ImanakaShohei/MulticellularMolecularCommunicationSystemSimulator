using CellSim.Cells;
using CellSim.Containers;
using CellSim.Numerics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Molecular
{
    public class ReadOnlyMoleculeField
    {
        
        protected double[,,] m_concentrations;
        private MoleculeKind m_kind;

        public ReadOnlyArray3<double> Concentrations => new(m_concentrations);

        public MoleculeKind Kind => m_kind;

        public GridPosition3 ToGridPosition3(ReadOnlyCell cell) => ToGridPosition3(cell.Position);

        public GridPosition3 ToGridPosition3(Vector3 position)
        {
            throw new NotImplementedException();
        }
    }
}
