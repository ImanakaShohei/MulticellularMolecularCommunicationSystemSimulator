using CellSim.Cells;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Nodes;
using System.Threading.Tasks;

namespace CellSim.Settings
{
    public static partial class Config
    {
        public static partial class CellBehavior
        {
            private static CellBehaviorType s_behaviorType;

            /// <summary>
            /// ふるまい定義
            /// </summary>
            public static CellBehaviorType BehaviorType => s_behaviorType;

            internal static void Load(JsonObject config)
            {
                throw new NotImplementedException();
            }
        }

    }
}
