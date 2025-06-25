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
        public static class Optimization
        {
            private static PeformanceType s_peformance;

            /// <summary>
            /// 実行速度とメモリ使用量の設定
            /// </summary>
            public static PeformanceType Peformance => s_peformance;

            internal static void Load(JsonObject config)
            {
                throw new NotImplementedException();
            }
        }
    }
}
