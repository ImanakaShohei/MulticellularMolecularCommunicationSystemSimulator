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
            private static CellSimulationType s_simulationType;

            /// <summary>
            /// モデルの種類
            /// </summary>
            public static CellSimulationType SimulationType => s_simulationType;

            internal static void Load(JsonObject config)
            {
                throw new NotImplementedException();
            }
        }

    }
}
