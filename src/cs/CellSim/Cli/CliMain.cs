using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim.Cli
{
    public static class CliMain
    {
        public static void Run(string[] args)
        {
            Console.WriteLine($"CellSim {Versions.Major}.{Versions.Minor}.{Versions.Patch} {Versions.Extension}");
            Console.WriteLine();
        
            Messages.Initialize();

            CliOptions options = new CliOptions(args);

            options.Run();
        }
    }
}
