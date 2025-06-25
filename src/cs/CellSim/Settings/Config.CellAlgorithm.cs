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
                throw new NotImplementedException();
            }
        }

    }
}
