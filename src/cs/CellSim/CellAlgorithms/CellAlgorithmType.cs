using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.CellAlgorithms
{
    /// <summary>
    /// CellAlgorithmの種類
    /// </summary>
    public enum CellAlgorithmType
    {
        BarnesHut,
        CellList,
        Naive,
        Null,
        ParticleMesh,
        User,
    }
}
