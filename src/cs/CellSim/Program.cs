using CellSim.Cli;
using OpenCvSharp;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CellSim
{
    internal static class Program
    {
        internal static void Main(string[] args)
        {
            // うっざい表示を抑制
            Cv2.SetLogLevel(LogLevel.SILENT);

            CliMain.Run(args);
        }
    }
}
