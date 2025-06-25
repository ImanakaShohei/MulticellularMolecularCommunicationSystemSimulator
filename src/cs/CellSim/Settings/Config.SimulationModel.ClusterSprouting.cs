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
            /// クラスタスプラウトモデルの設定
            /// </summary>
            public static class ClusterSprouting
            {
                private static int s_adhesionThreshold; //接着している細胞の数がこの値以下の時に反発力が働く
                private static double s_coefficientCd; //反発力にかける係数
                private static double s_contactDistance; //細胞同士がこの値より近づくと反発力が発生
                private static double s_followerAttractionFactor; //接着している細胞の数がadhesion_thresholdより多い時に受ける引力にかける係数
                private static double s_globalAttractionFactor; //すべての細胞間にかかる力の係数
                private static double s_lambda; //力の届く範囲を決める値
                private static double s_leaderRepulsionFactor; //接着している細胞の数がadhesion_thresholdの時に受ける反発力にかける係数
                private static double s_leaderRepulsionMaxDistance; //リーダーに届く反発力の最大距離
                private static double s_leaderRepulsionMinDistance; //リーダーに届く反発力の最小距離

                /// <summary>
                /// 接着している細胞の数がこの値以下の時に反発力が働く
                /// </summary>
                public static int AdhesionThreshold => s_adhesionThreshold;

                /// <summary>
                /// 反発力にかける係数
                /// </summary>
                public static double CoefficientCd => s_coefficientCd;

                /// <summary>
                /// 細胞同士がこの値より近づくと反発力が発生
                /// </summary>
                public static double ContactDistance => s_contactDistance;

                /// <summary>
                /// 接着している細胞の数がadhesion_thresholdより多い時に受ける引力にかける係数
                /// </summary>
                public static double FollowerAttractionFactor => s_followerAttractionFactor;

                /// <summary>
                /// すべての細胞間にかかる力の係数
                /// </summary>
                public static double GlobalAttractionFactor => s_globalAttractionFactor;

                /// <summary>
                /// 力の届く範囲を決める値
                /// </summary>
                public static double Lambda => s_lambda;

                /// <summary>
                /// 接着している細胞の数がadhesion_thresholdの時に受ける反発力にかける係数
                /// </summary>
                public static double LeaderRepulsionFactor => s_leaderRepulsionFactor;

                /// <summary>
                /// リーダーに届く反発力の最大距離
                /// </summary>
                public static double LeaderRepulsionMaxDistance => s_leaderRepulsionMaxDistance;

                /// <summary>
                /// リーダーに届く反発力の最小距離
                /// </summary>
                public static double LeaderRepulsionMinDistance => s_leaderRepulsionMinDistance;

                internal static void Load(JsonObject config)
                {
                    throw new NotImplementedException();
                }
            }

        }

    }
}
