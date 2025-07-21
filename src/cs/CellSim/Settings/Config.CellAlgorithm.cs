using CellSim.CellAlgorithms;
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
        public static partial class CellAlgorithm
        {
            private static CellAlgorithmType s_algorithmType;
            private static bool s_useClusterModel;

            /// <summary>
            /// 使用するアルゴリズム
            /// </summary>
            public static CellAlgorithmType AlgorithmType => s_algorithmType;

            /// <summary>
            /// シミュレーションでクラスタモデルを使用するかどうか
            /// </summary>
            public static bool UseClusterModel => s_useClusterModel;

            internal static void Load(JsonNode? config)
            {
                if (config == null) throw new FormatException(Messages.Get("Settings.Config.CellAlgorithm.Load.Error.JsonError"));

                string s;
                try
                {
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                    s_useClusterModel = config["useClusterModel"].GetValue<bool>();
                    s = config["algorithmType"].GetValue<string>();
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
                }
                catch
                {
                    throw new FormatException(Messages.Get("Settings.Config.CellAlgorithm.Load.Error.JsonError"));
                }

                s_algorithmType = s switch
                {
                    "BarnesHut" => CellAlgorithmType.BarnesHut,
                    "CellList" => CellAlgorithmType.CellList,
                    "Naive" => CellAlgorithmType.Naive,
                    "Null" => CellAlgorithmType.Null,
                    "ParticleMesh" => CellAlgorithmType.ParticleMesh,
                    "User" => CellAlgorithmType.User,
                    _ => throw new FormatException(Messages.Get("Settings.Config.CellAlgorithm.Load.Error.algorithmType"))
                };

                BarnesHut.Load(config["barnesHut"]);
                CellList.Load(config["cellList"]);
                ParticleMesh.Load(config["particleMesh"]);
                User.Load(config["User"]);
            }
        }

    }
}
