#include "CellSim.Cli.CliMain.hpp"
#include "CellSim.Cli.CliOptions.hpp"
#include "CellSim.Messages.hpp"
#include <iostream>
#include <stdexcept>

namespace CellSim::Cli
{
    int CliMain::Run(int argc, char** argv) noexcept
    {
        ::printf(
            "CellSim %d.%d.%d %s\n",
            CELLSIM_VERSION_MAJOR,
            CELLSIM_VERSION_MINOR,
            CELLSIM_VERSION_PATCH,
            CELLSIM_VERSION_EXTENSION
        );
        try {
            Messages::Initialize();

            CliOptions options(argc, argv);

            options.Run();
        }
        catch (::std::exception& e) {
            ::fprintf(stderr, "%s\n", e.what());
            return 1;
        }

        return 0;
    }
}