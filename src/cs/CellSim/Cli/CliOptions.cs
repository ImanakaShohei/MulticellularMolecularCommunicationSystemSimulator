using CellSim.Settings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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

                Config.Load("./config.json");

                Simulation sim = new Simulation(CreateSimulationOption());

                sim.Run();
            }
        }
    }
}
