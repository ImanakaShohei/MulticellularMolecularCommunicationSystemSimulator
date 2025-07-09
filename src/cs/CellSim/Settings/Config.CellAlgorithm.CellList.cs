using CellSim.CellAlgorithms;
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
        public static partial class CellAlgorithm
        {
            public static class CellList
            {
                private static int s_gridCount;
                private static double s_searchRadius;

                /// <summary>
                /// 
                /// </summary>
                public static int GridCount => s_gridCount;

                /// <summary>
                /// 探索範囲
                /// </summary>
                public static double SearchRadius => s_searchRadius;

                internal static void Load(JsonObject config)
                {
                    try
                    {
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                        s_gridCount = config["gridCount"].ToInt32();
                        s_searchRadius = config["searchRadius"].ToDouble();
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
                    }
                    catch
                    {
                        throw new FormatException(Messages.Get("Settings.Config.CellAlgorithm.CellList.Load.Error.JsonError"));
                    }

                    if (s_gridCount == 0) throw new FormatException(Messages.Get("Settings.Config.CellAlgorithm.CellList.Load.Error.gridCount"));
                    if (s_searchRadius == 0) throw new FormatException(Messages.Get("Settings.Config.CellAlgorithm.CellList.Load.Error.searchRadius"));
                }
            }

        }

    }
}
