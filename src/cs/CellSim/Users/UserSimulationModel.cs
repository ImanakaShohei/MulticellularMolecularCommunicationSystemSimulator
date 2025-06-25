using CellSim.Cells;
using CellSim.Model;
using CellSim.Numerics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Users
{
    /// <summary>
    /// ユーザー定義力学モデル
    /// </summary>
    public class UserSimulationModel : CellSimulationModel
    {
        public UserSimulationModel()
        {
            // TODO: ここに処理を追加します
        }

        // TODO: ComputeForceOnCell()で引数cellAlgorithmを使用する場合は'true'に置き換えます
        public override bool UseCellAlgorithm => false;

        public override void BeforeAdvanceStep(ReadOnlySimulation sender, SimulationModelStepArgs args)
        {
            // TODO: ここに処理を追加します
        }

        public override Vector3 ComputeForceOnCell(ReadOnlySimulation sender, SimulationModelForceComputationArgs args)
        {
            // TODO: ここに処理を追加します

            return Vector3.Zero;
        }

        public override void InitializeCells(ReadOnlySimulation sender, List<Cell> cells)
        {
            // TODO: ここに処理を追加します
            base.InitializeCells(sender, cells);
        }

        public override void OnAdvanceStep(ReadOnlySimulation sender, SimulationModelStepArgs args)
        {
            // TODO: ここに処理を追加します
        }
    }
}
