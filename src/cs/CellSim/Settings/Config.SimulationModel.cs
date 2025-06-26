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
                string s;

                try
                {
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                    s = config["simulationType"].GetValue<string>();
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
                }
                catch {
                    throw new FormatException(Messages.Get("Settings.Config.SimulationModel.Load.Error.JsonError"));
                }

                if (s == "CellGrowth") s_simulationType = CellSimulationType.CellGrowth;
                else if (s == "ClusterFormation") s_simulationType = CellSimulationType.ClusterFormation;
                else if (s == "ClusterRotation") s_simulationType = CellSimulationType.ClusterRotation;
                else if (s == "ClusterSprouting") s_simulationType = CellSimulationType.ClusterSprouting;
                else if (s == "NetworkFormation") s_simulationType = CellSimulationType.NetworkFormation;
                else if (s == "Null") s_simulationType = CellSimulationType.Null;
                else if (s == "User") s_simulationType = CellSimulationType.User;
                else throw new FormatException(Messages.Get("Settings.Config.SimulationModel.Load.Error.simulationType"));

#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                switch (s_simulationType)
                {
                    case CellSimulationType.CellGrowth: CellGrowth.Load(config["cellGrowth"].AsObject()); break;
                    case CellSimulationType.ClusterFormation: ClusterFormation.Load(config["clusterFormation"].AsObject()); break;
                    case CellSimulationType.ClusterRotation: ClusterRotation.Load(config["clusterRotation"].AsObject()); break;
                    case CellSimulationType.ClusterSprouting: ClusterSprouting.Load(config["clusterSprouting"].AsObject()); break;
                    case CellSimulationType.NetworkFormation: NetworkFormation.Load(config["networkFormation"].AsObject()); break;
                    case CellSimulationType.Null: break;
                    case CellSimulationType.User: User.Load(config["user"].AsObject()); break;
                }
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
            }
        }

    }
}
