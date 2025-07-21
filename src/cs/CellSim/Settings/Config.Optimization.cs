using CellSim.Text;
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
            private static uint s_maxDegreeOfParallelism;
            private static readonly ParallelOptions s_parallelOptions = new ParallelOptions();
            private static PeformanceType s_peformance;

            public static uint MaxDegreeOfParallelism => s_maxDegreeOfParallelism;

            public static ParallelOptions ParallelOptions => s_parallelOptions;

            /// <summary>
            /// 実行速度とメモリ使用量の設定
            /// </summary>
            public static PeformanceType Peformance => s_peformance;

            internal static void Load(JsonNode? config)
            {
                if (config == null) throw new FormatException(Messages.Get("Settings.Config.Optimization.Load.Error.JsonError"));

                string s;
                int maxDegreeOfParallelism;
                try
                {
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                    s = config["peformance"].GetValue<string>();
                    maxDegreeOfParallelism = config["maxDegreeOfParallelism"].ToInt32();
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
                }
                catch
                {
                    throw new FormatException(Messages.Get("Settings.Config.Optimization.Load.Error.JsonError"));
                }

                s_peformance = s switch
                {
                    "Fast" => PeformanceType.Fast,
                    "LowMemory" => PeformanceType.LowMemory,
                    _ => throw new FormatException(Messages.Get("Settings.Config.Optimization.Load.Error.peformance"))
                };

                int maxThread = Environment.ProcessorCount;

                if (maxDegreeOfParallelism <= 0 || maxThread < maxDegreeOfParallelism) s_maxDegreeOfParallelism = (uint)maxThread;
                else s_maxDegreeOfParallelism = (uint)maxDegreeOfParallelism;

                s_parallelOptions.MaxDegreeOfParallelism = (int)s_maxDegreeOfParallelism;
            }
        }
    }
}
