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

                internal static void Load(JsonObject config)
                {
                    throw new NotImplementedException();
                }
            }

        }

    }
}
