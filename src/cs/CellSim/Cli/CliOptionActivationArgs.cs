using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cli
{
    public struct CliOptionActivationArgs
    {
        public Dictionary<CliOptionType, ReadOnlyCliOption> Options;

        public CliOptionActivationArgs(Dictionary<CliOptionType, ReadOnlyCliOption> options)
        {
            Options = options;
        }
    }
}
