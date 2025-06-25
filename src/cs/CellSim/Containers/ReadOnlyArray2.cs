using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Containers
{
    public readonly struct ReadOnlyArray2<T>
    {
        private readonly T[,] m_array;

        public ReadOnlyArray2(T[,] array)
        {
            m_array = array;
        }

        public T this[int x, int y] => m_array[x, y];

        public int Length => m_array.Length;
    }
}
