using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Molecular
{
    /// <summary>
    /// 分子クラス
    /// </summary>
    public sealed class Molecule : ReadOnlyMolecule
    {
        public Molecule(MoleculeKind kind) : base(kind)
        {
        }

        public Molecule(double amount, MoleculeKind kind) : base(amount, kind)
        {
        }

        /// <summary>
        /// 分子の量
        /// </summary>
        public new double Amount
        {
            get { return m_amount; }
            set
            {
                if (value < 0) ArgumentOutOfRangeException.ThrowIfNegative(m_amount, nameof(value));
                m_amount = value;
            }
        }

        /// <summary>
        /// 分子の量を設定
        /// </summary>
        /// <param name="amount">量</param>
        public void SetAmountUnsafe(double amount)
        {
            m_amount = amount;
        }
    }
}
