using CellSim.Molecular;
using CellSim.Numerics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cells
{
    public struct MolecularProcessArgs
    {
        /// <summary>
        /// 細胞外の分子の量
        /// </summary>
        public double ExtracellularAmount;

        /// <summary>
        /// 分子空間
        /// </summary>
        public ReadOnlyMoleculeField Field;

        /// <summary>
        /// 細胞内の分子の量
        /// </summary>
        public double IntracellularAmount;

        /// <summary>
        /// 分子の種類
        /// </summary>
        public MoleculeKind Kind;

        /// <summary>
        /// 分子空間上の細胞の位置
        /// </summary>
        public GridPosition3 Position;

        public MolecularProcessArgs(
            double extracellularAmount,
            ReadOnlyMoleculeField field,
            double intracellularAmount,
            MoleculeKind kind,
            GridPosition3 position
        )
        {
            ExtracellularAmount = extracellularAmount;
            Field = field;
            IntracellularAmount = intracellularAmount;
            Kind = kind;
            Position = position;
        }
        
    }
}
