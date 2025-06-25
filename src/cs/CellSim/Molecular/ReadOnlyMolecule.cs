using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Molecular
{
    public class ReadOnlyMolecule
    {
        /// <summary>
        /// 分子の量
        /// </summary>
        protected double m_amount;

        /// <summary>
        /// 分子の種類
        /// </summary>
        protected readonly MoleculeKind m_kind;

        public ReadOnlyMolecule(MoleculeKind kind) : this(0, kind)
        {
        }

        public ReadOnlyMolecule(double amount, MoleculeKind kind)
        {
            m_amount = amount;
            m_kind = kind;
        }

        /// <summary>
        /// 分子の量
        /// </summary>
        public double Amount => m_amount;

        /// <summary>
        /// 分子の種類
        /// </summary>
        public MoleculeKind Kind => m_kind;
    }
}
