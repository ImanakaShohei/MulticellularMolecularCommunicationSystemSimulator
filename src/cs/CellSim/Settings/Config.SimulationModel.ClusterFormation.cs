using CellSim.Model;
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
            public static class ClusterFormation
            {
                private static double s_adhesiveRepulsionFactor;
                private static double s_lambda;
                private static double s_remoteForceFactor;

                /// <summary>
                /// くっついた細胞同士に働く反発力の係数
                /// </summary>
                public static double AdhesiveRepulsionFactor => s_adhesiveRepulsionFactor;

                /// <summary>
                /// 
                /// </summary>
                public static double Lambda => s_lambda;

                /// <summary>
                /// 遠隔力の係数
                /// </summary>
                public static double RemoteForceFactor => s_remoteForceFactor;

                internal static void Load(JsonObject config)
                {
                    try
                    {
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                        s_adhesiveRepulsionFactor = config["adhesiveRepulsionFactor"].GetValue<double>();
                        s_lambda = config["lambda"].GetValue<double>();
                        s_remoteForceFactor = config["remoteForceFactor"].GetValue<double>();
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
                    }
                    catch
                    {
                        throw new FormatException(Messages.Get("Settings.Config.SimulationModel.ClusterFormation.Load.Error.JsonError"));
                    }

                    if (s_adhesiveRepulsionFactor < 0.0) throw new FormatException(Messages.Get("Settings.Config.SimulationModel.ClusterFormation.Load.Error.adhesiveRepulsionFactor"));
                    if (s_lambda == 0.0) throw new FormatException(Messages.Get("Settings.Config.SimulationModel.ClusterFormation.Load.Error.lambda"));
                    if (s_remoteForceFactor < 0.0) throw new FormatException(Messages.Get("Settings.Config.SimulationModel.ClusterFormation.Load.Error.remoteForceFactor"));
                }
            }

        }

    }
}
