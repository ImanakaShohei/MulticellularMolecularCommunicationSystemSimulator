using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cli
{
    public sealed class OutputOption : ValueOption
    {
        public OutputOption() : base("./result/")
        {
        }

        public override string FullName => "--output";

        public override string Names => "-o, --output";

        public override CliOptionType OptionType => CliOptionType.Output;

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

        public override bool IsMatch(string optionName) => optionName == "-o" || optionName == "--output";

        public override void OnActive(ReadOnlyCliOptions sender, CliOptionActivationArgs args)
        {
        }

    }
}
