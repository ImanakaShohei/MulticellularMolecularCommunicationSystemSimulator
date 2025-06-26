using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cli
{
    public struct CliOptionActivationArgs
    {
        public IReadOnlyDictionary<CliOptionType, ReadOnlyCliOption> Options;

        public CliOptionActivationArgs(IReadOnlyDictionary<CliOptionType, ReadOnlyCliOption> options)
        {
            Options = options;
        }
    }
}
