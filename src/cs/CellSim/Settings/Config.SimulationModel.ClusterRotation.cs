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
            /// <summary>
            /// クラスタ回転モデルの設定
            /// </summary>
            public static class ClusterRotation
            {

                private static double s_adhesionDistanceThreshold;
                private static double s_adhesionForceFactor;
                private static double s_centralForceFactor;
                private static double s_repulsionFactor;
                private static double s_repulsionMaxDistance;

                /// <summary>
                /// 細胞同士がこの値より近いと接着力が働く
                /// </summary>
                public static double AdhesionDistanceThreshold => s_adhesionDistanceThreshold;

                /// <summary>
                /// 接着力にかける係数
                /// </summary>
                public static double AdhesionForceFactor => s_adhesionForceFactor;

                /// <summary>
                /// 中心力にかける係数
                /// </summary>
                public static double CentralForceFactor => s_centralForceFactor;

                /// <summary>
                /// 反発力の係数
                /// </summary>
                public static double RepulsionFactor => s_repulsionFactor;

                /// <summary>
                /// 細胞同士がこの値より近いと反発する
                /// </summary>
                public static double RepulsionMaxDistance => s_repulsionMaxDistance;

                internal static void Load(JsonObject config)
                {
                    throw new NotImplementedException();
                }
            }

        }

    }
}
