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

            internal static void Load(JsonObject config)
            {
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

                if (s == "BarnesHut") s_algorithmType = CellAlgorithmType.BarnesHut;
                else if (s == "CellList") s_algorithmType = CellAlgorithmType.CellList;
                else if (s == "Naive") s_algorithmType = CellAlgorithmType.Naive;
                else if (s == "Null") s_algorithmType = CellAlgorithmType.Null;
                else if (s == "ParticleMesh") s_algorithmType = CellAlgorithmType.ParticleMesh;
                else if (s == "User") s_algorithmType = CellAlgorithmType.User;
                else throw new FormatException(Messages.Get("Settings.Config.CellAlgorithm.Load.Error.algorithmType"));

#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                switch (s_algorithmType)
                {
                    case CellAlgorithmType.BarnesHut: BarnesHut.Load(config["barnesHut"].AsObject()); break;
                    case CellAlgorithmType.CellList: CellList.Load(config["cellList"].AsObject()); break;
                    case CellAlgorithmType.Naive: break;
                    case CellAlgorithmType.Null: break;
                    case CellAlgorithmType.ParticleMesh: ParticleMesh.Load(config["particleMesh"].AsObject()); break;
                    case CellAlgorithmType.User: User.Load(config["User"].AsObject()); break;
                }
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
            }
        }

    }
}
