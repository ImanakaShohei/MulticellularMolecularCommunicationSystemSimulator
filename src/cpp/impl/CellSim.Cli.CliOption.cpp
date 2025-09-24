#include "CellSim.Cli.CliOption.hpp"
#include "CellSim.Cli.CliOptionArgs.hpp"
#include "CellSim.Cli.CliOptionType.hpp"
#include "CellSim.Cli.CliOptionActivationArgs.hpp"
#include "CellSim.Messages.hpp"
#include "CellSim.SimulationOption.hpp"


#include <stdexcept>

namespace CellSim::Cli
{
    void CliOption::Enable()
    {
        if (m_isEnabled && !IsRepeatable()) [[unlikely]] {
            ::std::string s = "'";
            s.append(Names());
            s.push_back('\'');
            throw ::std::runtime_error(
                ::std::move(s) + Messages::Get("Cli.CliOption.Enable.Error")
            );
        }

        m_isEnabled = true;
    }

    void CliOption::OnActive(
        const CliOptions*,
        CliOptionActivationArgs
    )
    {
    }

    void CliOption::Run(
        const CliOptions*,
        CliOptionArgs
    )
    {
    }
}