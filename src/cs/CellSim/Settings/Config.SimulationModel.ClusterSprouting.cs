using CellSim.Model;
using CellSim.Text;
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
                    try
                    {
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                        s_adhesionThreshold = config["adhesionThreshold"].ToInt32();
                        s_coefficientCd = config["coefficientCd"].ToDouble();
                        s_contactDistance = config["contactDistance"].ToDouble();
                        s_followerAttractionFactor = config["followerAttractionFactor"].ToDouble();
                        s_globalAttractionFactor = config["globalAttractionFactor"].ToDouble();
                        s_lambda = config["lambda"].ToDouble();
                        s_leaderRepulsionFactor = config["leaderRepulsionFactor"].ToDouble();
                        s_leaderRepulsionMaxDistance = config["leaderRepulsionMaxDistance"].ToDouble();
                        s_leaderRepulsionMinDistance = config["leaderRepulsionMinDistance"].ToDouble();
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
                    }
                    catch
                    {
                        throw new FormatException(Messages.Get("Settings.Config.SimulationModel.ClusterSprouting.Load.Error.JsonError"));
                    }

                    if (s_coefficientCd < 0.0) throw new FormatException(Messages.Get("Settings.Config.SimulationModel.ClusterSprouting.Load.Error.coefficientCd"));
                    if (s_contactDistance < 0.0) throw new FormatException(Messages.Get("Settings.Config.SimulationModel.ClusterSprouting.Load.Error.contactDistance"));
                    if (s_followerAttractionFactor < 0.0) throw new FormatException(Messages.Get("Settings.Config.SimulationModel.ClusterSprouting.Load.Error.followerAttractionFactor"));
                    if (s_globalAttractionFactor < 0.0) throw new FormatException(Messages.Get("Settings.Config.SimulationModel.ClusterSprouting.Load.Error.globalAttractionFactor"));
                    if (s_lambda == 0.0) throw new FormatException(Messages.Get("Settings.Config.SimulationModel.ClusterSprouting.Load.Error.lambda"));
                    if (s_leaderRepulsionFactor < 0.0) throw new FormatException(Messages.Get("Settings.Config.SimulationModel.ClusterSprouting.Load.Error.leaderRepulsionFactor"));
                    if (s_leaderRepulsionMaxDistance < 0.0) throw new FormatException(Messages.Get("Settings.Config.SimulationModel.ClusterSprouting.Load.Error.leaderRepulsionMaxDistance"));
                    if (s_leaderRepulsionMinDistance < 0.0) throw new FormatException(Messages.Get("Settings.Config.SimulationModel.ClusterSprouting.Load.Error.leaderRepulsionMinDistance"));

                    if (s_contactDistance >= s_leaderRepulsionMinDistance) throw new FormatException(Messages.Get("Settings.Config.SimulationModel.ClusterSprouting.Load.Error.contactDistance-leaderRepulsionMinDistance"));
                }
            }

        }

    }
}
