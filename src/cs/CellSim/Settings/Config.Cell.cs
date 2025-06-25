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
        /// <summary>
        /// 細胞設定
        /// </summary>
        public static class Cell
        {
            private static int s_cellCount;
            private static bool s_enableGrowth;
            private static double s_growthRate;
            private static double s_initialPlacementRadius;
            private static bool s_isSensitiveToMolecules;
            private static int s_initialPlacementSeed;
            private static double s_mass;
            private static double s_radius;
            private static CellType s_type;

            /// <summary>
            /// 細胞の初期数
            /// </summary>
            public static int CellCount => s_cellCount;

            /// <summary>
            /// 細胞の成長・分裂を有効にするかどうか
            /// </summary>
            public static bool EnableGrowth => s_enableGrowth;

            /// <summary>
            /// 細胞の成長速度
            /// </summary>
            public static double GrowthRate => s_growthRate;

            /// <summary>
            /// 細胞が配置される円・球の半径
            /// </summary>
            public static double InitialPlacementRadius => s_initialPlacementRadius;

            /// <summary>
            /// 細胞の初期配置を決めるシード値
            /// </summary>
            public static int InitialPlacementSeed => s_initialPlacementSeed;

            /// <summary>
            /// 細胞が周囲の分子の影響を受けるかどうか
            /// </summary>
            public static bool IsSensitiveToMolecules => s_isSensitiveToMolecules;

            /// <summary>
            /// 細胞の初期質量
            /// </summary>
            public static double Mass => s_mass;

            /// <summary>
            /// 細胞の初期半径
            /// </summary>
            public static double Radius => s_radius;

            /// <summary>
            /// 細胞の種類
            /// </summary>
            public static CellType Type => s_type;

            internal static void Load(JsonObject config)
            {
                throw new NotImplementedException();
            }
        }
    }
}
