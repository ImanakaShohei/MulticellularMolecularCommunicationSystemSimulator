using CellSim.Numerics;
using CellSim.Settings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cells
{
    /// <summary>
    /// 分子の影響を考慮したクラス
    /// </summary>
    public class MoleculeAwareCellBehavior : NormalCellBehavior
    {
        /// <summary>
        /// 細胞の半径がこの値を超えると分裂する
        /// </summary>
        private double m_cellDivisionRadius;

        /// <summary>
        /// 生成係数 k1
        /// </summary>
        private double m_synthesisRate;

        /// <summary>
        /// 分解係数 k2
        /// </summary>
        private double m_degradationRate;

        public MoleculeAwareCellBehavior()
            : this(
                Config.CellBehavior.MoleculeAware.CellDivisionRadius,
                Config.CellBehavior.MoleculeAware.SynthesisRate,
                Config.CellBehavior.MoleculeAware.DegradationRate
            )
        {
        }

        public MoleculeAwareCellBehavior(
            double cellDivisionRadius,
            double synthesisRate,
            double degradationRate
        )
        {
            if (cellDivisionRadius <= 0.0) throw new ArgumentOutOfRangeException(Messages.Get("Cells.MoleculeAwareCellBehavior.MoleculeAwareCellBehavior.Error.cellDivisionRadius"));
            if (synthesisRate <= 0.0) throw new ArgumentOutOfRangeException(Messages.Get("Cells.MoleculeAwareCellBehavior.MoleculeAwareCellBehavior.Error.synthesisRate"));
            if (degradationRate <= 0.0) throw new ArgumentOutOfRangeException(Messages.Get("Cells.MoleculeAwareCellBehavior.MoleculeAwareCellBehavior.Error.degradationRate"));
        
            m_cellDivisionRadius = cellDivisionRadius;
            m_synthesisRate = synthesisRate;
            m_degradationRate = degradationRate;
        }

        public override double ComputeMetabolicChange(ReadOnlyCell sender, CellMetabolicArgs args)
        {
            return (m_synthesisRate - m_degradationRate * args.MoleculeInfo.Amount) * Config.Simulation.DeltaTime;
        }

        public override Vector3 OnSenseMolecules(ReadOnlyCell sender, CellMoleculeSensingArgs args)
        {
            // TODO: ここに処理を追加します
            return Vector3.Zero;
        }

        public override bool ShouldDivideThisStep(ReadOnlyCell sender)
        {
            return sender.Radius > m_cellDivisionRadius;
        }
    }
}
