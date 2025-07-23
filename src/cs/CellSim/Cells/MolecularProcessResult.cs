using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cells
{
    public struct MolecularProcessResult
    {
        /// <summary>
        /// 細胞外の分子の変化量
        /// </summary>
        public double ExtracellularChange;

        /// <summary>
        /// 細胞内の分子の変化量
        /// </summary>
        public double IntracellularChange;

        public MolecularProcessResult()
        {
            ExtracellularChange = 0;
            IntracellularChange = 0;
        }

        public MolecularProcessResult(
            double extracellularChange,
            double intracellularChange
        )
        {
            ExtracellularChange = extracellularChange;
            IntracellularChange = intracellularChange;
        }
    }
}
