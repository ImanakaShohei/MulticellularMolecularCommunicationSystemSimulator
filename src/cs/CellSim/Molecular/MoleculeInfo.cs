using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Molecular
{
    public struct MoleculeInfo
    {
        /// <summary>
        /// 分子の量
        /// </summary>
        public double Amount;

        /// <summary>
        /// 分子の種類
        /// </summary>
        public MoleculeKind Kind;

        public MoleculeInfo(double amount, MoleculeKind kind)
        {
            Amount = amount;
            Kind = kind;
        }
    }
}
