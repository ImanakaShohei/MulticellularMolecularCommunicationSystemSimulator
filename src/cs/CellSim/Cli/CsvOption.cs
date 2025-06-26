using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cli
{
    public sealed class CsvOption : FlagOption
    {
        public override string FullName => "--csv";

        public override string Names => "-c, --csv";

        public override CliOptionType OptionType => CliOptionType.Csv;

        public override bool TakesControl => false;

        public override bool IsMatch(string optionName) => optionName == "-c" || optionName == "--csv";

        public override void OnActive(ReadOnlyCliOptions sender, CliOptionActivationArgs args)
        {
        }

        
    }
}
