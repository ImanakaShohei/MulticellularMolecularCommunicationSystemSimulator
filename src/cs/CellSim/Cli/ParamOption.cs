using CellSim.Text;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Text.Json.Nodes;
using System.Threading.Tasks;

namespace CellSim.Cli
{
    public sealed class ParamOption : RepeatedValueOption
    {
        private const string s_fullName = "--param";
        private const string s_shortName = "-p";

        public static void OverrideParameter(JsonObject config, string param)
        {
            int index = param.IndexOf('=');

            if (index == -1 || index == 0) throw new FormatException(Messages.Get("Cli.ParamOption.OverrideParameter.Error.FormatError"));

            string paramName = param[..index];
            string value = param[(index + 1)..];

            JsonNode j = JsonHelper.GetParam(config, paramName) ?? throw new ArgumentException(Messages.Get("Cli.ParamOption.OverrideParameter.Error.NotFound"));
            
            switch (j.GetValueKind())
            {
                case JsonValueKind.True:
                case JsonValueKind.False:

                    config[paramName] = value switch
                    {
                        "true" => true,
                        "false" => false,
                        _ => throw new FormatException(Messages.Get("Cli.ParamOption.OverrideParameter.Error.InvalidValue"))
                    };

                    break;

                case JsonValueKind.Number:
                    double v;

                    if (!double.TryParse(value, out v)) throw new FormatException(Messages.Get("Cli.ParamOption.OverrideParameter.Error.InvalidValue"));

                    config[paramName] = v;
                    break;

                case JsonValueKind.String:
                    config[paramName] = value;
                    break;

                default: throw new ArgumentException(Messages.Get("Cli.ParamOption.OverrideParameter.Error.InvalidParam"));
            }
        }
        public override string FullName => s_fullName;

        public override string Names => $"{s_shortName} {s_fullName}";

        public override CliOptionType OptionType => CliOptionType.Param;

        public override bool TakesControl => false;

        public override bool IsMatch(string optionName) => optionName == s_shortName || optionName == s_fullName;

        public override void OnActive(ReadOnlyCliOptions sender, CliOptionActivationArgs args)
        {
        }

        public void OverrideParameter(JsonObject config)
        {
            foreach (string param in m_values)
            {
                OverrideParameter(config, param);
            }
        }
    }
}
