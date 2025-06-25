using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Model
{
    /// <summary>
    /// モデルの種類
    /// </summary>
    public enum CellSimulationType
    {
        CellGrowth,
        ClusterFormation,
        ClusterRotation,
        ClusterSprouting,
        NetworkFormation,
        Null,
        User,
    }
}
