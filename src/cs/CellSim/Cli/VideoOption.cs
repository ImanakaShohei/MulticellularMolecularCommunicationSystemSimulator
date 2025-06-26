using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cli
{
    public sealed class VideoOption : FlagOption
    {
        public override string FullName => "--video";

        public override string Names => "-v, --video";

        public override CliOptionType OptionType => CliOptionType.Video;

        public override bool TakesControl => false;

        public override bool IsMatch(string optionName) => optionName == "-v" || optionName == "--video";

        public override void OnActive(ReadOnlyCliOptions sender, CliOptionActivationArgs args)
        {
        }

    }
}
