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
            public static class NetworkFormation
            {
                private static double s_adhesiveRepulsionFactor;
                private static double s_attractionFactor;
                private static double s_lambda;
                private static double s_maxAttractionDistance;
                private static double s_maxRepulsionDistance;
                private static double s_minAttractionDistance;
                private static double s_remoteForceFactor;

                /// <summary>
                /// くっついた細胞同士に働く反発力の係数
                /// </summary>
                public static double AdhesiveRepulsionFactor => s_adhesiveRepulsionFactor;

                /// <summary>
                /// 接着した細胞同士にかかる引力の係数
                /// </summary>
                public static double AttributeActionFactor => s_attractionFactor;

                public static double Lambda => s_lambda;

                /// <summary>
                /// 接着可能な最大距離
                /// </summary>
                public static double MaxAttractionDistance => s_maxAttractionDistance;

                /// <summary>
                /// 反発力が働く最大距離
                /// </summary>
                public static double MaxRepulsionDistance => s_maxRepulsionDistance;

                /// <summary>
                /// 接着可能な最小距離
                /// </summary>
                public static double MinAttractionDistance => s_minAttractionDistance;

                /// <summary>
                /// 遠隔力の係数
                /// </summary>
                public static double RemoteForceFactor => s_remoteForceFactor;

                internal static void Load(JsonNode? config)
                {
                    if (config == null) return;

                    try
                    {
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                        s_adhesiveRepulsionFactor = config["adhesiveRepulsionFactor"].ToDouble();
                        s_attractionFactor = config["attractionFactor"].ToDouble();
                        s_lambda = config["lambda"].ToDouble();
                        s_maxAttractionDistance = config["maxAttractionDistance"].ToDouble();
                        s_maxRepulsionDistance = config["maxRepulsionDistance"].ToDouble();
                        s_minAttractionDistance = config["minAttractionDistance"].ToDouble();
                        s_remoteForceFactor = config["remoteForceFactor"].ToDouble();
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
                    }
                    catch
                    {
                        throw new FormatException(Messages.Get("Settings.Config.SimulationModel.NetworkFormation.Load.Error.JsonError"));
                    }

                    if (s_adhesiveRepulsionFactor < 0.0) throw new FormatException(Messages.Get("Settings.Config.SimulationModel.NetworkFormation.Load.Error.adhesiveRepulsionFactor"));
                    if (s_attractionFactor < 0.0) throw new FormatException(Messages.Get("Settings.Config.SimulationModel.NetworkFormation.Load.Error.attractionFactor"));
                    if (s_lambda == 0.0) throw new FormatException(Messages.Get("Settings.Config.SimulationModel.NetworkFormation.Load.Error.lambda"));
                    if (s_maxAttractionDistance <= 0.0) throw new FormatException(Messages.Get("Settings.Config.SimulationModel.NetworkFormation.Load.Error.maxAttractionDistance"));
                    if (s_maxRepulsionDistance <= 0.0) throw new FormatException(Messages.Get("Settings.Config.SimulationModel.NetworkFormation.Load.Error.maxRepulsionDistance"));
                    if (s_minAttractionDistance <= 0.0) throw new FormatException(Messages.Get("Settings.Config.SimulationModel.NetworkFormation.Load.Error.minAttractionDistance"));
                    if (s_remoteForceFactor < 0.0) throw new FormatException(Messages.Get("Settings.Config.SimulationModel.NetworkFormation.Load.Error.remoteForceFactor"));

                    if (s_minAttractionDistance >= s_maxAttractionDistance) throw new FormatException(Messages.Get("Settings.Config.SimulationModel.NetworkFormation.Load.Error.minAttractionDistance-maxAttractionDistance"));
                    if (s_maxRepulsionDistance >= s_minAttractionDistance) throw new FormatException(Messages.Get("Settings.Config.SimulationModel.NetworkFormation.Load.Error.maxRepulsionDistance-minAttractionDistance"));
                }
            }

        }

    }
}
