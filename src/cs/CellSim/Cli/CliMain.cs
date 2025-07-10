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
            Console.WriteLine($"CellSim {Version.Major}.{Version.Minor}.{Version.Patch} {Version.Extension}");
            Console.WriteLine();
        
            Messages.Initialize();

            CliOptions options = new CliOptions(args);

            options.Run();
        }
    }
}
