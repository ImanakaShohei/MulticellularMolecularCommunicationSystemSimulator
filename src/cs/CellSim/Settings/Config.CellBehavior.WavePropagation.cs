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
        public static partial class CellBehavior
        {
            public static class WavePropagation
            {
                private static double s_cellDivisionRadius;
                private static double s_degradationRate;
                private static double s_synthesisRate;

                private static double s_c;
                private static double s_k_1;
                private static double s_k_2;
                private static double s_l_1;
                private static double s_l_2;
                private static double s_q;
                private static double s_sigma;
                private static double s_k_i;
                private static double s_k_e;
                private static double s_k_t;
                private static double s_alpha;
                private static double s_h;
                private static double s_theta;
                private static double s_lambda;
                private static double s_epsilon;

                public static double CellDivisionRadius => s_cellDivisionRadius;
                public static double DegradationRate => s_degradationRate;
                public static double SynthesisRate => s_synthesisRate;
                public static double C => s_c;
                public static double K1 => s_k_1;
                public static double K2 => s_k_2;
                public static double L1 => s_l_1;
                public static double L2 => s_l_2;
                public static double Q => s_q;
                public static double Sigma => s_sigma;
                public static double Ki => s_k_i;
                public static double Ke => s_k_e;
                public static double Kt => s_k_t;
                public static double Alpha => s_alpha;
                public static double H => s_h;
                public static double Theta => s_theta;
                public static double Lambda => s_lambda;
                public static double Epsilon => s_epsilon;

                internal static void Load(JsonNode? config)
                {
                    if (config == null) return;

                    try
                    {
#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                        s_cellDivisionRadius = config["cellDivisionRadius"].ToDouble();
                        s_degradationRate = config["degradationRate"].ToDouble();
                        s_synthesisRate = config["synthesisRate"].ToDouble();
                        s_c = config["c"].ToDouble();
                        s_k_1 = config["k1"].ToDouble();
                        s_k_2 = config["k2"].ToDouble();
                        s_l_1 = config["l1"].ToDouble();
                        s_l_2 = config["l2"].ToDouble();
                        s_q = config["q"].ToDouble();
                        s_sigma = config["sigma"].ToDouble();
                        s_k_i = config["ki"].ToDouble();
                        s_k_e = config["ke"].ToDouble();
                        s_k_t = config["kt"].ToDouble();
                        s_alpha = config["alpha"].ToDouble();
                        s_h = config["h"].ToDouble();
                        s_theta = config["theta"].ToDouble();
                        s_lambda = config["lambda"].ToDouble();
                        s_epsilon = config["epsilon"].ToDouble();
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。
                    }
                    catch
                    {
                        throw new FormatException(Messages.Get("Settings.Config.CellBehavior.WavePropagation.Load.Error.JsonError"));
                    }

                    if (s_cellDivisionRadius <= 0.0) throw new FormatException(Messages.Get("Settings.Config.CellBehavior.WavePropagation.Load.Error.cellDivisionRadius"));
                    if (s_degradationRate <= 0.0) throw new FormatException(Messages.Get("Settings.Config.CellBehavior.WavePropagation.Load.Error.degradationRate"));
                    if (s_synthesisRate <= 0.0) throw new FormatException(Messages.Get("Settings.Config.CellBehavior.WavePropagation.Load.Error.synthesisRate"));
                }
            }
        }
    }
}
