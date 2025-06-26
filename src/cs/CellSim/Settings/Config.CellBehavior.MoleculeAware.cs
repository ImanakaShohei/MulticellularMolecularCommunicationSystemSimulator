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
            public static class MoleculeAware
            {
                private static double s_cellDivisionRadius;
                private static double s_degradationRate;
                private static double s_synthesisRate;

                /// <summary>
                /// 細胞の半径がこの値を超えると分裂する
                /// </summary>
                public static double CellDivisionRadius => s_cellDivisionRadius;

                /// <summary>
                /// 分解係数 k2
                /// </summary>
                public static double DegradationRate => s_degradationRate;

                /// <summary>
                /// 生成係数 k1
                /// </summary>
                public static double SynthesisRate => s_synthesisRate;

                internal static void Load(JsonObject config)
                {
                    try
                    {
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                        s_cellDivisionRadius = config["cellDivisionRadius"].GetValue<double>();
                        s_degradationRate = config["degradationRate"].GetValue<double>();
                        s_synthesisRate = config["synthesisRate"].GetValue<double>();
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
                    }
                    catch
                    {
                        throw new FormatException(Messages.Get("Settings.Config.CellBehavior.MoleculeAware.Load.Error.JsonError"));
                    }

                    if (s_cellDivisionRadius <= 0.0) throw new FormatException(Messages.Get("Settings.Config.CellBehavior.MoleculeAware.Load.Error.cellDivisionRadius"));
                    if (s_degradationRate <= 0.0) throw new FormatException(Messages.Get("Settings.Config.CellBehavior.MoleculeAware.Load.Error.degradationRate"));
                    if (s_synthesisRate <= 0.0) throw new FormatException(Messages.Get("Settings.Config.CellBehavior.MoleculeAware.Load.Error.synthesisRate"));
                }
            }
        }
    }
}
