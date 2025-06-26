using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cli
{
    public sealed class SettingOption : ValueOption
    {
        public SettingOption() : base("./config.json/")
        {
        }

        public override string FullName => "--setting";

        public override string Names => "-s, --setting";

        public override CliOptionType OptionType => CliOptionType.Setting;

        public override bool TakesControl => false;

        public override void AddValue(string value)
        {
            m_value = value;

            m_value = value[^1] switch
            {
                '\\' or '/' => value,
                _ => $"{value}{Path.DirectorySeparatorChar}",
            };
        }

        public override bool IsMatch(string optionName) => optionName == "-s" || optionName == "--setting";

        public override void OnActive(ReadOnlyCliOptions sender, CliOptionActivationArgs args)
        {
        }

    }
}
