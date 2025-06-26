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
        public static partial class CellBehavior
        {
            public static class Normal
            {
                private static double s_cellDivisionRadius;

                /// <summary>
                /// 細胞の半径がこの値を超えると分裂する
                /// </summary>
                public static double CellDivisionRadius => s_cellDivisionRadius;

                internal static void Load(JsonObject config)
                {
                    try
                    {
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                        s_cellDivisionRadius = config["cellDivisionRadius"].GetValue<double>();
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
                    }
                    catch
                    {
                        throw new FormatException(Messages.Get("Settings.Config.CellBehavior.Normal.Load.Error.JsonError"));
                    }

                    if (s_cellDivisionRadius <= 0.0) throw new FormatException(Messages.Get("Settings.Config.CellBehavior.Normal.Load.Error.cellDivisionRadius"));
                }
            }
        }
    }
}
