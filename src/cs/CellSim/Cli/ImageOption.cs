using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cli
{
    public sealed class ImageOption : FlagOption
    {
        public override string FullName => "--image";

        public override string Names => "-i, --image";

        public override CliOptionType OptionType => CliOptionType.Image;

        public override bool TakesControl => false;

        public override bool IsMatch(string optionName) => optionName == "-i" || optionName == "--image";

        public override void OnActive(ReadOnlyCliOptions sender, CliOptionActivationArgs args)
        {
        }


    }
}
