using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cells
{
    /// <summary>
    /// CellBehavior.ComputeGrowth()の戻り値
    /// </summary>
    public struct CellGrowthResult
    {
        /// <summary>
        /// 成長後の質量
        /// </summary>
        public double NewMass;

        /// <summary>
        /// 成長後の半径
        /// </summary>
        public double NewRadius;

        public CellGrowthResult(double newMass, double newRadius)
        {
            NewMass = newMass;
            NewRadius = newRadius;
        }
    }
}
