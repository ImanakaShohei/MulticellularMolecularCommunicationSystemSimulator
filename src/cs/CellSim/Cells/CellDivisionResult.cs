using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cells
{
    public struct CellDivisionResult
    {
        public DaughterCellInfo OriginalDaughter;
        public DaughterCellInfo NewDaughter;

        public CellDivisionResult(DaughterCellInfo originalDaughter, DaughterCellInfo newDaughter)
        {
            OriginalDaughter = originalDaughter;
            NewDaughter = newDaughter;
        }
    }
}
