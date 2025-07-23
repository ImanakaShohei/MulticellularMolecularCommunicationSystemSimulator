using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Containers
{
    public readonly struct ReadOnlyArray3<T>
    {
        private readonly T[,,] m_array;

        public ReadOnlyArray3(T[,,] array)
        {
            m_array = array;
        }

        public T this[int x, int y, int z] => m_array[x, y, z];

        public int Length => m_array.Length;

        public T At(int x, int y, int z) => m_array[x, y, z];
    }
}
