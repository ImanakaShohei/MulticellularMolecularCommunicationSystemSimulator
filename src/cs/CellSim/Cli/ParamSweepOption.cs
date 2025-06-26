using CellSim.Settings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Text.Json.Nodes;
using System.Threading.Tasks;

namespace CellSim.Cli
{
    public sealed class ParamSweepOption : ValueOption
    {
        private const string s_fullName = "--param-sweep";

        private static JsonNode CheckValue(JsonObject config, string param)
        {
            int index = param.IndexOf('.');

            if (index != -1)
            {
                string paramName = param.Substring(0, index);
                JsonNode node = config[paramName] ?? throw new ArgumentException(Messages.Get("Cli.ParamSweepOption.CheckValue.Error.NotFound"));

                return CheckValue(node.AsObject(), param.Substring(index + 1));
            }

            JsonNode? j = config[param];

            if (j is not null)
            {
                try
                {
                    _ = j.GetValue<double>();
                }
                catch
                {
                    throw new ArgumentException(Messages.Get("Cli.ParamSweepOption.CheckValue.Error.NotNumber"));
                }

                return j;
            }

            config.Add(param, 0.0);

#pragma warning disable CS8603 // Null 参照戻り値である可能性があります。
            return config[param];
#pragma warning restore CS8603 // Null 参照戻り値である可能性があります。
        }
        public override string FullName => s_fullName;

        public override string Names => s_fullName;

        public override CliOptionType OptionType => CliOptionType.ParamSweep;

        public override bool TakesControl => true;

        public override bool IsMatch(string optionName) => optionName == s_fullName;

        public override void OnActive(ReadOnlyCliOptions sender, CliOptionActivationArgs args)
        {
            int index = m_value.IndexOf('=');

            if (index == -1) throw new FormatException(Messages.Get("Cli.ParamSweepOption.OnActive.Error"));

            string paramName = m_value.Substring(0, index);

            string[] values = m_value.Substring(index + 1).Split(':');

            if (values.Length != 3) throw new FormatException(Messages.Get("Cli.ParamSweepOption.OnActive.Error"));

            bool isFloatingPoint = false;

            foreach (string value in values)
            {
                if (value.Contains('.'))
                {
                    isFloatingPoint = true;
                }
            }

            JsonObject config = Config.OpenJsonFile(args.Options[CliOptionType.Output].Value);

            if (isFloatingPoint)
            {
                double begin;
                double end;
                double delta;
                try
                {
                    begin = double.Parse(values[0]);
                    end = double.Parse(values[1]);
                    delta = double.Parse(values[2]);
                }
                catch
                {
                    throw new FormatException(Messages.Get("Cli.ParamSweepOption.OnActive.Error"));
                }
                
                for (double current = begin; current < end; current += delta)
                {
                    JsonNode j = CheckValue(config, paramName);

#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                    j.Parent[paramName.Split('.')[^1]] = current;
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。

                    string path = $"{args.Options[CliOptionType.Output].Value}{paramName}={current}";

                    Directory.CreateDirectory(path);

#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                    SimulationOption option = new SimulationOption(
                        (args.Options[CliOptionType.Binary] as CliOption).IsEnabled,
                        (args.Options[CliOptionType.Csv] as CliOption).IsEnabled,
                        (args.Options[CliOptionType.Image] as CliOption).IsEnabled,
                        (args.Options[CliOptionType.Video] as CliOption).IsEnabled,
                        path
                    );
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。

                    Simulation simulation = new Simulation(option);

                    simulation.Run();
                }
            }
            else
            {
                long begin;
                long end;
                long delta;
                try
                {
                    begin = long.Parse(values[0]);
                    end = long.Parse(values[1]);
                    delta = long.Parse(values[2]);
                }
                catch
                {
                    throw new FormatException(Messages.Get("Cli.ParamSweepOption.OnActive.Error"));
                }

                for (long current = begin; current < end; current += delta)
                {
                    JsonNode j = CheckValue(config, paramName);

#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                    j.Parent[paramName.Split('.')[^1]] = current;
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。

                    string path = $"{args.Options[CliOptionType.Output].Value}{paramName}={current}";

                    Directory.CreateDirectory(path);

#pragma warning disable CS8602 // null 参照の可能性があるものの逆参照です。
                    SimulationOption option = new SimulationOption(
                        (args.Options[CliOptionType.Binary] as CliOption).IsEnabled,
                        (args.Options[CliOptionType.Csv] as CliOption).IsEnabled,
                        (args.Options[CliOptionType.Image] as CliOption).IsEnabled,
                        (args.Options[CliOptionType.Video] as CliOption).IsEnabled,
                        path
                    );
#pragma warning restore CS8602 // null 参照の可能性があるものの逆参照です。

                    Simulation simulation = new Simulation(option);

                    simulation.Run();
                }
            }
        }
    }
}
