using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cli
{
    public sealed class BinaryOption : FlagOption
    {
        public override string FullName => "--binary";

        public override string Names => "-b, --binary";

        public override CliOptionType OptionType => CliOptionType.Binary;

        public override bool TakesControl => false;

        public override bool IsMatch(string optionName) => optionName == "-b" || optionName == "--binary";

        public override void OnActive(ReadOnlyCliOptions sender, CliOptionActivationArgs args)
        {
        }


    }
}
