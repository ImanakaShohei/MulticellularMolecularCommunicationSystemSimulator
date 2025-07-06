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
                string s;

                try
                {
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                    s_cellCount = config["cellCount"].GetValue<int>();
                    s_enableGrowth = config["enableGrowth"].GetValue<bool>();
                    s_growthRate = config["growthRate"].GetValue<double>();
                    s_initialPlacementRadius = config["initialPlacementRadius"].GetValue<double>();
                    s_isSensitiveToMolecules = config["isSensitiveToMolecules"].GetValue<bool>();
                    s_initialPlacementSeed = config["initialPlacementSeed"].GetValue<int>();
                    s_mass = config["mass"].GetValue<double>();
                    s_radius = config["radius"].GetValue<double>();
                    s = config["type"].GetValue<string>();
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
                }
                catch {
                    Console.WriteLine(config);
                    throw new FormatException(Messages.Get("Settings.Config.Cell.Load.Error.JsonError"));
                }

                if (s_cellCount == 0) throw new FormatException(Messages.Get("Settings.Config.Cell.Load.Error.cellCount"));
                if (s_growthRate <= 0) throw new FormatException(Messages.Get("Settings.Config.Cell.Load.Error.growthRate"));
                if (s_initialPlacementRadius <= 0) throw new FormatException(Messages.Get("Settings.Config.Cell.Load.Error.initialPlacementRadius"));
                if (s_mass == 0) throw new FormatException(Messages.Get("Settings.Config.Cell.Load.Error.mass"));
                if (s_radius == 0) throw new FormatException(Messages.Get("Settings.Config.Cell.Load.Error.radius"));
                if (s_cellCount == 0) throw new FormatException(Messages.Get("Settings.Config.Cell.Load.Error.radius"));

                if (s == "Normal") s_type = CellType.Normal;
                else throw new FormatException(Messages.Get("Settings.Config.Cell.Load.Error.type"));
            }
        }
    }
}
