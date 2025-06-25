using CellSim.Numerics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cells
{
    /// <summary>
    /// 細胞分裂で使う
    /// </summary>
    public struct DaughterCellInfo
    {
        public double NewMass;
        public double NewRadius;
        public Vector3 NewPosition;

        public DaughterCellInfo(double newMass, double newRadius, Vector3 newPosition)
        {
            NewMass = newMass;
            NewRadius = newRadius;
            NewPosition = newPosition;
        }
    }
}
