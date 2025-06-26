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
        internal static void Load(string path)
        {
            using FileStream fileStream = new FileStream(path, FileMode.Open, FileAccess.Read);
            JsonNode? node = JsonNode.Parse(fileStream);

            if (node == null) return;

            Load(node.AsObject());
        }
        internal static void Load(JsonObject config)
        {
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
            Cell.Load(config["cell"].AsObject());
            CellAlgorithm.Load(config["cellAlgorithm"].AsObject());
            CellBehavior.Load(config["cellBehavior"].AsObject());
            Optimization.Load(config["optimization"].AsObject());
            Simulation.Load(config["simulation"].AsObject());
            SimulationModel.Load(config["simulationModel"].AsObject());
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
        }

        internal static JsonObject OpenJsonFile(string path)
        {
            using FileStream fileStream = new FileStream(path, FileMode.Open, FileAccess.Read);
            
            JsonNode? node = JsonNode.Parse(fileStream) ?? throw new ArgumentException("JsonObject Config.OpenJsonFile(string path)");

            return node.AsObject();
        }
    }
}
