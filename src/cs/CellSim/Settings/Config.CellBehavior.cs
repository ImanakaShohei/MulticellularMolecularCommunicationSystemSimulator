using CellSim.Cells;
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
            private static CellBehaviorType s_behaviorType;

            /// <summary>
            /// ふるまい定義
            /// </summary>
            public static CellBehaviorType BehaviorType => s_behaviorType;

            internal static void Load(JsonNode? config)
            {
                if (config == null) throw new FormatException(Messages.Get("Settings.Config.CellBehavior.Load.Error.JsonError"));
                string s;

                try
                {
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                    s = config["behaviorType"].GetValue<string>();
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
                }
                catch
                {
                    throw new FormatException(Messages.Get("Settings.Config.CellBehavior.Load.Error.JsonError"));
                }

                s_behaviorType = s switch
                {
                    "MoleculeAware" => CellBehaviorType.MoleculeAware,
                    "Normal" => CellBehaviorType.Normal,
                    "User" => CellBehaviorType.User,
                    "WavePropagation" => CellBehaviorType.WavePropagation,
                    _ => throw new FormatException(Messages.Get("Settings.Config.CellBehavior.Load.Error.behaviorType"))
                };

                MoleculeAware.Load(config["moleculeAware"]);
                Normal.Load(config["normal"]);
                User.Load(config["user"]);
                WavePropagation.Load(config["wavePropagation"]);
            }
        }

    }
}
