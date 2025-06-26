#include "CellSim.Cli.SettingOption.hpp"
#include "CellSim.Cli.CliOptionActivationArgs.hpp"

namespace CellSim::Cli
{
    SettingOption::SettingOption() : ValueOption("./config.json")
    {
    }

    void SettingOption::OnActive(const CliOptions*, CliOptionActivationArgs)
    {
    }
}