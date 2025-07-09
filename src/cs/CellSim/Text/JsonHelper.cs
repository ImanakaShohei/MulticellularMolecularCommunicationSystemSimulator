using OpenCvSharp.Flann;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Nodes;
using System.Threading.Tasks;

namespace CellSim.Text
{
    public static class JsonHelper
    {
        public static JsonNode? GetParam(JsonNode j, string paramName)
        {
            int index = paramName.IndexOf('.');

            if (index == -1) return j[paramName];

            string param1 = paramName[..index];

            JsonNode? j1 = j[paramName];

            if (j1 == null) return null;

            string newParamName = paramName[(index + 1)..];

            return GetParam(j, newParamName);
        }
public static int ToInt32(this JsonNode? node)
        {
            ArgumentNullException.ThrowIfNull(node);
            return int.Parse(node.ToString());
        }

        public static long ToInt64(this JsonNode? node)
        {
            ArgumentNullException.ThrowIfNull(node);
            return long.Parse(node.ToString());
        }

        public static double ToDouble(this JsonNode? node)
        {
            ArgumentNullException.ThrowIfNull(node);
            return double.Parse(node.ToString());
        }

        public static ulong ToUInt64(this JsonNode? node)
        {
            ArgumentNullException.ThrowIfNull(node);
            return ulong.Parse(node.ToString());
        }
    }
}
