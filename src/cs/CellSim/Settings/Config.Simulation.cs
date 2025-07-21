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
        /// <summary>
        /// シミュレーション共通設定
        /// </summary>
        public static class Simulation
        {
            private static double s_deltaTime;
            private static bool s_enable2DMode;
            private static double s_fieldRadius;
            private static int s_imageSize;
            private static int s_outputInterval;
            private static ulong s_totalSteps;

            /// <summary>
            /// 1ステップあたりのシミュレーション内時間
            /// </summary>
            public static double DeltaTime => s_deltaTime;

            /// <summary>
            /// 2Dとしてシミュレーションするかどうか
            /// </summary>
            public static bool Enable2DMode => s_enable2DMode;

            /// <summary>
            /// フィールドのX方向の半径
            /// </summary>
            public static double FieldRadius => s_fieldRadius;

            /// <summary>
            /// フィールドのX方向の半径
            /// </summary>
            public static double FieldRadiusX => s_fieldRadius;

            /// <summary>
            /// フィールドのY方向の半径
            /// </summary>
            public static double FieldRadiusY => s_fieldRadius;

            /// <summary>
            /// フィールドのZ方向の半径
            /// </summary>
            public static double FieldRadiusZ => s_enable2DMode ? 0.0 : s_fieldRadius;

            /// <summary>
            /// 出力画像の縦横の長さ
            /// </summary>
            public static int ImageSize => s_imageSize;

            /// <summary>
            /// 出力間隔
            /// </summary>
            public static double OutputInterval => s_outputInterval;

            /// <summary>
            /// 総ステップ数
            /// </summary>
            public static ulong TotalSteps => s_totalSteps;

            internal static void Load(JsonNode? config)
            {
                if (config == null) throw new FormatException(Messages.Get("Settings.Config.Simulation.Load.Error.JsonError"));

                try
                {
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                    s_deltaTime = config["deltaTime"].ToDouble();
                    s_enable2DMode = config["enable2DMode"].GetValue<bool>();
                    s_fieldRadius = config["fieldRadius"].ToDouble();
                    s_imageSize = config["imageSize"].ToInt32();
                    s_outputInterval = config["outputInterval"].ToInt32();
                    s_totalSteps = config["totalSteps"].ToUInt64();
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
                }
                catch
                {
                    throw new FormatException(Messages.Get("Settings.Config.Simulation.Load.Error.JsonError"));
                }

                if (s_deltaTime <= 0.0) throw new FormatException(Messages.Get("Settings.Config.Simulation.Load.Error.deltaTime"));
                if (s_fieldRadius < 0.0) throw new FormatException(Messages.Get("Settings.Config.Simulation.Load.Error.fieldRadius"));
                if (s_imageSize <= 0) throw new FormatException(Messages.Get("Settings.Config.Simulation.Load.Error.imageSize"));
                if (s_outputInterval <= 0) throw new FormatException(Messages.Get("Settings.Config.Simulation.Load.Error.outputInterval"));
                if (s_totalSteps == 0) throw new FormatException(Messages.Get("Settings.Config.Simulation.Load.Error.totalSteps"));
            }
        }

    }
}
