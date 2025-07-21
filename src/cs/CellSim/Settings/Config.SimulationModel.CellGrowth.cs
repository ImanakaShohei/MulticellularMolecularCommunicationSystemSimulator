using CellSim.Model;
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
        public static partial class SimulationModel
        {
            public static class CellGrowth
            {
                private static double s_adhesiveRepulsionFactor;

                /// <summary>
                /// くっついた細胞同士に働く反発力の係数
                /// </summary>
                public static double AdhesiveRepulsionFactor => s_adhesiveRepulsionFactor;

                internal static void Load(JsonNode? config)
                {
                    if (config == null) return;

                    try
                    {
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                        s_adhesiveRepulsionFactor = config["adhesiveRepulsionFactor"].ToDouble();
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
                    }
                    catch
                    {
                        throw new FormatException(Messages.Get("Settings.Config.SimulationModel.CellGrowth.Load.Error.JsonError"));
                    }

                    if (s_adhesiveRepulsionFactor < 0.0) throw new FormatException(Messages.Get("Settings.Config.SimulationModel.CellGrowth.Load.Error.adhesiveRepulsionFactor"));
                }
            }

        }

    }
}
