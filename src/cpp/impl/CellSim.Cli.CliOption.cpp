#include "CellSim.Cli.CliOption.hpp"
#include "CellSim.Cli.CliOptionType.hpp"

namespace CellSim::Cli
{
    CliOptionType CliOption::Parse(::std::string_view view)
    {
        using namespace std;

        if (view == "-h"sv || view == "--help"sv) return CliOptionType::Help;
    }
}