using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Numerics
{
    public struct GridPosition3
    {
        public int X;
        public int Y;
        public int Z;

        public GridPosition3() : this(0, 0, 0)
        {
        }

        public GridPosition3(int x, int y, int z)
        {
            X = x;
            Y = y;
            Z = z;
        }
    }
}
