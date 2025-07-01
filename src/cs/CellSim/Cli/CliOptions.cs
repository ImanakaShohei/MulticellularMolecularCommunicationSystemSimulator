using CellSim.Settings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Nodes;
using System.Threading.Tasks;

namespace CellSim.Cli
{
    public sealed class CliOptions : ReadOnlyCliOptions
    {
        internal CliOptions(string[] args) : base(args)
        {
        }

        internal void Run()
        {
            if (m_controllerOption != null)
            {
                m_controllerOption.Run(this);
            }
            else
            {
                JsonObject config = Config.OpenJsonFile(m_options[CliOptionType.Setting].Value);

                ParamOption paramOption = (ParamOption)m_options[CliOptionType.Param];

                if (paramOption.IsEnabled)
                {
                    paramOption.OverrideParameter(config);
                }

                Config.Load(config);

                Simulation sim = new Simulation(CreateSimulationOption());

                sim.Run();
            }
        }
    }
}
