using CellSim.CellAlgorithms;
using CellSim.Cells;
using CellSim.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Users
{
    public class UserCellAlgorithm : CellAlgorithm
    {
        // TODO: 複数スレッドによる処理ができない場合は'false'にします
        public override bool HasMultithreadingSupport => true;

        public override void BeforeAdvanceStep(ReadOnlySimulation sender, CellAlgorithmStepArgs args)
        {
            // TODO: ここに処理を追加します
        }

        public override IEnumerable<CellInfo> EnumerateAffectableCellInfos(CellSimulationModel sender, CellAlgorithmAffectableCellQueryArgs args)
        {
            //: ここに処理を追加します
            yield break;
        }

        public override List<CellInfo> GetAffectableCellInfos(CellSimulationModel sender, CellAlgorithmAffectableCellQueryArgs args)
        {
            //: ここに処理を追加します
            return [];
        }

        public override void OnAdvanceStep(ReadOnlySimulation sender, CellAlgorithmStepArgs args)
        {
            // TODO: ここに処理を追加します
        }
    }
}
