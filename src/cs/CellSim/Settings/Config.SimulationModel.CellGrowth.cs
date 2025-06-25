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
            public static class CellGrowth
            {
                private static double s_adhesiveRepulsionFactor;

                /// <summary>
                /// くっついた細胞同士に働く反発力の係数
                /// </summary>
                public static double AdhesiveRepulsionFactor => s_adhesiveRepulsionFactor;

                internal static void Load(JsonObject config)
                {
                    throw new NotImplementedException();
                }
            }

        }

    }
}
