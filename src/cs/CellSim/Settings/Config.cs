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

            Load(node);
        }
        internal static void Load(JsonNode config)
        {
            Cell.Load(config["cell"]);
            CellAlgorithm.Load(config["cellAlgorithm"]);
            CellBehavior.Load(config["cellBehavior"]);
            Optimization.Load(config["optimization"]);
            Simulation.Load(config["simulation"]);
            SimulationModel.Load(config["simulationModel"]);
            UserSettings.Load(config["userSettings"]);
        }

        internal static JsonObject OpenJsonFile(string path)
        {
            using FileStream fileStream = new FileStream(path, FileMode.Open, FileAccess.Read);
            
            JsonNode? node = JsonNode.Parse(fileStream) ?? throw new ArgumentException("JsonObject Config.OpenJsonFile(string path)");

            return node.AsObject();
        }
    }
}
