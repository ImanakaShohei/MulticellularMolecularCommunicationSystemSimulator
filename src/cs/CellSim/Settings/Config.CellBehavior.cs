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

            internal static void Load(JsonObject config)
            {
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

                if (s == "MoleculeAware") s_behaviorType = CellBehaviorType.MoleculeAware;
                else if (s == "Normal") s_behaviorType = CellBehaviorType.Normal;
                else if (s == "User") s_behaviorType = CellBehaviorType.User;
                else throw new FormatException(Messages.Get("Settings.Config.CellBehavior.Load.Error.behaviorType"));

#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                switch (s_behaviorType)
                {
                    case CellBehaviorType.MoleculeAware: MoleculeAware.Load(config["moleculeAware"].AsObject()); break;
                    case CellBehaviorType.Normal: Normal.Load(config["normal"].AsObject()); break;
                    case CellBehaviorType.User: User.Load(config["user"].AsObject()); break;
                }
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
            }
        }

    }
}
