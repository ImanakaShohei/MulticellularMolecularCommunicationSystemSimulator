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

            internal static void Load(JsonNode? config)
            {
                if (config == null) throw new FormatException(Messages.Get("Settings.Config.SimulationModel.Load.Error.JsonError"));

                string s;

                try
                {
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                    s = config["simulationType"].GetValue<string>();
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
                }
                catch
                {
                    throw new FormatException(Messages.Get("Settings.Config.SimulationModel.Load.Error.JsonError"));
                }

                s_simulationType = s switch
                {
                    "CellGrowth" => CellSimulationType.CellGrowth,
                    "ClusterFormation" => CellSimulationType.ClusterFormation,
                    "ClusterRotation" => CellSimulationType.ClusterRotation,
                    "ClusterSprouting" => CellSimulationType.ClusterSprouting,
                    "NetworkFormation" => CellSimulationType.NetworkFormation,
                    "Null" => CellSimulationType.Null,
                    "User" => CellSimulationType.User,
                    _ => throw new FormatException(Messages.Get("Settings.Config.SimulationModel.Load.Error.simulationType"))
                };

                CellGrowth.Load(config["cellGrowth"]);
                ClusterFormation.Load(config["clusterFormation"]);
                ClusterRotation.Load(config["clusterRotation"]);
                ClusterSprouting.Load(config["clusterSprouting"]);
                NetworkFormation.Load(config["networkFormation"]);
                User.Load(config["user"]);
            }
        }

    }
}
