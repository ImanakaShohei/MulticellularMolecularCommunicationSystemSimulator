using CellSim.Numerics;
using CellSim.Users;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cells
{
    public abstract class CellBehavior
    {
        public static CellBehavior FromType(CellBehaviorType type)
        {
            return type switch
            {
                CellBehaviorType.MoleculeAware => new MoleculeAwareCellBehavior(),
                CellBehaviorType.Normal => new NormalCellBehavior(),
                CellBehaviorType.User => new UserCellBehavior(),
                CellBehaviorType.WavePropagation => new WavePropagationCellBehavior(),
                _ => throw new NotSupportedException(Messages.Get("Cells.CellBehaviorPtr.FromType.Error")),
            };
        }

        public abstract CellBehavior Clone();

        /// <summary>
        /// 細胞の成長度合いを計算
        /// </summary>
        /// <param name="sender">この関数を呼び出した細胞インスタンス</param>
        /// <returns>計算結果</returns>
        public abstract CellGrowthResult ComputeGrowth(ReadOnlyCell sender);

        public abstract MolecularProcessResult ComputeMolecularProcess(ReadOnlyCell sender, MolecularProcessArgs args);

        /// <summary>
        /// 細胞分裂後の細胞の状態を定義
        /// </summary>
        /// <param name="sender">この関数を呼び出した細胞インスタンス</param>
        /// <returns>分裂後の2つの細胞の状態</returns>
        public abstract CellDivisionResult ComputeDivisionOutcome(ReadOnlyCell sender);

        /// <summary>
        /// Cell.SenseMolecules()から呼ばれる関数
        /// </summary>
        /// <param name="sender">この関数を呼び出した細胞インスタンス</param>
        /// <param name="args">処理に必要な情報</param>
        /// <returns>分子から受ける力</returns>
        public abstract Vector3 OnSenseMolecules(ReadOnlyCell sender, CellMoleculeSensingArgs args);

        /// <summary>
        /// このステップで細胞が分裂するかを定義
        /// </summary>
        /// <param name="sender">この関数を呼び出した細胞インスタンス</param>
        /// <returns>細胞が分裂するかどうか</returns>
        public abstract bool ShouldDivideThisStep(ReadOnlyCell sender);
    }
}
