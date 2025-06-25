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
            public static class Normal
            {
                private static double s_cellDivisionRadius;

                /// <summary>
                /// 細胞の半径がこの値を超えると分裂する
                /// </summary>
                public static double CellDivisionRadius => s_cellDivisionRadius;

                internal static void Load(JsonObject config)
                {
                    throw new NotImplementedException();
                }
            }
        }
    }
}
