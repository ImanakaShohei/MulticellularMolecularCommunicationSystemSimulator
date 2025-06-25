using CellSim.Cells;
using CellSim.Numerics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Users
{
    public class UserCellBehavior : CellBehavior
    {
        public UserCellBehavior()
        {

        }

        public override CellBehavior Clone()
        {
            // ここはいじらない
            return new UserCellBehavior();
        }

        public override CellDivisionResult ComputeDivisionOutcome(ReadOnlyCell sender)
        {
            CellDivisionResult result = new CellDivisionResult();

            // TODO: ここに処理を追加します

            return result;
        }

        public override CellGrowthResult ComputeGrowth(ReadOnlyCell sender)
        {
            CellGrowthResult result = new CellGrowthResult();

            // TODO: resultに値を格納します

            return result;
        }

        public override double ComputeMetabolicChange(ReadOnlyCell sender, CellMetabolicArgs args)
        {
            // TODO: ここに処理を追加します
            return 0.0;
        }

        public override double ComputeMoleculeEmitAmount(ReadOnlyCell sender, CellMoleculeEmissionArgs args)
        {
            // TODO: 放出量を計算します
            return 0.0;
        }

        public override Vector3 OnSenseMolecules(ReadOnlyCell sender, CellMoleculeSensingArgs args)
        {
            // TODO: ここに処理を追加します
            return Vector3.Zero;
        }

        public override bool ShouldDivideThisStep(ReadOnlyCell sender)
        {
            // TODO: ここに処理を追加します
            return false;
        }
    }
}
