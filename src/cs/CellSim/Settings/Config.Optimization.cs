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
                string s;
                try
                {
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                    s = config["peformance"].GetValue<string>();
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
                }
                catch
                {
                    throw new FormatException(Messages.Get("Settings.Config.Optimization.Load.Error.JsonError"));
                }

                if (s == "Fast") s_peformance = PeformanceType.Fast;
                else if (s == "LowMemory") s_peformance = PeformanceType.LowMemory;
                else throw new FormatException(Messages.Get("Settings.Config.Optimization.Load.Error.peformance"));
            }
        }
    }
}
