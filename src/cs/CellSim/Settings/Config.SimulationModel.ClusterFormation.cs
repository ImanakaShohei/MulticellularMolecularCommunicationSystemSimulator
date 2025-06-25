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
                    throw new NotImplementedException();
                }
            }

        }

    }
}
